#include "metaparser.h"

#include "errors.h"
#include "mpmodules/namespace.h"


void Sts_MetaParser_Arguments_init(Sts_MetaParser_Arguments* arguments) {
  arguments->metadata.filename = (String) {0};
}
void Sts_MetaParser_Arguments_free(Sts_MetaParser_Arguments* arguments) {
  String_free(&arguments->metadata.filename);
}

void_errno Sts_MetaParser_parse(MUT_BORROW(Sts_MetaFile*) metaFile, Iter iter, Sts_MetaParser_Arguments args) {
  ViewString errLocation = ViewString_of("Sts_MetaParser_parse");
  if (metaFile == null) Errors_internal_nullPointer(ViewString_of("Sts_MetaFile* metaFile"), errLocation);
  // if (args == null) Errors_internal_nullPointer(ViewString_of("Sts_MetaParser_Arguments* args"), errLocation);
  
  Sts_MetaParser_Context context = {
    .filename = args.metadata.filename,
    .metaFile = metaFile,
    .iter = iter,
    .linkNamesBuffer = {},
  };
  ViewStringList_init(&context.linkNamesBuffer, 32);

  if (setjmp(context.errjmp) != 0) { // ERROR EXIT
    errno = 1; return;
  }
  
  Sts_MetaDeclarationHead tempHead;
  StringList_init(&tempHead.linkNames, 0);
  Sts_MetaDeclarationExtendElementList_init(&tempHead.extenders, 0);

  Sts_MetaNamespaceDeclaration tempNamespaceDec;
  tempNamespaceDec.head = tempHead;
  tempNamespaceDec.declarations = metaFile->declarations; // moveing list to tempNamespaceDec and back after parse
  parseNamespaceBody(&context, &tempNamespaceDec, true);
  metaFile->declarations = tempNamespaceDec.declarations;

  Sts_MetaDeclarationExtendElementList_freeElements(&tempHead.extenders);
  Sts_MetaDeclarationExtendElementList_free(&tempHead.extenders);
  StringList_freeElements(&tempHead.linkNames);
  StringList_free(&tempHead.linkNames);
  ViewStringList_freeElements(&context.linkNamesBuffer);
  ViewStringList_free(&context.linkNamesBuffer);

  errno = 0; return;
}

size_t Sts_MetaParser_Context_pushLinkNames(Sts_MetaParser_Context* context, BORROW(StringList) pushLinks) {
  size_t linkNamesNumber = pushLinks.size;
  if (context->linkNamesBuffer.capacity < context->linkNamesBuffer.size + linkNamesNumber) {
    ViewStringList_setCapacity(&context->linkNamesBuffer, context->linkNamesBuffer.size + linkNamesNumber);
  }
  for (size_t i = 0; i < linkNamesNumber; i++) {
    ViewString vs = *(ViewString*) StringList_get(&pushLinks, i);
    ViewStringList_add(&context->linkNamesBuffer, vs);
  }
  return linkNamesNumber;
}
void Sts_MetaParser_Context_popLinkNames(Sts_MetaParser_Context* context, size_t linkNamesNumber) {
  for (size_t i = linkNamesNumber; i > 0; i--) {
    ViewStringList_remove(&context->linkNamesBuffer, i-1);
  }
}

bool Sts_MetaDeclarationValue_checkForLink(Sts_MetaDeclarationValue* decValue, Sts_MetaParser_Context* context) {
  if (decValue->type == Sts_MetaDeclarationValueType_NAME) {
    bool contains = ViewStringList_contains(&context->linkNamesBuffer, ViewString_by(decValue->value.name));
    if (contains) {
      decValue->type = Sts_MetaDeclarationValueType_LINK;
      decValue->value.linkName = decValue->value.name;
    }
    return contains;
  }
  return false;
}
