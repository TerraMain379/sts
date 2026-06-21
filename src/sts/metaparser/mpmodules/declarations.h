#pragma once

#include "metaparser.h"

void Declarations_parseDeclarationHead(Sts_MetaDeclarationHead* head, Sts_MetaParser_Context* ctx, char exitChar);
void Declarations_parseDeclarations(Sts_MetaDeclarationHead* head, Sts_MetaLineDeclarationList* declarations, Sts_MetaParser_Context* ctx, char exitChar);
