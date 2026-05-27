#include "mpmodules/token.h"

#include "metablocks.h"
#include "metaparser_errors.h"
#include "mpmodules/declarations.h"
#include "mpmodules/utils.h"

#include "allocator.h"
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
  Sts_MetaDeclarationsBlock block;
  Sts_MetaDeclarationsBlock_init(&block, Sts_MetaDeclarationsBlockType_TOKEN);

  Iter* iter = &ctx->iter;
  String name = Utils_Iter_readName(ctx);
  Utils_Iter_skipVoid(ctx, false);

  char c = Iter_currChar(iter);
  
  bool isGeneric = false;

  if (c == '!') {
    Sts_MetaDeclaration* dec = A_xloc(sizeof(Sts_MetaDeclaration));
    *dec = (Sts_MetaDeclaration) {
      .type = Sts_MetaDeclarationType_PARAM,
      .value = { .param = {
        .name = {
          .type = Sts_MetaDeclarationValueType_NAME,
          .value = { .name = String_by("isGhost") }
        },
        .values = {/* */},
      } }
    };
    Sts_MetaDeclarationValueList_init(&dec->value.param.values, 1);
    Sts_MetaDeclarationValueList_add(&dec->value.param.values, (Sts_MetaDeclarationValue) {
      .type = Sts_MetaDeclarationValueType_NUMBER,
      .value = { .number = 1 },
    });
    Sts_MetaDeclarationList_add(&block.declarations, dec);

    Iter_nextChar(iter);
    Utils_Iter_skipVoid(ctx, false);
    c = Iter_currChar(iter);
  }
  else if (c == '<') {
    isGeneric = true;

    Iter_nextChar(iter);
    while (true) {
      Utils_Iter_skipVoid(ctx, false);
      if (!Chars_isNameStart(Iter_currChar(&ctx->iter))) {
        error_readName(ctx, 0);
        non_call_return;
      }
      type_errno(String) paramName = Utils_Iter_readName(ctx);
      if (errno != 0) {
        error_readName(ctx, 2);
        non_call_return;
      }
      StringList_add(&block.linkNames, paramName);
      Utils_Iter_skipVoid(ctx, false);
      c = Iter_currChar(iter);
      if (c == '>') break;
      else if (c == ',') {
        Iter_nextChar(iter);
      }
      else {
        Errors_metaparser_unknownToken(ctx, Source_byIter(
          ViewString_by(ctx->filename),
          iter,
          SPD_new2(SPDMode_CURR_CHAR),
          SPD_new2(SPDMode_CURR_CHAR)
        ));
        non_call_return;
      }
    }
    Iter_nextChar(iter);
    Utils_Iter_skipVoid(ctx, false);
    c = Iter_currChar(iter);
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
    c = Iter_currChar(iter);
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
