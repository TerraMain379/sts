#include "mpmodules/token.h"

#include "metablocks.h"
#include "metaparser_errors.h"
#include "mpmodules/utils.h"

#include "stringlist.h"

void parseToken(Context* ctx) {
  Iter* iter = &ctx->iter;

  String name = Utils_Iter_readName(ctx);
  Utils_Iter_skipVoid(ctx, false);

  char c = Iter_nextChar(iter);
  
  bool isGhost = false;
  bool isGeneric = false;
  StringList temp_genericParamList;
  StringList* genericParamList = &temp_genericParamList;
  StringList_init(genericParamList, 2);

  if (c == '!') {
    isGhost = true;
    Utils_Iter_skipVoid(ctx, false);
    c = Iter_nextChar(iter);
  }
  else if (c == '<') {
    isGeneric = true;
    while (true) {
      Utils_Iter_skipVoid(ctx, false);
      String paramName = Utils_Iter_readName(ctx);
      StringList_add(genericParamList, paramName);
      Utils_Iter_skipVoid(ctx, false);
      c = Iter_nextChar(iter);
      if (c == '>') break;
      if (c != ',') {
        Errors_metaparser_unkownToken(ctx, Source_byIter(
          (ViewString*) &ctx->args->metadata.filename,
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
      String extendName = Utils_Iter_readName(ctx);
      Utils_Iter_skipVoid(ctx, false);
      c = Iter_nextChar(iter);
      if (c == '<') {
        // TO‍DO;
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
    // TODO;
  }
  else {
    Errors_metaparser_unkownToken(ctx, Source_byIter(
      (ViewString*) &ctx->args->metadata.filename,
      iter,
      SPD_new2(SPDMode_CURR_CHAR),
      SPD_new2(SPDMode_CURR_CHAR)
    ));
  }
  String_free(&name);
}
