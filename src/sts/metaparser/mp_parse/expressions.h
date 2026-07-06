#pragma once

#include "metaparser.h"

Sts_MetaDeclarationValue Expressions_parseValue(Sts_MetaParser_Context* ctx, ViewString exitChars);
Sts_MetaDeclarationValue Expressions_parseStatements(Sts_MetaParser_Context* ctx, ViewString exitChars);
