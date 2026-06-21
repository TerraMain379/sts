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
    // .args = args,
  };

  if (setjmp(context.errjmp) != 0) { // ERROR EXIT
    errno = 1; return;
  }
  
  Sts_MetaDeclarationHead tempHead;
  StringList_init(&tempHead.linkNames, 0);
  Sts_MetaDeclarationExtendElementList_init(&tempHead.extenders, 0);
  Sts_MetaNamespaceDeclaration tempNamespaceDec;
  tempNamespaceDec.head = tempHead;
  Sts_MetaDeclarations_init(&tempNamespaceDec.declarations, 50);
  
  parseNamespaceBody(&context, &tempNamespaceDec, true);
  metaFile->declarations = tempNamespaceDec.declarations;
  errno = 0; return;
}
