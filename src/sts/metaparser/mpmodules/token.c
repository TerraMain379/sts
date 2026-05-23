#include "mpmodules/token.h"

#include "metablocks.h"
#include "metaparser_errors.h"
#include "mpmodules/declarations.h"
#include "mpmodules/utils.h"

#include "stringlist.h"


void_stop error_readName(Context* ctx, int backCharsDistance) {
  if (Iter_currChar(&ctx->iter) == '\0') {
    Errors_metaparser_unexpectedEnd(ctx, Source_byIter(
      ViewString_by(ctx->filename),
      &ctx->iter,
      SPD_new1(SPDMode_BACK_CHAR_SHIFT, backCharsDistance),
      SPD_new1(SPDMode_BACK_CHAR_SHIFT, 1)
    ));
  }
  else {
    Errors_metaparser_anotherTokenExpected(ctx, Source_byIter(
      ViewString_by(ctx->filename),
      &ctx->iter,
      SPD_new1(SPDMode_BACK_CHAR_SHIFT, backCharsDistance),
      SPD_new2(SPDMode_CURR_CHAR)
    ), ViewString_of("<name>"));
  }
  non_call_return;
}

void parseToken(Context* ctx) {
  Iter* iter = &ctx->iter;

  Sts_MetaDeclarationsBlock block;
  Sts_MetaDeclarationsBlock_init(&block, Sts_MetaDeclarationsBlockType_TOKEN);

  String name = Utils_Iter_readName(ctx);
  Utils_Iter_skipVoid(ctx, false);

  char c = Iter_currChar(iter);
  
  bool isGhost = false;
  bool isGeneric = false;

  if (c == '!') {
    isGhost = true;
    Utils_Iter_skipVoid(ctx, false);
    c = Iter_nextChar(iter);
  }
  else if (c == '<') {
    isGeneric = true;
    while (true) {
      Utils_Iter_skipVoid(ctx, false);
      type_errno(String) paramName = Utils_Iter_readName(ctx);
      if (errno != 0) {
        error_readName(ctx, 2);
        non_call_return;
      }
      StringList_add(&block.linkNames, paramName);
      Utils_Iter_skipVoid(ctx, false);
      c = Iter_nextChar(iter);
      if (c == '>') break;
      if (c != ',') {
        Errors_metaparser_unknownToken(ctx, Source_byIter(
          ViewString_by(ctx->filename),
          iter,
          SPD_new2(SPDMode_CURR_CHAR),
          SPD_new2(SPDMode_CURR_CHAR)
        ));
      }
    }
    c = Iter_nextChar(iter);
  }

  if (c == ':') {
    do {
      Utils_Iter_skipVoid(ctx, false);
      type_errno(String) extendName = Utils_Iter_readName(ctx);
      if (errno != 0) {
        error_readName(ctx, 1);
        non_call_return;
      }
      Utils_Iter_skipVoid(ctx, false);
      c = Iter_nextChar(iter);
      if (c == '<') {
        // TODO;
      }
      else if (c == ',') {

      }
      else {
        // TODO ERROR;
      }

      // TODO write this 
      // String extendName = Utils_Iter_readName(ctx);
    } while (true /*TODO*/);

    // TODO;
  }
  else if (c == '{') {
    Iter_nextChar(iter);
    parseDeclarations(&block, ctx);
    Utils_Iter_skipChar(ctx, '}');
  }
  else {
    Errors_metaparser_unknownToken(ctx, Source_byIter(
      ViewString_by(ctx->filename),
      iter,
      SPD_new2(SPDMode_CURR_CHAR),
      SPD_new2(SPDMode_CURR_CHAR)
    ));
  }

  block.name = name;
  Sts_MetaDeclarationsBlocks_add(&ctx->metaFile->decBlocks, block);
}
