#include "metablocks.h"
#include "string.h"
#include "iter.h"
#include "metaparser.h"

typedef struct Context {
  MUT_BORROW(Sts_MetaFile) metaFile;
  Iter iter;
  BORROW(Sts_MetaParser_Arguments) args;
} Context;
