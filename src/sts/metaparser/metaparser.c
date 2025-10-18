#include "metaparser.h"

void MetaParser_parse(StsFile* stsFile, const char* input) {
  String errLocation = String_const("Sts_MetaParser_parse");
  if (stsFile == 0) Errors_internal_nullPointer(String_const("stsFile"), errLocation);
  if (input == 0) Errors_internal_nullPointer(String_const("input"), errLocation);

  stsFile->currStart = input;
  parseLoop(stsFile, input);
  stsFile->currStart = 0;
}
