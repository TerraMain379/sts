#include "mp_parse/namespace.h"

#include "mp_parse/utils.h"
#include "mp_parse/declarations.h"
#include "mp_parse/elements.h"
#include "mp_parse/ssts.h"
#include "mp_parse/namespace.h"
#include "metaparser_errors.h"
#include "allocator.h"

void parseNamespace(Sts_MetaParser_Context* ctx, Sts_MetaNamespaceDeclaration* parentNamespaceDec) {
  Iter_nextChar(&ctx->iter);
  Utils_Iter_skipVoid(ctx, false);
  type_errno(String) name = Utils_Iter_readName(ctx);
  Sts_MetaDeclarationValue nameValue = Sts_MetaDeclarationValue_byName1(name, ctx);
  Sts_MetaDeclarationValue_checkForLink(&nameValue, ctx);

  Sts_MetaNamespaceDeclaration* namespaceDec = A_xloc(sizeof(Sts_MetaNamespaceDeclaration));
  Sts_MetaNamespaceDeclaration_init(namespaceDec, nameValue);
  size_t linkNamesInBufferNumber = Declarations_parseDeclarationHead(&namespaceDec->head, ctx, '{');

  // size_t linkNamesNumber = Sts_MetaParser_Context_pushLinkNames(ctx, namespaceDec->head.linkNames);
  Sts_MetaParser_Context_pushNamespace(ctx, namespaceDec);
  parseNamespaceBody(ctx, namespaceDec, false);
  Sts_MetaParser_Context_popLinkNames(ctx, linkNamesInBufferNumber);
  Sts_MetaParser_Context_popNamespace(ctx);

  Sts_MetaDeclaration declaration = Sts_MetaDeclaration_byNamespace(namespaceDec);
  Sts_MetaDeclarations_add(&parentNamespaceDec->declarations, declaration);
}

void parseNamespaceBody(Context* ctx, Sts_MetaNamespaceDeclaration* namespaceDec, bool isRootSpace) {
  Iter* iter = &ctx->iter;

  ViewString filename = ViewString_by(ctx->filename);

  bool flagModificator = false;
  for (char c = Iter_currChar(iter);; c = Iter_currChar(iter)) {
    // TODO: In the future, it's worth switching to the dispatch table.

    if (c == '#' || Chars_isVoid(c)) {
      Utils_Iter_skipVoid(ctx, false);
    }
    else if (Chars_isLetter(c)) {
      parseToken(ctx, namespaceDec);
    }
    else if (c == '~') {
      // modificator flag
      if (!flagModificator) {
        flagModificator = true;
      }
      else {
        Errors_metaparser_unknownToken(ctx, Source_byIter(
          filename,
          iter,
          SPD_new1(SPDMode_BACK_WORD_SHIFT, 1),
          SPD_new2(SPDMode_CURR_CHAR)
        ));
      }
    }
    else if (c == '-') {
      c = Iter_nextChar(iter);
      if (errno != 0) {
        Errors_metaparser_unexpectedEnd(ctx, Source_byIter(
          filename,
          iter,
          SPD_new2(SPDMode_CURR_LINE),
          SPD_new2(SPDMode_CURR_CHAR)
        ));
      }

      if (c == '-') {
        if (!isRootSpace) {
          Errors_metaparser_tokenNotAvailableHere(ctx, Source_byIter(
            ViewString_by(ctx->filename),
            iter,
            SPD_new2_double(SPDMode_CURR_CHAR)
          ), ViewString_of("main zone declaration available only in root space"));
          non_call_return;
        }
        parseSetMainZone(ctx, namespaceDec);
      }
      else {
        parseZone(ctx, namespaceDec);
      }
    }
    else if (c == '/') { 
      if (!isRootSpace) {
        Errors_metaparser_tokenNotAvailableHere(ctx, Source_byIter(
          ViewString_by(ctx->filename),
          iter,
          SPD_new2_double(SPDMode_CURR_CHAR)
        ), ViewString_of("regex-link declaration available only in root space"));
        non_call_return;
      }
      parseRegexLink(ctx, namespaceDec);
    }
    else if (c == '[') {
      // TODO: supertokens deleted
      Errors_metaparser_unknownToken(ctx, Source_byIter(
        filename,
        iter,
        SPD_new2(SPDMode_CURR_CHAR),
        SPD_new2(SPDMode_CURR_CHAR)
      ));
    }
    else if (c == '*') {
      parseGroup(ctx, namespaceDec);
    }
    else if (c == ':') { 
      parseSstsFunction(ctx, namespaceDec); // TODO:
    }
    else if (c == '%') {
      parseNamespace(ctx, namespaceDec);
    }
    else if (c == '}' && !isRootSpace) {
      Iter_nextChar(iter);
      break;
    }
    else if (c == '\0') {
      if (isRootSpace) {
        break;
      }
      else {
        Errors_metaparser_unexpectedEnd(ctx, Source_byIter(
          filename,
          iter,
          SPD_new2(SPDMode_CURR_CHAR),
          SPD_new2(SPDMode_CURR_CHAR)
        ));
      }
    }
    else {
      Errors_metaparser_unknownToken(ctx, Source_byIter(
        filename,
        iter,
        SPD_new2(SPDMode_CURR_CHAR),
        SPD_new2(SPDMode_CURR_CHAR)
      ));
    }
  }
}
