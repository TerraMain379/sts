#include "expressions.h"

#include "mp_parse/pratt.h"

Sts_MetaDeclarationValue Expressions_parseValue(Sts_MetaParser_Context* ctx, ViewString exitChars) {
  Source expressionSrc;
  Lexems lexems = Lexems_parseLexems(
    ctx,
    (Lexems_ParseSettings) {
      .available = {
        .assign = false,
        .statements = false,
        .blocks = false,
        .keyword_of = false,
        .increments = true,
        .semicolon = false,
      },
      .exitChars = exitChars
    },
    &expressionSrc
  );
  size_t currIndex = 0;
  Pratt_Context prattContext = (Pratt_Context) {
    .ctx = ctx,
    .lexems = &lexems,
    .currIndex = &currIndex,
    .expressionSrc = expressionSrc,
  };
  Sts_MetaDeclarationValue value = Pratt_pratt(prattContext, 0);
  Pratt_Context_free(&prattContext);
  return value;
}

Sts_MetaDeclarationValue Expressions_parseStatements(Sts_MetaParser_Context* ctx, ViewString exitChars) {
  Source expressionSrc;
  Lexems lexems = Lexems_parseLexems(
    ctx,
    (Lexems_ParseSettings) { 
      .available = {
        .assign = true,
        .statements = true,
        .blocks = true,
        .keyword_of = false,
        .increments = true,
        .semicolon = true,
      },
      .exitChars = exitChars
    },
    &expressionSrc
  );
  size_t currIndex = 0;
  Pratt_Context prattContext = (Pratt_Context) {
    .ctx = ctx,
    .lexems = &lexems,
    .currIndex = &currIndex,
    .expressionSrc = expressionSrc,
  };
  // TODO: rewrite for statements
  Sts_MetaDeclarationValue value = Pratt_pratt(prattContext, 0);
  Pratt_Context_free(&prattContext);
  return value;
}
