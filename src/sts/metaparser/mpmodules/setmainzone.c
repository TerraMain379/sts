#include "mpmodules/setmainzone.h"

#include "metablocks.h"
#include "mpmodules/utils.h"

void parseSetMainZone(Context* ctx) {
  String name = Utils_Iter_readName(ctx);
  Utils_Iter_readChar(ctx, '-');

  Sts_MetaZone* mainZone = Sts_MetaFile_getOrCreateZone(ctx->metaFile, (ViewString*) &name);
  if (ctx->metaFile->mainZone) {
    // TODO: redefining main zone warning
  }
  ctx->metaFile->mainZone = mainZone;
  String_free(&name);
}
