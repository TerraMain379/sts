#pragma once

#include "lexems.h"
#include "metaparser.h"
#include "allocator.h"
#include "metablocks.h"
#include "mp_parse/lexems.h"
#include "sources.h"

// This is an extended version of the Pratt parser, which allows you to process operators that can be both `infix`, `posfix`, and `prefix' at the same time.
// in rare situations, it may not be O(n)

typedef struct Pratt_Context {
  Sts_MetaParser_Context* ctx;
  OWNER(Lexems*) lexems;
  size_t* currIndex;
  OWNER(Source) expressionSrc;
} Pratt_Context;
void Pratt_Context_free(Pratt_Context* prattContext);


Sts_MetaDeclarationValue Pratt_pratt(Pratt_Context ctx, int minLbp);
