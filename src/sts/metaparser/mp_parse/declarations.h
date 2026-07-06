#pragma once

#include "metaparser.h"

size_t Declarations_parseDeclarationHead(Sts_MetaDeclarationHead* head, Sts_MetaParser_Context* ctx, char exitChar);
void Declarations_parseDeclarations(Sts_MetaLineDeclarationList* declarations, Sts_MetaParser_Context* ctx, char exitChar);
