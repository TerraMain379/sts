#include "mpmodules/token.h"

#include "mpmodules/declarations.h"
#include "mpmodules/utils.h"


void parseToken(Context* ctx) {
  String name = Utils_Iter_readName(ctx);

  Sts_MetaDeclarationsBlock decBlock;
  Sts_MetaDeclarationsBlock_init(&decBlock, Sts_MetaDeclarationsBlockType_TOKEN);
  Declarations_parseDeclarationsBlockHeader(&decBlock, ctx, name, '{');
  Declarations_parseDeclarations(&decBlock, ctx, '}');
  Sts_MetaDeclarationsBlocks_add(&ctx->metaFile->decBlocks, decBlock);
}
