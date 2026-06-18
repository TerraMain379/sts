#include "mpmodules/zone.h"

#include "mpmodules/declarations.h"
#include "mpmodules/utils.h"

void parseZone(Context* ctx) {
  Utils_Iter_skipVoid(ctx, false);
  String name = Utils_Iter_readName(ctx);

  Sts_MetaDeclarationsBlock decBlock;
  Sts_MetaDeclarationsBlock_init(&decBlock, Sts_MetaDeclarationsBlockType_ZONE);
  Declarations_parseDeclarationsBlockHeader(&decBlock, ctx, name, '(');
  Declarations_parseDeclarations(&decBlock, ctx, ')');
  Sts_MetaDeclarationsBlocks_add(&ctx->metaFile->decBlocks, decBlock);
}
