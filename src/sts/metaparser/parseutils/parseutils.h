#include "metaparser_ctx.h"
#include "metaparser.h"
#include "iter.h"

String readName(Context* ctx);
void skipVoid(Context* ctx);
void readChar(Context* ctx, char c);

typedef struct Sts_MetaBodyLine {
  Sts_MetaBodyLineType type;
} Sts_MetaBodyLine;

typedef enum Sts_MetaBodyLineType {
  Sts_MetaBodyLineType_Param,
  Sts_MetaBodyLineType_Variable,
  Sts_MetaBodyLineType_Events,
} Sts_MetaBodyLineType;
