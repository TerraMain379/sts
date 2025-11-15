#include "metablocks.h"
#include "iter.h"

typedef struct Sts_MetaParser_Context {
  Sts_MetaFile* metaFile;
  Iter* iter;
  Sts_MetaParserArguments* args;
} Sts_MetaParser_Context;

void Sts_MetaParser_parse(Sts_MetaFile* metaFile, Iter* iter, Sts_MetaParserArguments* args);
