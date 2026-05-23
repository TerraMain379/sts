#include "mpmodules/regexlink.h"

#include "metablocks.h"
#include "mpmodules/utils.h"
#include "metaparser_errors.h"

void parseRegexLink(Context* ctx) {
  Utils_Iter_skipChar(ctx, '/');
  Utils_Iter_skipVoid(ctx, false);
  type_errno(String) name = Utils_Iter_readName(ctx);
  if (errno != 0) {
    if (Iter_currChar(&ctx->iter) == '\0') {
      Errors_metaparser_unexpectedEnd(ctx, Source_byIter(
        ViewString_by(ctx->filename),
        &ctx->iter,
        SPD_new1(SPDMode_BACK_CHAR_SHIFT, 1),
        SPD_new1(SPDMode_BACK_CHAR_SHIFT, 1)
      ));
      non_call_return;
    }
    else {
      Errors_metaparser_anotherTokenExpected(ctx, Source_byIter(
        ViewString_by(ctx->filename),
        &ctx->iter,
        SPD_new1(SPDMode_BACK_CHAR_SHIFT, 1),
        SPD_new2(SPDMode_CURR_CHAR)
      ), ViewString_of("<name>"));
      non_call_return;
    }
  }
  Utils_Iter_skipVoid(ctx, false);
  Utils_Iter_skipChar(ctx, '"');
  String regex = Utils_Iter_readString(ctx);
  Utils_Iter_skipChar(ctx, '/');

  Sts_MetaRegex metaRegex;
  Sts_MetaRegex_init(&metaRegex, regex);
  Sts_MetaRegexLinks_setByOwnKey(&ctx->metaFile->regexes, name, metaRegex);
}
