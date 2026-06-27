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
  Sts_MetaNamespaceDeclarationList_init(&context.namespacesBuffer, 8);

  if (setjmp(context.errjmp) != 0) { // ERROR EXIT
    errno = 1; return;
  }
  
  Sts_MetaParser_Context_pushNamespace(&context, metaFile->baseNamespaceDeclaration);
  parseNamespaceBody(&context, metaFile->baseNamespaceDeclaration, true);
  Sts_MetaParser_Context_popNamespace(&context);

  Sts_MetaNamespaceDeclarationList_free(&context.namespacesBuffer);
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
  size_t startSize = context->linkNamesBuffer.size;
  for (size_t i = linkNamesNumber; i > 0; i--) {
    ViewStringList_remove(&context->linkNamesBuffer, startSize-i);
  }
}

void Sts_MetaParser_Context_pushNamespace(Sts_MetaParser_Context* context, MUT_WEAK(Sts_MetaNamespaceDeclaration*) namespace) {
  Sts_MetaNamespaceDeclarationList_add(&context->namespacesBuffer, namespace);
}
void Sts_MetaParser_Context_popNamespace(Sts_MetaParser_Context* context) {
  Sts_MetaNamespaceDeclarationList_remove(&context->namespacesBuffer, context->namespacesBuffer.size - 1);
}
MUT_WEAK(Sts_MetaNamespaceDeclaration*) Sts_MetaParser_Context_getCurrNamespace(Sts_MetaParser_Context* context) {
  return Sts_MetaNamespaceDeclarationList_get(&context->namespacesBuffer, context->namespacesBuffer.size - 1);
}

bool Sts_MetaDeclarationValue_checkForLink(Sts_MetaDeclarationValue* decValue, Sts_MetaParser_Context* context) {
  if (decValue->type == Sts_MetaDeclarationValueType_NAME) {
    bool contains = ViewStringList_contains(&context->linkNamesBuffer, ViewString_by(decValue->value.name.name));
    if (contains) {
      decValue->type = Sts_MetaDeclarationValueType_LINK;
      decValue->value.linkName = decValue->value.name.name;
    }
    return contains;
  }
  return false;
}
Sts_MetaDeclarationValue Sts_MetaDeclarationValue_byName1(String name, Sts_MetaParser_Context* context) {
  return Sts_MetaDeclarationValue_byName((Sts_MetaDeclarationValueName) {
    .name = name,
    .parentNamespace = Sts_MetaParser_Context_getCurrNamespace(context),
  });
}
