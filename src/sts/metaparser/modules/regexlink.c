#include "modules/regexlink.h"

#include "metablocks.h"
#include "modules/utils.h"

void parseRegexLink(Context* ctx) {
  skipVoid(ctx);
  String name = readName(ctx);
  skipVoid(ctx);
  readChar(ctx, '"');
  String regex = readString(ctx);
  readChar(ctx, '/');

  Sts_MetaRegex metaRegex;
  Sts_MetaRegex_init(&metaRegex, regex);
  Sts_MetaRegexes_set(ctx->metaFile->regexes, name, regex);
  String_free(name);
}
