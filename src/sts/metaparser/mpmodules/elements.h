#pragma once

#include "metaparser.h"

void parseRegexLink(Sts_MetaParser_Context* ctx, Sts_MetaNamespaceDeclaration* namespaceDec);
void parseSetMainZone(Sts_MetaParser_Context* ctx, Sts_MetaNamespaceDeclaration* namespaceDec);
void parseZone(Sts_MetaParser_Context* ctx, Sts_MetaNamespaceDeclaration* namespaceDec);
void parseToken(Sts_MetaParser_Context* ctx, Sts_MetaNamespaceDeclaration* namespaceDec);
void parseGroup(Sts_MetaParser_Context* ctx, Sts_MetaNamespaceDeclaration* namespaceDec);
