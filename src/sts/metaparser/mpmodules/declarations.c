#include "mpmodules/declarations.h"

#include "allocator.h"
#include "iter.h"
#include "metablocks.h"
#include "metaparser_errors.h"
#include "errors.h"
#include "mpmodules/utils.h"
#include "sources.h"


typedef struct OpData {
  bool isInfix;
  bool isPrefix;
  bool isPostfix;
  int binLbp; // binary priority
  int unaLbp; // unary priority
  int right; // open right priority shift (+1 for left-right ; -1 for right-left)
  Sts_MetaDeclarationExpressionType expType;
} OpData;
#define OpData_LEFT_ASSOCIATIVITY (+1)
#define OpData_RIGHT_ASSOCIATIVITY (-1)


OpData OpData_SUM = (OpData) { // +
  .isInfix = true,
  .isPrefix = true,
  .isPostfix = false,
  .binLbp = 10,
  .unaLbp = 30,
  .right = OpData_LEFT_ASSOCIATIVITY,
  .expType = Sts_MetaDeclarationExpressionType_SUM,
};
OpData OpData_SUB = (OpData) { // -
  .isInfix = true,
  .isPrefix = true,
  .isPostfix = false,
  .binLbp = 10,
  .unaLbp = 50,
  .right = OpData_LEFT_ASSOCIATIVITY,
  .expType = Sts_MetaDeclarationExpressionType_SUB,
};
OpData OpData_MUL = (OpData) { // *
  .isInfix = true,
  .isPrefix = false,
  .isPostfix = false,
  .binLbp = 20,
  .right = OpData_LEFT_ASSOCIATIVITY,
  .expType = Sts_MetaDeclarationExpressionType_MUL,
};
OpData OpData_DIV = (OpData) { // /
  .isInfix = true,
  .isPrefix = false,
  .isPostfix = false,
  .binLbp = 20,
  .right = OpData_LEFT_ASSOCIATIVITY,
  .expType = Sts_MetaDeclarationExpressionType_DIV,
};
OpData OpData_MOD = (OpData) { // %
  .isInfix = true,
  .isPrefix = false,
  .isPostfix = false,
  .binLbp = 20,
  .right = OpData_LEFT_ASSOCIATIVITY,
  .expType = Sts_MetaDeclarationExpressionType_MOD,
};
OpData OpData_POW = (OpData) { // **
  .isInfix = true,
  .isPrefix = false,
  .isPostfix = false,
  .binLbp = 40,
  .right = OpData_RIGHT_ASSOCIATIVITY,
  .expType = Sts_MetaDeclarationExpressionType_POW,
};
OpData OpData_INC = (OpData) { // ++
  .isInfix = false,
  .isPrefix = true,
  .isPostfix = true,
  .unaLbp = 50,
  .right = OpData_LEFT_ASSOCIATIVITY, // ++a++ -> (++a)++
  .expType = Sts_MetaDeclarationExpressionType_INC,
};
OpData OpData_DEC = (OpData) { // --
  .isInfix = false,
  .isPrefix = true,
  .isPostfix = true,
  .unaLbp = 50,
  .right = OpData_LEFT_ASSOCIATIVITY, // --a-- -> (--a)--
  .expType = Sts_MetaDeclarationExpressionType_DEC,
};


typedef enum LexemType {
  LexemType_VALUE,
  LexemType_OPERATOR,
  LexemType_PAREN_OPEN,
  LexemType_PAREN_CLOSE,
} LexemType;

typedef struct Lexem {
  LexemType type;
  union {
    Sts_MetaDeclarationValue decValue;
    WEAK(OpData*) opData;
  } value;
  Source src;
} Lexem;


void Lexem_free(Lexem* lexem) {
  Source_free(&lexem->src);

  // remove this, if logic is changed
  // Errors_internal_unexpectedBehavior(
  //   ViewString_of("Lexem_free(Lexem* lexem)"),
  //   ViewString_of("this function should not be run")
  // );
}


#define NAME Lexems
#define TYPE Lexem
#define NULLV (Lexem) {0}
#define FREEFUN Lexem_free
#include "glist.h"
#undef NAME
#undef TYPE
#undef NULLV
#undef FREEFUN

#define NAME Lexems
#define TYPE Lexem
#define NULLV (Lexem) {0}
#define FREEFUN Lexem_free
#include "glist.c.h"
#undef NAME
#undef TYPE
#undef NULLV
#undef FREEFUN


void registerDeclarationValue(Sts_MetaDeclarationsBlock* decBlock, Sts_MetaDeclarationValue* value) {
  if (value->type == Sts_MetaDeclarationValueType_LINK) {
    Sts_MetaDeclarationValuesLinks_registerDeclaratonValue(&decBlock->links, value);
  }
}

Lexem parseLexems_string(Sts_MetaDeclarationsBlock* decBlock, Sts_MetaParser_Context* ctx);
Lexem parseLexems_number(Sts_MetaDeclarationsBlock* decBlock, Sts_MetaParser_Context* ctx);
Lexem parseLexems_name(Sts_MetaDeclarationsBlock* decBlock, Sts_MetaParser_Context* ctx);
Lexem parseLexems_operator(Sts_MetaDeclarationsBlock* decBlock, Sts_MetaParser_Context* ctx);
Lexems parseLexems(Sts_MetaDeclarationsBlock* decBlock, Sts_MetaParser_Context* ctx, Source* expressionSource);
Sts_MetaDeclarationValue parseValue(Sts_MetaDeclarationsBlock* decBlock, Sts_MetaParser_Context* ctx);

typedef enum OpenType {
  OpenType_BODY,
  OpenType_VALUE,
  OpenType_SHORT_CLOSE,
} OpenType;

void parseDeclarations(Sts_MetaDeclarationsBlock* decBlock, Sts_MetaParser_Context* ctx);
static inline void parseDeclarations_name(Sts_MetaDeclarationsBlock* decBlock, Sts_MetaParser_Context* ctx, char c);
static inline void parseDeclarations_name_param(Sts_MetaDeclarationsBlock* decBlock, Sts_MetaParser_Context* ctx, Sts_MetaDeclarationValue nameDec, OpenType openType);

void parseDeclarations(Sts_MetaDeclarationsBlock* decBlock, Sts_MetaParser_Context* ctx) {
  Sts_MetaDeclarationsBlockType type = decBlock->type;
  char exitChar =
    type == Sts_MetaDeclarationsBlockType_TOKEN ? '}' :
    type == Sts_MetaDeclarationsBlockType_ZONE ? ')' :
    type == Sts_MetaDeclarationsBlockType_GROUP ? ')' :
    type == Sts_MetaDeclarationsBlockType_SUPER_TOKEN ? '}' :
    '\0';
  if (exitChar == '\0') {
    Errors_internal_unexpectedEnumType(ViewString_of("parseDeclarations().decBlock->type"));
    non_call_return;
  }
  
  while (true) {
    Utils_Iter_skipVoid(ctx, false);
    char c = Iter_currChar(&ctx->iter);

    if (Chars_isLetter(c) || c == '_') {
      parseDeclarations_name(decBlock, ctx, c);
    }
    else if (c == '$') {
      // TODO: variable
    }
    else if (c == '#') {
      Iter* iter = &ctx->iter;
      Iter_foreachChars(c, iter) {
        if (c == '\n') {
          Utils_Iter_skipVoid(ctx, false);
          break;
        }
      }
    }
    else if (c == exitChar || c == '\0') {
      break;
    }
    else {
      // TODO: ERROR
    }
  }
}
static inline void parseDeclarations_name(Sts_MetaDeclarationsBlock* decBlock, Sts_MetaParser_Context* ctx, char c) {
  String name = Utils_Iter_readName(ctx);
  Sts_MetaDeclarationValue nameDec;

  bool contains = StringList_contains(&decBlock->linkNames, ViewString_by(name));
  if (contains) {
    nameDec.type = Sts_MetaDeclarationValueType_LINK;
    nameDec.value.linkName = name;
  }
  else {
    nameDec.type = Sts_MetaDeclarationValueType_NAME;
    nameDec.value.name = name;
  }

  Utils_Iter_skipVoid(ctx, false);
  bool isGhost = Iter_currChar(&ctx->iter) == '!';
  if (isGhost) Iter_nextChar(&ctx->iter);
  Utils_Iter_skipVoid(ctx, false);
  c = Iter_currChar(&ctx->iter);

  OpenType openType;
  if (c == '{') openType = OpenType_BODY;
  else if (c == ':') openType = OpenType_VALUE;
  else if (c == ';') openType = OpenType_SHORT_CLOSE;
  else {
    Errors_metaparser_unknownToken(ctx, Source_byIter(
      ViewString_by(ctx->filename),
      &ctx->iter,
      SPD_new2_double(SPDMode_CURR_CHAR)
    ));
    return;
  }
  Iter_nextChar(&ctx->iter);

  ViewString vs_event = ViewString_of("event");
  ViewString vs_regex = ViewString_of("regex");
  if (ViewStrings_equals(ViewString_by(name), vs_event) && !contains) {
    if (openType == OpenType_BODY) {
      // TODO: events
    }
    else if (openType == OpenType_SHORT_CLOSE) {
      Iter_nextChar(&ctx->iter);
    }
    else {
      Errors_metaparser_anotherTokenExpected(ctx, Source_byIter(
        ViewString_by(ctx->filename),
        &ctx->iter,
        SPD_new1_double(SPDMode_BACK_CHAR_SHIFT, 1)
      ), ViewString_of("{"));
    }
  }
  else if (ViewStrings_equals(ViewString_by(name), vs_regex) && openType == OpenType_BODY && !contains) {
    // TODO: super regex
  }
  else { // default param
    parseDeclarations_name_param(decBlock, ctx, nameDec, openType);
  }
}
static inline void parseDeclarations_name_param(Sts_MetaDeclarationsBlock* decBlock, Sts_MetaParser_Context* ctx, Sts_MetaDeclarationValue nameDec, OpenType openType) {
  char c;
  Sts_MetaDeclaration* dec = A_xloc(sizeof(Sts_MetaDeclaration));
  *dec = (Sts_MetaDeclaration) {
    .type = Sts_MetaDeclarationType_PARAM,
  };
  Sts_MetaDeclarationValueList values;
  Sts_MetaDeclarationValueList_init(&values, 1);
  if (openType == OpenType_SHORT_CLOSE) { // short true
    Sts_MetaDeclarationValue trueValue = (Sts_MetaDeclarationValue) {
      .type = Sts_MetaDeclarationValueType_NUMBER,
      .value.number = 1,
    };
    Sts_MetaDeclarationValueList_add(&values, trueValue);
  }
  else if (openType == OpenType_VALUE) {
    do {
      Utils_Iter_skipVoid(ctx, false);

      Sts_MetaDeclarationValue valueDec = parseValue(decBlock, ctx);
      Sts_MetaDeclarationValue* valueDecPtr = Sts_MetaDeclarationValueList_add(&values, valueDec);
      registerDeclarationValue(decBlock, valueDecPtr);

      Utils_Iter_skipVoid(ctx, false);
      c = Iter_currChar(&ctx->iter);
      Iter_nextChar(&ctx->iter);
    } while (c == ',');
    if (c != ';') {
      Errors_metaparser_unknownToken(ctx, Source_byIter(
        ViewString_by(ctx->filename),
        &ctx->iter,
        SPD_new1_double(SPDMode_BACK_CHAR_SHIFT, 1)
      ));
    }
  }
  else {
    Errors_metaparser_anotherTokenExpected(ctx, Source_byIter(
      ViewString_by(ctx->filename),
      &ctx->iter,
      SPD_new1_double(SPDMode_BACK_CHAR_SHIFT, 1)
    ), ViewString_of("{"));
  }
  dec->value.param = (Sts_MetaParamDeclaration) {
    .name = nameDec,
    .values = values,
  };
  registerDeclarationValue(decBlock, &dec->value.param.name);
  Sts_MetaDeclarationList_add(&decBlock->declarations, dec);
}

// This is an extended version of the Pratt parser, which allows you to process operators that can be both `infix`, `posfix`, and `prefix' at the same time.
// in rare situations, it may not be O(n)
typedef struct PrattContext {
  Sts_MetaParser_Context* ctx;
  Sts_MetaDeclarationsBlock* decBlock;
  OWNER(Lexems*) lexems;
  size_t* currIndex;
  OWNER(Source) expressionSrc;
} PrattContext;
void PrattContext_free(PrattContext* prattContext) {
  Lexems_freeElements(prattContext->lexems);
  Lexems_free(prattContext->lexems);
  Source_free(&prattContext->expressionSrc);
}

Sts_MetaDeclarationValue pratt(PrattContext ctx, int minLbp);

typedef enum PrattCheckLeftResult {
  PrattCheckLeftResult_OK,
  PrattCheckLeftResult_PAREN_CLOSE,
  PrattCheckLeftResult_ERROR,
} PrattCheckLeftResult;
PrattCheckLeftResult pratt_checkLeft(PrattContext ctx, Sts_MetaDeclarationValue* retDecValue, Lexem* leftLexem);
Sts_MetaDeclarationValue pratt_loop(PrattContext ctx, int minLbp, Lexem* leftLexem, Sts_MetaDeclarationValue left);
Sts_MetaDeclarationValue pratt_prefix(PrattContext ctx, Lexem* op);
Sts_MetaDeclarationValue pratt_infix(PrattContext ctx, Lexem* op, Sts_MetaDeclarationValue left);
Sts_MetaDeclarationValue pratt_postfix(PrattContext ctx, Lexem* op, Sts_MetaDeclarationValue left);
Sts_MetaDeclarationValue pratt_infix_postfix(PrattContext ctx, Lexem* op, Sts_MetaDeclarationValue left, int minLbp);
Sts_MetaDeclarationValue pratt_paren(PrattContext ctx);


// main parse function. Parse left and run right parse looparse left and run right parse loop
Sts_MetaDeclarationValue pratt(PrattContext ctx, int minLbp) {
  Lexem* leftLexem = Lexems_get(ctx.lexems, *ctx.currIndex);
  if (!leftLexem) {
    Source expressionSrc = ctx.expressionSrc;
    Context* ctx1 = ctx.ctx;
    ctx.ctx = null;
    ctx.expressionSrc = (Source) {0};
    PrattContext_free(&ctx);
    Errors_metaparser_emptyExpression(ctx1, expressionSrc);
    non_call_return (Sts_MetaDeclarationValue) {};
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
PrattCheckLeftResult pratt_checkLeft(PrattContext ctx, Sts_MetaDeclarationValue* retDecValue, Lexem* leftLexem) {
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
Sts_MetaDeclarationValue pratt_loop(PrattContext ctx, int minLbp, Lexem* leftLexem, Sts_MetaDeclarationValue startLeft) {
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
    const OpData* opData = opLexem->value.opData;
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
Sts_MetaDeclarationValue pratt_prefix(PrattContext ctx, Lexem* op) {
  const OpData* opData = op->value.opData;
  Sts_MetaDeclarationValue right = pratt(ctx, opData->unaLbp + opData->right);
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
Sts_MetaDeclarationValue pratt_infix(PrattContext ctx, Lexem* op, Sts_MetaDeclarationValue left) {
  const OpData* opData = op->value.opData;
  *ctx.currIndex += 1;
  Sts_MetaDeclarationValue right = pratt(ctx, opData->binLbp + opData->right);
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
Sts_MetaDeclarationValue pratt_postfix(PrattContext ctx, Lexem* op, Sts_MetaDeclarationValue left) {
  const OpData* opData = op->value.opData;
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
Sts_MetaDeclarationValue pratt_infix_postfix(PrattContext ctx, Lexem* op, Sts_MetaDeclarationValue left, int minLbp) {
  const OpData* opData = op->value.opData;

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
Sts_MetaDeclarationValue pratt_paren(PrattContext ctx) {
  Sts_MetaDeclarationValue value = pratt(ctx, 0);
  *ctx.currIndex += 1;
  return value;
}


Sts_MetaDeclarationValue parseValue(Sts_MetaDeclarationsBlock* decBlock, Sts_MetaParser_Context* ctx) {
  Source expressionSrc;
  Lexems lexems = parseLexems(decBlock, ctx, &expressionSrc);
  size_t currIndex = 0;
  PrattContext prattContext = (PrattContext) {
    .ctx = ctx,
    .decBlock = decBlock,
    .lexems = &lexems,
    .currIndex = &currIndex,
    .expressionSrc = expressionSrc,
  };
  Sts_MetaDeclarationValue value = pratt(prattContext, 0);
  PrattContext_free(&prattContext);
  return value;
}



Lexems parseLexems(Sts_MetaDeclarationsBlock* decBlock, Sts_MetaParser_Context* ctx, Source* expressionSource) {
  Lexems lexems;
  Lexems_init(&lexems, 10);

  Iter* iter = &ctx->iter;
  
  Iter startIterClone = Iter_copy(iter);

  for (char c = Iter_currChar(iter); c != '\0'; c = Iter_currChar(iter)) {
    if (Chars_isLetter(c)) {
      Lexems_add(&lexems, parseLexems_name(decBlock, ctx));
    }
    else if (Chars_isDigit(c) || c == '.') {
      Lexems_add(&lexems, parseLexems_number(decBlock, ctx));
    }
    else if (c == '"') {
      Lexems_add(&lexems, parseLexems_string(decBlock, ctx));
    }
    else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '(' || c == ')') {
      Lexems_add(&lexems, parseLexems_operator(decBlock, ctx));
    }
    else if (Chars_isVoid(c)) {
      Utils_Iter_skipVoid(ctx, true);
    }
    else {
      break;
    }
    // else if (c == ';' || c == ',') {
  }
  *expressionSource = Source_byIters(
    ViewString_by(ctx->filename),
    &startIterClone, SPD_new2(SPDMode_CURR_CHAR),
    iter, SPD_new2(SPDMode_CURR_CHAR)
  );
  return lexems;
}
Lexem parseLexems_name(Sts_MetaDeclarationsBlock* decBlock, Sts_MetaParser_Context* ctx) {
  Iter startIterClone = Iter_copy(&ctx->iter);

  String name = Utils_Iter_readName(ctx);
  Sts_MetaDeclarationValue decValue;
  if (StringList_contains(&decBlock->linkNames, ViewString_by(name))) {
    decValue = (Sts_MetaDeclarationValue) {
      .type = Sts_MetaDeclarationValueType_LINK,
      .value = { .linkName = name },
    };
  }
  else {
    decValue = (Sts_MetaDeclarationValue) {
      .type = Sts_MetaDeclarationValueType_NAME,
      .value = { .name = name },
    };
  }

  Iter* iter = &ctx->iter;
  Utils_Iter_skipVoid(ctx, false);
  while (Iter_currChar(iter) == '.') {
    Iter_nextChar(iter);
    Utils_Iter_skipVoid(ctx, false);

    type_errno(String) name2 = Utils_Iter_readName(ctx);
    if (errno != 0) {
      Errors_metaparser_anotherTokenExpected(ctx, Source_byIter(
        ViewString_by(ctx->filename),
        iter,
        SPD_new1(SPDMode_BACK_WORD_SHIFT, 1),
        SPD_new2(SPDMode_CURR_CHAR)
      ), ViewString_of("<name>"));
    }

    Sts_MetaDeclarationValue name2DecValue;
    name2DecValue.type = Sts_MetaDeclarationValueType_NAME;
    name2DecValue.value.name = name2;

    Sts_MetaDeclarationExpression* expression = A_xloc(sizeof(Sts_MetaDeclarationExpression));
    expression->type = Sts_MetaDeclarationExpressionType_CHILD;
    expression->value1 = decValue;
    expression->value2 = name2DecValue;

    decValue.type = Sts_MetaDeclarationValueType_EXPRESSION;
    decValue.value.expression = expression;

    Utils_Iter_skipVoid(ctx, false);
  }

  Source lexemSrc = Source_byIters(
    ViewString_by(ctx->filename),
    &startIterClone, SPD_new2(SPDMode_CURR_CHAR),
    &ctx->iter, SPD_new1(SPDMode_BACK_CHAR_SHIFT, 1)
  );

  Lexem lexem = (Lexem) {
    .type = LexemType_VALUE,
    .value.decValue = decValue,
    .src = lexemSrc,
  };
  return lexem;
}
Lexem parseLexems_number(Sts_MetaDeclarationsBlock* decBlock, Sts_MetaParser_Context* ctx) {
  Iter startIterClone = Iter_copy(&ctx->iter);

  double number = Utils_Iter_readNumber(ctx);
  Sts_MetaDeclarationValue decValue;
  decValue.type = Sts_MetaDeclarationValueType_NUMBER;
  decValue.value.number = number;
  Source lexemSrc = Source_byIters(
    ViewString_by(ctx->filename),
    &startIterClone, SPD_new2(SPDMode_CURR_CHAR),
    &ctx->iter, SPD_new1(SPDMode_BACK_CHAR_SHIFT, 1)
  );
  return (Lexem) {
    .type = LexemType_VALUE,
    .value = { .decValue = decValue },
    .src = lexemSrc,
  };
}
Lexem parseLexems_string(Sts_MetaDeclarationsBlock* decBlock, Sts_MetaParser_Context* ctx) {
  Iter* iter = &ctx->iter;
  Iter startIterClone = Iter_copy(iter);

  Iter_nextChar(iter);
  String string = Utils_Iter_readString(ctx);
  Sts_MetaDeclarationValue decValue;
  decValue.type = Sts_MetaDeclarationValueType_STRING;
  decValue.value.string = string;
  Source lexemSrc = Source_byIters(
    ViewString_by(ctx->filename),
    &startIterClone, SPD_new2(SPDMode_CURR_CHAR),
    &ctx->iter, SPD_new1(SPDMode_BACK_CHAR_SHIFT, 1)
  );
  return (Lexem) {
    .type = LexemType_VALUE,
    .value = { .decValue = decValue },
    .src = lexemSrc,
  };
}

Lexem parseLexems_operator(Sts_MetaDeclarationsBlock* decBlock, Sts_MetaParser_Context* ctx) {
  Iter* iter = &ctx->iter;
  Iter startIterClone = Iter_copy(iter);
  char c = Iter_currChar(iter);
  char c1 = Iter_nextChar(iter);

  LexemType type;
  OpData* opData;
  if (c == '+') {
    if (c1 == '+') {
      Iter_nextChar(iter);
      type = LexemType_OPERATOR;
      opData = &OpData_INC;
    }
    else {
      type = LexemType_OPERATOR;
      opData = &OpData_SUM;
    }
  }
  else if (c == '-') {
    if (c1 == '-') {
      Iter_nextChar(iter);
      type = LexemType_OPERATOR;
      opData = &OpData_DEC;
    }
    else {
      type = LexemType_OPERATOR;
      opData = &OpData_SUB;
    }
  }
  else if (c == '*') {
    if (c1 == '*') {
      Iter_nextChar(iter);
      type = LexemType_OPERATOR;
      opData = &OpData_POW;
    }
    else {
      type = LexemType_OPERATOR;
      opData = &OpData_MUL;
    }
  }
  else if (c == '/') {
    type = LexemType_OPERATOR;
    opData = &OpData_DIV;
  }
  else if (c == '%') {
    type = LexemType_OPERATOR;
    opData = &OpData_MOD;
  }
  else if (c == '(') {
    type = LexemType_PAREN_OPEN;
    opData = null;
  }
  else if (c == ')') {
    type = LexemType_PAREN_CLOSE;
    opData = null;
  }
  else {
    Errors_metaparser_unknownToken(ctx, Source_byIter(
      ViewString_by(ctx->filename), &ctx->iter, SPD_new2_double(SPDMode_CURR_CHAR)
    ));
    non_call_return (Lexem) {};
  }
  Source lexemSrc = Source_byIters(
    ViewString_by(ctx->filename),
    &startIterClone, SPD_new2(SPDMode_CURR_CHAR),
    &ctx->iter, SPD_new1(SPDMode_BACK_CHAR_SHIFT, 1)
  );
  return (Lexem) {
    .type = type,
    .value = { .opData = opData },
    .src = lexemSrc,
  };
}
