#include "mpmodules/lexems.h"

#include "mpmodules/utils.h"
#include "metaparser_errors.h"
#include "stringbuilder.h"

Lexem_OpData Lexem_OpData_ASSIGN = (Lexem_OpData) {
  .isInfix = true,
  .isPrefix = false,
  .isPostfix = false,
  .binLbp = -50,
  .right = Lexem_OpData_RIGHT_ASSOCIATIVITY, // a=b=c -> a=(b=c)
  .expType = Sts_MetaDeclarationExpressionType_ASSIGN,
};

Lexem_OpData Lexem_OpData_SUM = (Lexem_OpData) { // +
  .isInfix = true,
  .isPrefix = true,
  .isPostfix = false,
  .binLbp = 110,
  .unaLbp = 130,
  .right = Lexem_OpData_LEFT_ASSOCIATIVITY,
  .expType = Sts_MetaDeclarationExpressionType_SUM,
};
Lexem_OpData Lexem_OpData_SUB = (Lexem_OpData) { // -
  .isInfix = true,
  .isPrefix = true,
  .isPostfix = false,
  .binLbp = 110,
  .unaLbp = 130,
  .right = Lexem_OpData_LEFT_ASSOCIATIVITY,
  .expType = Sts_MetaDeclarationExpressionType_SUB,
};
Lexem_OpData Lexem_OpData_MUL = (Lexem_OpData) { // *
  .isInfix = true,
  .isPrefix = false,
  .isPostfix = false,
  .binLbp = 120,
  .right = Lexem_OpData_LEFT_ASSOCIATIVITY,
  .expType = Sts_MetaDeclarationExpressionType_MUL,
};
Lexem_OpData Lexem_OpData_DIV = (Lexem_OpData) { // /
  .isInfix = true,
  .isPrefix = false,
  .isPostfix = false,
  .binLbp = 120,
  .right = Lexem_OpData_LEFT_ASSOCIATIVITY,
  .expType = Sts_MetaDeclarationExpressionType_DIV,
};
Lexem_OpData Lexem_OpData_MOD = (Lexem_OpData) { // %
  .isInfix = true,
  .isPrefix = false,
  .isPostfix = false,
  .binLbp = 120,
  .right = Lexem_OpData_LEFT_ASSOCIATIVITY,
  .expType = Sts_MetaDeclarationExpressionType_MOD,
};
Lexem_OpData Lexem_OpData_POW = (Lexem_OpData) { // **
  .isInfix = true,
  .isPrefix = false,
  .isPostfix = false,
  .binLbp = 140,
  .right = Lexem_OpData_RIGHT_ASSOCIATIVITY,
  .expType = Sts_MetaDeclarationExpressionType_POW,
};

Lexem_OpData Lexem_OpData_NOT = (Lexem_OpData) { // !
  .isInfix = false,
  .isPrefix = true,
  .isPostfix = false,
  .unaLbp = 150,
  .expType = Sts_MetaDeclarationExpressionType_NOT,
};
Lexem_OpData Lexem_OpData_INC = (Lexem_OpData) { // ++
  .isInfix = false,
  .isPrefix = true,
  .isPostfix = true,
  .unaLbp = 200,
  .right = Lexem_OpData_LEFT_ASSOCIATIVITY, // ++a++ -> (++a)++
  .expType = Sts_MetaDeclarationExpressionType_INC,
};
Lexem_OpData Lexem_OpData_DEC = (Lexem_OpData) { // --
  .isInfix = false,
  .isPrefix = true,
  .isPostfix = true,
  .unaLbp = 200,
  .right = Lexem_OpData_LEFT_ASSOCIATIVITY, // --a-- -> (--a)--
  .expType = Sts_MetaDeclarationExpressionType_DEC,
};

Lexem_OpData Lexem_OpData_LOGICAL_OR = (Lexem_OpData) { // ||
  .isInfix = true,
  .isPrefix = false,
  .isPostfix = false,
  .binLbp = 10,
  .right = Lexem_OpData_LEFT_ASSOCIATIVITY,
  .expType = Sts_MetaDeclarationExpressionType_LOGICAL_OR,
};
Lexem_OpData Lexem_OpData_LOGICAL_AND = (Lexem_OpData) { // &&
  .isInfix = true,
  .isPrefix = false,
  .isPostfix = false,
  .binLbp = 20,
  .right = Lexem_OpData_LEFT_ASSOCIATIVITY,
  .expType = Sts_MetaDeclarationExpressionType_LOGICAL_AND,
};
Lexem_OpData Lexem_OpData_BITWISE_OR = (Lexem_OpData) { // |
  .isInfix = true,
  .isPrefix = false,
  .isPostfix = false,
  .binLbp = 30,
  .right = Lexem_OpData_LEFT_ASSOCIATIVITY,
  .expType = Sts_MetaDeclarationExpressionType_BITWISE_OR,
};
Lexem_OpData Lexem_OpData_BITWISE_XOR = (Lexem_OpData) { // ^
  .isInfix = true,
  .isPrefix = false,
  .isPostfix = false,
  .binLbp = 40,
  .right = Lexem_OpData_LEFT_ASSOCIATIVITY,
  .expType = Sts_MetaDeclarationExpressionType_BITWISE_XOR,
};
Lexem_OpData Lexem_OpData_BITWISE_AND = (Lexem_OpData) { // &
  .isInfix = true,
  .isPrefix = false,
  .isPostfix = false,
  .binLbp = 50,
  .right = Lexem_OpData_LEFT_ASSOCIATIVITY,
  .expType = Sts_MetaDeclarationExpressionType_BITWISE_AND,
};

Lexem_OpData Lexem_OpData_LOGICAL_EQL = (Lexem_OpData) { // ==
  .isInfix = true,
  .isPrefix = false,
  .isPostfix = false,
  .binLbp = 60,
  .right = Lexem_OpData_LEFT_ASSOCIATIVITY,
  .expType = Sts_MetaDeclarationExpressionType_LOGICAL_EQL,
};
Lexem_OpData Lexem_OpData_LOGICAL_NOT_EQL = (Lexem_OpData) { // !=
  .isInfix = true,
  .isPrefix = false,
  .isPostfix = false,
  .binLbp = 60,
  .right = Lexem_OpData_LEFT_ASSOCIATIVITY,
  .expType = Sts_MetaDeclarationExpressionType_LOGICAL_NOT_EQL,
};
Lexem_OpData Lexem_OpData_LOGICAL_GT = (Lexem_OpData) { // >
  .isInfix = true,
  .isPrefix = false,
  .isPostfix = false,
  .binLbp = 70,
  .right = Lexem_OpData_LEFT_ASSOCIATIVITY,
  .expType = Sts_MetaDeclarationExpressionType_LOGICAL_GT,
};
Lexem_OpData Lexem_OpData_LOGICAL_LT = (Lexem_OpData) { // <
  .isInfix = true,
  .isPrefix = false,
  .isPostfix = false,
  .binLbp = 70,
  .right = Lexem_OpData_LEFT_ASSOCIATIVITY,
  .expType = Sts_MetaDeclarationExpressionType_LOGICAL_LT,
};
Lexem_OpData Lexem_OpData_LOGICAL_GTE = (Lexem_OpData) { // >=
  .isInfix = true,
  .isPrefix = false,
  .isPostfix = false,
  .binLbp = 70,
  .right = Lexem_OpData_LEFT_ASSOCIATIVITY,
  .expType = Sts_MetaDeclarationExpressionType_LOGICAL_GTE,
};
Lexem_OpData Lexem_OpData_LOGICAL_LTE = (Lexem_OpData) { // <=
  .isInfix = true,
  .isPrefix = false,
  .isPostfix = false,
  .binLbp = 70,
  .right = Lexem_OpData_LEFT_ASSOCIATIVITY,
  .expType = Sts_MetaDeclarationExpressionType_LOGICAL_LTE,
};

Lexem_OpData Lexem_OpData_TERN_COND_IF = (Lexem_OpData) { // ?
  .isInfix = true,
  .isPrefix = false,
  .isPostfix = false,
  .binLbp = -30,
  .right = Lexem_OpData_RIGHT_ASSOCIATIVITY,
  .expType = Sts_MetaDeclarationExpressionType_TERN_COND_IF,
};
Lexem_OpData Lexem_OpData_TERN_COND_ELSE = (Lexem_OpData) { // :
  .isInfix = true,
  .isPrefix = false,
  .isPostfix = false,
  .binLbp = -40,
  .right = Lexem_OpData_LEFT_ASSOCIATIVITY,
  .expType = Sts_MetaDeclarationExpressionType_TERN_COND_ELSE,
};



void Lexem_free(Lexem* lexem) {
  Source_free(&lexem->src);
}

#define NAME Lexems
#define TYPE Lexem
#define NULLV (Lexem) {0}
#define FREEFUN Lexem_free
#include "glist.c.h"
#undef NAME
#undef TYPE
#undef NULLV
#undef FREEFUN


Lexem parseLexems_string(Sts_MetaDeclarationsBlock* decBlock, Sts_MetaParser_Context* ctx);
Lexem parseLexems_number(Sts_MetaDeclarationsBlock* decBlock, Sts_MetaParser_Context* ctx);
Lexem parseLexems_name(Sts_MetaDeclarationsBlock* decBlock, Sts_MetaParser_Context* ctx, Lexems_ParseSettings settings);
Lexem parseLexems_operator(Sts_MetaDeclarationsBlock* decBlock, Sts_MetaParser_Context* ctx, Lexems_ParseSettings settings);

Lexems Lexems_parseLexems(Sts_MetaDeclarationsBlock* decBlock, Sts_MetaParser_Context* ctx, Lexems_ParseSettings settings, Source* retExpressionSource) {
  Lexems lexems;
  Lexems_init(&lexems, 10);

  Iter* iter = &ctx->iter;
  
  Iter startIterClone = Iter_copy(iter);

  for (char c = Iter_currChar(iter);; c = Iter_currChar(iter)) {
    bool flag = true;
    for (size_t i = 0; i < settings.exitChars.size; i++) {
      if (c == settings.exitChars.buffer[i]) {
        flag = false;
        break;
      }
    }
    if (!flag) break;

    if (Chars_isLetter(c)) {
      Lexems_add(&lexems, parseLexems_name(decBlock, ctx, settings));
    }
    else if (Chars_isDigit(c) || c == '.') {
      Lexems_add(&lexems, parseLexems_number(decBlock, ctx));
    }
    else if (c == '"') {
      Lexems_add(&lexems, parseLexems_string(decBlock, ctx));
    }
    else if (Chars_isVoid(c)) {
      Utils_Iter_skipVoid(ctx, true);
    }
    else if (c == '\0') {
      Errors_metaparser_unexpectedEnd(ctx, Source_byIters(
        ViewString_by(ctx->filename),
        &startIterClone,
        SPD_new1(SPDMode_BACK_CHAR_SHIFT, 1),
        iter,
        SPD_new2(SPDMode_CURR_CHAR)
      ));
      non_call_return (Lexems) {};
    }
    else {
      Lexems_add(&lexems, parseLexems_operator(decBlock, ctx, settings));
    }
  }
  *retExpressionSource = Source_byIters(
    ViewString_by(ctx->filename),
    &startIterClone, SPD_new1(SPDMode_BACK_CHAR_SHIFT, 1),
    iter, SPD_new2(SPDMode_CURR_CHAR)
  );
  return lexems;
}
Lexem parseLexems_name(Sts_MetaDeclarationsBlock* decBlock, Sts_MetaParser_Context* ctx, Lexems_ParseSettings settings) {
  Iter* iter = &ctx->iter;
  Iter startIterClone = Iter_copy(iter);

  String name = Utils_Iter_readName(ctx);

  ViewString vname = ViewString_by(name);
  LexemType type = LexemType_NULL;
  bool restrictValue = true;
  if (ViewStrings_equals(vname, ViewString_of("if"))) {
    type = LexemType_STATEMENT_IF;
    restrictValue = settings.available.statements;
  }
  else if (ViewStrings_equals(vname, ViewString_of("else"))) {
    type = LexemType_STATEMENT_ELSE;
    restrictValue = settings.available.statements;
  }
  else if (ViewStrings_equals(vname, ViewString_of("for"))) {
    type = LexemType_STATEMENT_FOR;
    restrictValue = settings.available.statements;
  }
  else if (ViewStrings_equals(vname, ViewString_of("foreach"))) {
    type = LexemType_STATEMENT_FOREACH;
    restrictValue = settings.available.statements;
  }
  else if (ViewStrings_equals(vname, ViewString_of("of"))) {
    type = LexemType_STATEMENT_FOREACH;
    restrictValue = settings.available.keyword_of;
  }

  if (type != LexemType_NULL) {
    if (!restrictValue) {
      Errors_metaparser_tokenNotAvailableHere(ctx, Source_byIter(
        ViewString_by(ctx->filename), &ctx->iter, SPD_new2_double(SPDMode_CURR_CHAR)
      ), ViewString_of("ASSIGN operator is disabled here"));
      non_call_return (Lexem) {};
    }
    return (Lexem) {
      .type = type,
      .src = Source_byIters(
        ViewString_by(ctx->filename),
        &startIterClone, SPD_new2(SPDMode_CURR_CHAR),
        &ctx->iter, SPD_new1(SPDMode_BACK_CHAR_SHIFT, 1)
      ),
    };
  }


  Sts_MetaDeclarationValue leftValue = {
    .type = Sts_MetaDeclarationValueType_NULL
  };
  do {
    Sts_MetaDeclarationValue nameValue;
    if (StringList_contains(&decBlock->linkNames, vname)) {
      nameValue = (Sts_MetaDeclarationValue) {
        .type = Sts_MetaDeclarationValueType_LINK,
        .value = { .linkName = name },
      };
    }
    else {
      nameValue = (Sts_MetaDeclarationValue) {
        .type = Sts_MetaDeclarationValueType_NAME,
        .value = { .name = name },
      };
    }

    if (leftValue.type != Sts_MetaDeclarationValueType_NULL) {
      Sts_MetaDeclarationExpression* expression = A_xloc(sizeof(Sts_MetaDeclarationExpression));
      expression->type = Sts_MetaDeclarationExpressionType_CHILD;
      expression->value1 = leftValue;
      expression->value2 = nameValue;

      leftValue.type = Sts_MetaDeclarationValueType_EXPRESSION;
      leftValue.value.expression = expression;
    }
    else {
      leftValue = nameValue;
    }

    Utils_Iter_skipVoid(ctx, false);
    if (Iter_currChar(iter) == '.') {
      Iter_nextChar(iter);
      Utils_Iter_skipVoid(ctx, false);
      type_errno(name) = Utils_Iter_readName(ctx);
      if (errno != 0) {
        Errors_metaparser_anotherTokenExpected(ctx, Source_byIter(
          ViewString_by(ctx->filename),
          iter, SPD_new2_double(SPDMode_CURR_CHAR)
        ), ViewString_of("<name>"));
        non_call_return (Lexem) {};
      }
      vname = ViewString_by(name);
    }
    else break;
  } while (true);

  Lexem lexem = (Lexem) {
    .type = LexemType_VALUE,
    .value = {
      .decValue = leftValue
    },
    .src = Source_byIters(
      ViewString_by(ctx->filename),
      &startIterClone, SPD_new2(SPDMode_CURR_CHAR),
      &ctx->iter, SPD_new1(SPDMode_BACK_CHAR_SHIFT, 1)
    ),
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
Lexem parseLexems_operator(Sts_MetaDeclarationsBlock* decBlock, Sts_MetaParser_Context* ctx, Lexems_ParseSettings settings) {
  Iter* iter = &ctx->iter;
  Iter startIterClone = Iter_copy(iter);
  char c = Iter_currChar(iter);
  char c1 = Iter_nextChar(iter);

  LexemType type;
  Lexem_OpData* opData;
  ViewString errorLexemName;
  if (c == '+') {
    type = LexemType_OPERATOR;
    if (c1 == '+') {
      Iter_nextChar(iter);
      if (!settings.available.increments) {
        errorLexemName = ViewString_of("INC");
        goto tokenNotAvailableHere;
      }
      opData = &Lexem_OpData_INC;
    }
    else {
      opData = &Lexem_OpData_SUM;
    }
  }
  else if (c == '-') {
    type = LexemType_OPERATOR;
    if (c1 == '-') {
      Iter_nextChar(iter);
      if (!settings.available.increments) {
        errorLexemName = ViewString_of("DEC");
        goto tokenNotAvailableHere;
      }
      opData = &Lexem_OpData_DEC;
    }
    else {
      opData = &Lexem_OpData_SUB;
    }
  }
  else if (c == '*') {
    type = LexemType_OPERATOR;
    if (c1 == '*') {
      Iter_nextChar(iter);
      opData = &Lexem_OpData_POW;
    }
    else {
      opData = &Lexem_OpData_MUL;
    }
  }
  else if (c == '/') {
    type = LexemType_OPERATOR;
    opData = &Lexem_OpData_DIV;
  }
  else if (c == '%') {
    type = LexemType_OPERATOR;
    opData = &Lexem_OpData_MOD;
  }
  else if (c == '(') {
    type = LexemType_PAREN_OPEN;
    opData = null;
  }
  else if (c == ')') {
    type = LexemType_PAREN_CLOSE;
    opData = null;
  }
  else if (c == '=') {
    type = LexemType_OPERATOR;
    if (c1 == '=') {
      Iter_nextChar(iter);
      opData = &Lexem_OpData_LOGICAL_EQL;
    }
    else {
      if (!settings.available.assign) {
        errorLexemName = ViewString_of("ASSIGN");
        goto tokenNotAvailableHere;
      }
      opData = &Lexem_OpData_ASSIGN;
    }
  }
  else if (c == '!') {
    type = LexemType_OPERATOR;
    if (c1 == '=') {
      Iter_nextChar(iter);
      opData = &Lexem_OpData_LOGICAL_NOT_EQL;
    }
    else {
      opData = &Lexem_OpData_NOT;
    }
  }
  else if (c == '>') {
    type = LexemType_OPERATOR;
    if (c1 == '=') {
      Iter_nextChar(iter);
      opData = &Lexem_OpData_LOGICAL_GTE;
    }
    else {
      opData = &Lexem_OpData_LOGICAL_GT;
    }
  }
  else if (c == '<') {
    type = LexemType_OPERATOR;
    if (c1 == '=') {
      Iter_nextChar(iter);
      opData = &Lexem_OpData_LOGICAL_LTE;
    }
    else {
      opData = &Lexem_OpData_LOGICAL_LT;
    }
  }
  else if (c == '?') {
    type = LexemType_OPERATOR;
    opData = &Lexem_OpData_TERN_COND_IF;
  }
  else if (c == ':') {
    type = LexemType_OPERATOR;
    opData = &Lexem_OpData_TERN_COND_ELSE;
  }
  else if (c == '|') {
    type = LexemType_OPERATOR;
    if (c1 == '|') {
      Iter_nextChar(iter);
      opData = &Lexem_OpData_LOGICAL_OR;
    }
    else {
      opData = &Lexem_OpData_BITWISE_OR;
    }
  }
  else if (c == '&') {
    type = LexemType_OPERATOR;
    if (c1 == '&') {
      Iter_nextChar(iter);
      opData = &Lexem_OpData_LOGICAL_AND;
    }
    else {
      opData = &Lexem_OpData_BITWISE_AND;
    }
  }
  else if (c == '^') {
    type = LexemType_OPERATOR;
    opData = &Lexem_OpData_BITWISE_XOR;
  }
  else if (c == ';') {
    if (!settings.available.semicolon) {
      errorLexemName = ViewString_of("SEMICOLON");
      goto tokenNotAvailableHere;
    }
    type = LexemType_SEMICOLON;
    opData = null;
  }
  else if (c == '{') {
    if (!settings.available.blocks) {
      errorLexemName = ViewString_of("CODE_BLOCK_OPEN");
      goto tokenNotAvailableHere;
    }
    type = LexemType_BLOCK_OPEN;
    opData = null;
  }
  else if (c == '}') {
    if (!settings.available.blocks) {
      errorLexemName = ViewString_of("CODE_BLOCK_CLOSE");
      goto tokenNotAvailableHere;
    }
    type = LexemType_BLOCK_CLOSE;
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

  tokenNotAvailableHere: {
    Source lexemSrc = Source_byIters(
      ViewString_by(ctx->filename),
      &startIterClone, SPD_new2(SPDMode_CURR_CHAR),
      &ctx->iter, SPD_new1(SPDMode_BACK_CHAR_SHIFT, 1)
    );
    StringBuilder reasonBuilder;
    StringBuilder_init(&reasonBuilder);
    StringBuilder_addString(&reasonBuilder, errorLexemName);
    StringBuilder_addCharBuffer(&reasonBuilder, " operator is disabled here");
    String reason = StringBuilder_take(&reasonBuilder);
    String_moveToStack(reason);

    Errors_metaparser_tokenNotAvailableHere(
      ctx, lexemSrc, 
      ViewString_by(reason)
    );
    non_call_return (Lexem) {};
  }
}
