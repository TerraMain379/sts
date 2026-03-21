#include "modules/setmainzone.h"

#include "metablocks.h"

void parseSetMainZone(Context* ctx) {
  String name = Utils_Iter_readName(ctx);
  Utils_Iter_readChar(ctx, '-');

  Sts_MetaZone mainZone = Sts_MetaFile_getOrCreateZone(metaFile, name);
  ctx->metaFile->mainZone = mainZone;
  String_free(name);
}
