#pragma once

#include "metaparser.h"
#include "mp_parse/elements.h"

void parseNamespace(Sts_MetaParser_Context* ctx, Sts_MetaNamespaceDeclaration* parentNamespaceDec);
void parseNamespaceBody(Sts_MetaParser_Context* ctx, Sts_MetaNamespaceDeclaration* namespaceDec, bool isRootSpace);
