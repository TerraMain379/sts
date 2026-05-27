#include "mpmodules/regexlink.h"

#include "metablocks.h"
#include "mpmodules/utils.h"
#include "metaparser_errors.h"

void parseRegexLink(Context* ctx) {
  Iter startIter = Iter_copy(&ctx->iter);
  Utils_Iter_skipChar(ctx, '/');
  Utils_Iter_skipVoid(ctx, false);
  type_errno(String) name = Utils_Iter_readName(ctx);
  if (errno != 0) goto goto_error_readName;
  Utils_Iter_skipVoid(ctx, false);
  Utils_Iter_skipChar(ctx, '"');
  String regex = Utils_Iter_readString(ctx);
  Utils_Iter_skipChar(ctx, '/');

  Sts_MetaRegex metaRegex;
  Sts_MetaRegex_init(&metaRegex, regex);
  if (Sts_MetaRegexLinks_contains(&ctx->metaFile->regexes, ViewString_by(name))) {
    goto goto_error_redefining;
  }
  Sts_MetaRegexLinks_setByOwnKey(&ctx->metaFile->regexes, name, metaRegex);
  return;

  goto_error_readName: {
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
    return;
  }
  goto_error_redefining: {
    Warnings_metaparser_redefiningRegex(ctx, Source_byIters(
      ViewString_by(ctx->filename),
      &startIter,
      SPD_new2(SPDMode_CURR_CHAR),
      &ctx->iter,
      SPD_new2(SPDMode_CURR_CHAR)
    ), ViewString_by(name));
    return;
  }
}
