#include "metaparser.h"
#include "strings.h"

#define Context Sts_MetaParser_Context

String Utils_Iter_readName(Context* ctx);
void Utils_Iter_skipVoid(Context* ctx, bool strict);
void Utils_Iter_readChar(Context* ctx, char c);
String Utils_Iter_readString(Context* ctx);

