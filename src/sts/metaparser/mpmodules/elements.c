#include "mpmodules/elements.h"

#include "mpmodules/declarations.h"
#include "mpmodules/utils.h"
#include "metaparser_errors.h"

static void checkNameValueForLink(Sts_MetaDeclarationHead* head, Sts_MetaDeclarationValue* value) {
  if (value->type == Sts_MetaDeclarationValueType_NAME) {
    bool contains = StringList_contains(&head->linkNames, ViewString_by(value->value.name));
    if (contains) {
      value->type = Sts_MetaDeclarationValueType_LINK;
      value->value.linkName = value->value.name;
    }
  }
}

void parseRegexLink(Context* ctx, Sts_MetaNamespaceDeclaration* namespaceDec) { // TODO: redesign for namespace system
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

void parseSetMainZone(Context* ctx, Sts_MetaNamespaceDeclaration* namespaceDec) {
  Iter startIter = Iter_copy(&ctx->iter);
  Iter_nextChar(&ctx->iter);
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
  Utils_Iter_skipChar(ctx, '-');
  Utils_Iter_skipChar(ctx, '-');

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

void parseZone(Context* ctx, Sts_MetaNamespaceDeclaration* namespaceDec) {
  Utils_Iter_skipVoid(ctx, false);
  String name = Utils_Iter_readName(ctx);
  Sts_MetaDeclarationValue nameValue = Sts_MetaDeclarationValue_byName(name);
  checkNameValueForLink(&namespaceDec->head, &nameValue);

  Sts_MetaElementDeclaration elementDec;
  Sts_MetaElementDeclaration_init(&elementDec, nameValue, Sts_MetaElementDeclarationType_ZONE);
  Declarations_parseDeclarationHead(&elementDec.head, ctx, '(');

  size_t linkNamesNumber = Sts_MetaParser_Context_pushLinkNames(ctx, elementDec.head.linkNames);
  Declarations_parseDeclarations(&elementDec.lineDeclarations, ctx, ')');
  Sts_MetaParser_Context_popLinkNames(ctx, linkNamesNumber);

  Sts_MetaDeclaration declaration = Sts_MetaDeclaration_byElement(elementDec);
  Sts_MetaDeclarations_add(&namespaceDec->declarations, declaration);
}

void parseToken(Context* ctx, Sts_MetaNamespaceDeclaration* namespaceDec) {
  String name = Utils_Iter_readName(ctx);
  Sts_MetaDeclarationValue nameValue = Sts_MetaDeclarationValue_byName(name);
  checkNameValueForLink(&namespaceDec->head, &nameValue);

  Sts_MetaElementDeclaration elementDec;
  Sts_MetaElementDeclaration_init(&elementDec, nameValue, Sts_MetaElementDeclarationType_TOKEN);
  Declarations_parseDeclarationHead(&elementDec.head, ctx, '{');

  size_t linkNamesNumber = Sts_MetaParser_Context_pushLinkNames(ctx, elementDec.head.linkNames);
  Declarations_parseDeclarations(&elementDec.lineDeclarations, ctx, '}');
  Sts_MetaParser_Context_popLinkNames(ctx, linkNamesNumber);

  Sts_MetaDeclaration declaration = Sts_MetaDeclaration_byElement(elementDec);
  Sts_MetaDeclarations_add(&namespaceDec->declarations, declaration);
}

void parseGroup(Context* ctx, Sts_MetaNamespaceDeclaration* namespaceDec) {
  Iter_nextChar(&ctx->iter);
  Utils_Iter_skipVoid(ctx, false);
  String name = Utils_Iter_readName(ctx);
  Sts_MetaDeclarationValue nameValue = Sts_MetaDeclarationValue_byName(name);
  checkNameValueForLink(&namespaceDec->head, &nameValue);

  Sts_MetaElementDeclaration elementDec;
  Sts_MetaElementDeclaration_init(&elementDec, nameValue, Sts_MetaElementDeclarationType_GROUP);
  Declarations_parseDeclarationHead(&elementDec.head, ctx, '(');

  size_t linkNamesNumber = Sts_MetaParser_Context_pushLinkNames(ctx, elementDec.head.linkNames);
  Declarations_parseDeclarations(&elementDec.lineDeclarations, ctx, ')');
  Sts_MetaParser_Context_popLinkNames(ctx, linkNamesNumber);

  Sts_MetaDeclaration declaration = Sts_MetaDeclaration_byElement(elementDec);
  Sts_MetaDeclarations_add(&namespaceDec->declarations, declaration);
}
