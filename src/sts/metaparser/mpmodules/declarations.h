#pragma once

#include "metaparser.h"

void Declarations_parseDeclarationsBlockHeader(Sts_MetaDeclarationsBlock* decBlock, Sts_MetaParser_Context* ctx, OWNER(String) name, char exitChar);
void Declarations_parseDeclarations(Sts_MetaDeclarationsBlock* decBlock, Sts_MetaParser_Context* ctx, char exitChar);
