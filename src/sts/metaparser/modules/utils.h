#include "iter.h"
#include "metablocks.h"
#include "metaparser.h"
typedef Sts_MetaParser_Context Context;

String readName(Context* ctx);
void skipVoid(Context* ctx);
void readChar(Context* ctx, char c);

typedef struct Param Param;

#define PNAME Params
#define PTYPE Param
#include "plist.h"
#undef PNAME
#undef PTYPE

Params readParams(Context* ctx);
