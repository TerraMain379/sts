#include "metablocks.h"
#include "iter.h"
#include "string.h"

typedef struct Sts_MetaParser_Arguments {
  // TODO: write params for parser
} Sts_MetaParser_Arguments;
void Sts_MetaParser_Arguments_init(Sts_MetaParser_Arguments* arguments);
void Sts_MetaParser_Arguments_free(Sts_MetaParser_Arguments* arguments);

void Sts_MetaParser_parse(MUT_BORROW(Sts_MetaFile) metaFile, Iter iter, BORROW(Sts_MetaParser_Arguments) args);


typedef struct Sts_MetaParser_Context {
  MUT_BORROW(Sts_MetaFile) metaFile;
  Iter iter;
  BORROW(Sts_MetaParser_Arguments) args;
} Sts_MetaParser_Context;
