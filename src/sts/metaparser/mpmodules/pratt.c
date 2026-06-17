#include "pratt.h"

#include "metaparser_errors.h"
#include "errors.h"
#include "mpmodules/utils.h"

void Pratt_Context_free(Pratt_Context* prattContext) {
  Lexems_freeElements(prattContext->lexems);
  Lexems_free(prattContext->lexems);
  Source_free(&prattContext->expressionSrc);
}


static void registerDeclarationValue(Sts_MetaDeclarationsBlock* decBlock, Sts_MetaDeclarationValue* value) {
  if (value->type == Sts_MetaDeclarationValueType_LINK) {
    Sts_MetaDeclarationValuesLinks_registerDeclaratonValue(&decBlock->links, value);
  }
}


typedef enum PrattCheckLeftResult {
  PrattCheckLeftResult_OK,
  PrattCheckLeftResult_PAREN_CLOSE,
  PrattCheckLeftResult_ERROR,
} PrattCheckLeftResult;
PrattCheckLeftResult pratt_checkLeft(Pratt_Context ctx, Sts_MetaDeclarationValue* retDecValue, Lexem* leftLexem);

Sts_MetaDeclarationValue pratt_loop(Pratt_Context ctx, int minLbp, Lexem* leftLexem, Sts_MetaDeclarationValue left);
Sts_MetaDeclarationValue pratt_prefix(Pratt_Context ctx, Lexem* op);
Sts_MetaDeclarationValue pratt_infix(Pratt_Context ctx, Lexem* op, Sts_MetaDeclarationValue left);
Sts_MetaDeclarationValue pratt_postfix(Pratt_Context ctx, Lexem* op, Sts_MetaDeclarationValue left);
Sts_MetaDeclarationValue pratt_infix_postfix(Pratt_Context ctx, Lexem* op, Sts_MetaDeclarationValue left, int minLbp);
Sts_MetaDeclarationValue pratt_paren(Pratt_Context ctx);


// main parse function. Parse left and run right parse loop
Sts_MetaDeclarationValue Pratt_pratt(Pratt_Context ctx, int minLbp) {
  Lexem* leftLexem = Lexems_get(ctx.lexems, *ctx.currIndex);
  if (!leftLexem) {
    if (*ctx.currIndex == 0) {
      Errors_metaparser_emptyExpression(ctx.ctx, ctx.expressionSrc);
      non_call_return (Sts_MetaDeclarationValue) {};
    }
    else {
      Lexem* prevLexem = Lexems_get(ctx.lexems, *ctx.currIndex - 1);
      Errors_metaparser_expressionWasAwaitingSubexpression(ctx.ctx, ctx.expressionSrc, prevLexem->src);
      non_call_return (Sts_MetaDeclarationValue) {};
    }
  }
  Sts_MetaDeclarationValue left;
  PrattCheckLeftResult result = pratt_checkLeft(ctx, &left, leftLexem);
  if (result == PrattCheckLeftResult_OK) {
    return pratt_loop(ctx, minLbp, leftLexem, left);
  }
  else if (result == PrattCheckLeftResult_PAREN_CLOSE) {
    return left;
  }
  else {
    Errors_metaparser_expressionWasAwaitingOperand(ctx.ctx, ctx.expressionSrc, leftLexem->src);
    non_call_return (Sts_MetaDeclarationValue) {}; // non run return
  }
}

// parse left value
PrattCheckLeftResult pratt_checkLeft(Pratt_Context ctx, Sts_MetaDeclarationValue* retDecValue, Lexem* leftLexem) {
  if (leftLexem->type == LexemType_VALUE) {
    *retDecValue = leftLexem->value.decValue;
    leftLexem->value.decValue = (Sts_MetaDeclarationValue) {0};
    return PrattCheckLeftResult_OK;
  }
  else if (leftLexem->type == LexemType_OPERATOR) {
    if (leftLexem->value.opData->isPrefix) {
      *ctx.currIndex += 1;
      *retDecValue = pratt_prefix(ctx, leftLexem);
      return PrattCheckLeftResult_OK;
    }
    else {
      return PrattCheckLeftResult_ERROR;
    }
  }
  else if (leftLexem->type == LexemType_PAREN_OPEN) {
    *ctx.currIndex += 1;
    *retDecValue = pratt_paren(ctx);
    return PrattCheckLeftResult_OK;
  }
  else if (leftLexem->type == LexemType_PAREN_CLOSE) {
    *retDecValue = (Sts_MetaDeclarationValue) {
      .type = Sts_MetaDeclarationValueType_NULL,
    };
    return PrattCheckLeftResult_PAREN_CLOSE;
  }
  else {
    Errors_internal_unexpectedBehavior(ViewString_of("pratt_checkLeft().leftLexem->type"), ViewString_of("unexpected enum value"));
    non_call_return 0; // non run return
  }
}
// main parse loop. dont check left
Sts_MetaDeclarationValue pratt_loop(Pratt_Context ctx, int minLbp, Lexem* leftLexem, Sts_MetaDeclarationValue startLeft) {
  Sts_MetaDeclarationValue left = startLeft;
  while (*ctx.currIndex < ctx.lexems->size - 1) {
    bool isLastIndex = *ctx.currIndex == ctx.lexems->size - 1;

    Lexem* opLexem = Lexems_get(ctx.lexems, *ctx.currIndex + 1);
    if (opLexem->type == LexemType_PAREN_CLOSE) {
      break;
    }
    else if (opLexem->type != LexemType_OPERATOR) {
      Errors_metaparser_expressionWasAwaitingOperator(ctx.ctx, ctx.expressionSrc, opLexem->src);
    }
    const Lexem_OpData* opData = opLexem->value.opData;
    if ((opData->isInfix && !isLastIndex) || opData->isPostfix) {
      if (opData->isInfix && !opData->isPostfix && opData->binLbp >= minLbp) { // only infix and good lbp
        *ctx.currIndex += 1;
        left = pratt_infix(ctx, opLexem, left);
      }
      else if ((!opData->isInfix || isLastIndex) && opData->isPostfix && opData->unaLbp >= minLbp) {
        *ctx.currIndex += 1;
        left = pratt_postfix(ctx, opLexem, left);
      }
      else if (opData->isPostfix && opData->isInfix) { // pratt_infix_postfix checks lbps by itself
        left = pratt_infix_postfix(ctx, opLexem, left, minLbp);
      }
      else {
        return left;
      }
    }
    else {
      Errors_metaparser_expressionWasAwaitingOperator(ctx.ctx, ctx.expressionSrc, opLexem->src);
    }
  }
  return left;
}

Sts_MetaDeclarationValue pratt_prefix(Pratt_Context ctx, Lexem* op) {
  const Lexem_OpData* opData = op->value.opData;
  Sts_MetaDeclarationValue right = Pratt_pratt(ctx, opData->unaLbp + opData->right);
  Sts_MetaDeclarationExpression* expression = A_xloc(sizeof(Sts_MetaDeclarationExpression));
  *expression = (Sts_MetaDeclarationExpression) {
    .type = opData->expType,
    .value1 = (Sts_MetaDeclarationValue) { .type = Sts_MetaDeclarationValueType_NULL },
    .value2 = right,
  };
  registerDeclarationValue(ctx.decBlock, &expression->value2);
  return (Sts_MetaDeclarationValue) {
    .type = Sts_MetaDeclarationValueType_EXPRESSION,
    .value.expression = expression,
  };
}
Sts_MetaDeclarationValue pratt_infix(Pratt_Context ctx, Lexem* op, Sts_MetaDeclarationValue left) {
  const Lexem_OpData* opData = op->value.opData;
  *ctx.currIndex += 1;
  Sts_MetaDeclarationValue right = Pratt_pratt(ctx, opData->binLbp + opData->right);
  Sts_MetaDeclarationExpression* expression = A_xloc(sizeof(Sts_MetaDeclarationExpression));
  *expression = (Sts_MetaDeclarationExpression) {
    .type = opData->expType,
    .value1 = left,
    .value2 = right,
  };
  registerDeclarationValue(ctx.decBlock, &expression->value1);
  registerDeclarationValue(ctx.decBlock, &expression->value2);
  return (Sts_MetaDeclarationValue) {
    .type = Sts_MetaDeclarationValueType_EXPRESSION,
    .value.expression = expression,
  };
}
Sts_MetaDeclarationValue pratt_postfix(Pratt_Context ctx, Lexem* op, Sts_MetaDeclarationValue left) {
  const Lexem_OpData* opData = op->value.opData;
  Sts_MetaDeclarationExpression* expression = A_xloc(sizeof(Sts_MetaDeclarationExpression));
  *expression = (Sts_MetaDeclarationExpression) {
    .type = opData->expType,
    .value1 = left,
    .value2 = (Sts_MetaDeclarationValue) { .type = Sts_MetaDeclarationValueType_NULL },
  };
  registerDeclarationValue(ctx.decBlock, &expression->value1);
  return (Sts_MetaDeclarationValue) {
    .type = Sts_MetaDeclarationValueType_EXPRESSION,
    .value.expression = expression,
  };
}
Sts_MetaDeclarationValue pratt_infix_postfix(Pratt_Context ctx, Lexem* op, Sts_MetaDeclarationValue left, int minLbp) {
  const Lexem_OpData* opData = op->value.opData;

  Lexem* rightLexem = Lexems_get(ctx.lexems, *ctx.currIndex);
  Sts_MetaDeclarationValue right;
  PrattCheckLeftResult checkResult = pratt_checkLeft(ctx, &right, rightLexem);

  if (checkResult == PrattCheckLeftResult_OK && opData->binLbp >= minLbp) { // infix
    *ctx.currIndex += 1;
    // here, pratt_loop is run directly to avoid an unnecessary call to pratt_checkLeft.
    Sts_MetaDeclarationValue right = pratt_loop(ctx, opData->binLbp, rightLexem, left);
    Sts_MetaDeclarationExpression* expression = A_xloc(sizeof(Sts_MetaDeclarationExpression));
    *expression = (Sts_MetaDeclarationExpression) {
      .type = opData->expType,
      .value1 = left,
      .value2 = right,
    };
    registerDeclarationValue(ctx.decBlock, &expression->value1);
    registerDeclarationValue(ctx.decBlock, &expression->value2);
    return (Sts_MetaDeclarationValue) {
      .type = Sts_MetaDeclarationValueType_EXPRESSION,
      .value.expression = expression,
    };
  }
  else if (opData->unaLbp >= minLbp) { // posfix
    *ctx.currIndex += 1;
    return pratt_postfix(ctx, op, left);
  }
  else {
    return left;
  }
}
Sts_MetaDeclarationValue pratt_paren(Pratt_Context ctx) {
  Sts_MetaDeclarationValue value = Pratt_pratt(ctx, 0);
  *ctx.currIndex += 1;
  return value;
}
