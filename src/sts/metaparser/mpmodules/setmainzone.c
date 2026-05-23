#include "mpmodules/setmainzone.h"

#include "metablocks.h"
#include "mpmodules/utils.h"
#include "metaparser_errors.h"

void parseSetMainZone(Context* ctx) {
  Iter startIter = Iter_copy(&ctx->iter);
  Utils_Iter_skipVoid(ctx, false);
  type_errno(String) name = Utils_Iter_readName(ctx);
  if (errno != 0) {
    if (Iter_currChar(&ctx->iter) == '\0') {
      Errors_metaparser_unexpectedEnd(ctx, Source_byIter(
        ViewString_by(ctx->filename),
        &ctx->iter,
        SPD_new1(SPDMode_BACK_CHAR_SHIFT, 2),
        SPD_new1(SPDMode_BACK_CHAR_SHIFT, 1)
      ));
      non_call_return;
    }
    else {
      Errors_metaparser_anotherTokenExpected(ctx, Source_byIter(
        ViewString_by(ctx->filename),
        &ctx->iter,
        SPD_new1(SPDMode_BACK_CHAR_SHIFT, 2),
        SPD_new2(SPDMode_CURR_CHAR)
      ), ViewString_of("<name>"));
      non_call_return;
    }
  }
  Utils_Iter_readChar(ctx, '-');
  Utils_Iter_readChar(ctx, '-');

  Sts_MetaZone* mainZone = Sts_MetaFile_getOrCreateZone(ctx->metaFile, ViewString_by(name));
  if (ctx->metaFile->mainZone) {
    Warnings_metaparser_redefiningMainZone(ctx, Source_byIters(
      ViewString_by(ctx->filename),
      &startIter,
      SPD_new2(SPDMode_CURR_CHAR),
      &ctx->iter,
      SPD_new2(SPDMode_CURR_CHAR)
    ), ViewString_by(name));
  }
  ctx->metaFile->mainZone = mainZone;
  String_free(&name);
}
