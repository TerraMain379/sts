#include "mpmodules/regexlink.h"

#include "metablocks.h"
#include "mpmodules/utils.h"

void parseRegexLink(Context* ctx) {
  Utils_Iter_skipVoid(ctx, false);
  String name = Utils_Iter_readName(ctx);
  Utils_Iter_skipVoid(ctx, false);
  Utils_Iter_readChar(ctx, '"');
  String regex = Utils_Iter_readString(ctx);
  Utils_Iter_readChar(ctx, '/');

  Sts_MetaRegex metaRegex;
  Sts_MetaRegex_init(&metaRegex, regex);
  Sts_MetaRegexLinks_setByOwnKey(&ctx->metaFile->regexes, &name, metaRegex);
}
