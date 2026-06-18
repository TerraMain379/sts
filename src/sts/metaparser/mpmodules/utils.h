#pragma once

#include "metaparser.h"
#include "strings.h"

#define Context Sts_MetaParser_Context

type_errno(String) Utils_Iter_readName(Context* ctx);
void Utils_Iter_skipVoid(Context* ctx, bool strict);
void_stop Utils_Iter_skipChar(Context* ctx, char c);
String Utils_Iter_readString(Context* ctx);
double Utils_Iter_readNumber(Context* ctx);

