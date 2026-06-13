#include "expressions.h"

#include "pratt.h"

Sts_MetaDeclarationValue parseValue(Sts_MetaDeclarationsBlock* decBlock, Sts_MetaParser_Context* ctx, ViewString exitChars) {
  Source expressionSrc;
  Lexems lexems = Lexems_parseLexems(
    decBlock, ctx,
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
