#include "metablocks.h"
#include "metaparser/iter/iter.h"

typedef struct Sts_MetaParserArguments {
  // TODO:
} Sts_MetaParserArguments;
void Sts_MetaParserArguments_init(Sts_MetaParserArguments* arguments);

typedef struct Sts_MetaParser_Context {
  Sts_MetaFile* metaFile;
  const String input;
  Iter iter;
  Sts_MetaParserArguments* args;
} Sts_MetaParser_Context;

void Sts_MetaParser_parse(Sts_MetaFile* metaFile, Iter* iter, Sts_MetaParserArguments* args);
