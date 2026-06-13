#pragma once

#include "lexems.h"
#include "metaparser.h"
#include "allocator.h"
#include "metablocks.h"
#include "mpmodules/lexems.h"
#include "sources.h"

// This is an extended version of the Pratt parser, which allows you to process operators that can be both `infix`, `posfix`, and `prefix' at the same time.
// in rare situations, it may not be O(n)

typedef struct PrattContext {
  Sts_MetaParser_Context* ctx;
  Sts_MetaDeclarationsBlock* decBlock;
  OWNER(Lexems*) lexems;
  size_t* currIndex;
  OWNER(Source) expressionSrc;
} PrattContext;
void PrattContext_free(PrattContext* prattContext);


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
