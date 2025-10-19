#include "metaparser.h"
#include "errors.h"

void Sts_MetaParser_parse(Sts_MetaFile* metaFile, Iter* iter) {
  String errLocation = String_const("Sts_MetaParser_parse");
  if (metaFile == 0) Errors_internal_nullPointer(String_const("stsFile"), errLocation);
  if (iter == 0) Errors_internal_nullPointer(String_const("input"), errLocation);
}
