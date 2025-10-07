#include "metaparser.h"

#include "errors.h"
#include "utils.h"

#include "metaparsermodules/utils.h"
#include "metaparsermodules/regexlink.h"
#include "metaparsermodules/param.h"
#include "metaparsermodules/zone.h"
#include "metaparsermodules/token.h"

static void parseLoop(struct StsFile* stsFile, const char* input);

void Sts_MetaParser_parse(struct StsFile* stsFile, const char* input) {
  String errLocation = String_const("Sts_MetaParser_parse");
  if (stsFile == 0) Errors_internal_nullPointer(String_const("stsFile"), errLocation);
  if (input == 0) Errors_internal_nullPointer(String_const("input"), errLocation);

  stsFile->currStart = input;
  parseLoop(stsFile, input);
  stsFile->currStart = 0;
}
void parseLoop(struct StsFile* stsFile, const char* input) {
  char* ch = input;
  for (;;) {
    char c = *ch;
    if (c == '\0') break;
    else if (c == '/') {
      parseRegexLink(stsFile, &ch);
    }
    else if (c == '-') { // related to 'zones'
      // parseRelatedToZone(stsFile, &ch);
      parseRelatedToZone(stsFile, &ch);
    }
    else if (isLetter(c)) {
      parseToken(stsFile, &ch, 0);
    }
    else if (isVoid(c)) {
      ch++;
    }
    else {
      String token = String_const((char[]){c, '\0'});
      Errors_metaparser_unkownToken(token, ch, stsFile->currStart);
    }
  }
}
