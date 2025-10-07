#include "metaparsermodules/param.h"

#include "metaparsermodules/utils.h"
#include "errors.h"

String parseParamName(struct StsFile* stsFile, char** iter, struct StsParamModifiers* modifiers) {
  char* ch = *iter;

  if (*ch == '@') {
    modifiers->dog = 1;
    ch++;
    skipVoid(&ch);
  }
  else modifiers->dog = 0;

  String name = readName(stsFile, iter);
  skipVoid(iter);

  if (*ch == '!') {
    modifiers->negative = 1;
    ch++;
    skipVoid(&ch);
  }
  else modifiers->negative = 0;


  char c = *ch;
  if (c == ':') {
    modifiers->container = 0;
    modifiers->folder = 0;
  }
  else if (c == '{') {
    modifiers->container = 1;
    modifiers->folder = 0;
  }
  else if (c == '(') {
    modifiers->container = 0;
    modifiers->folder = 1;
  }
  else {
    Errors_metaparser_unkownToken(String_const((char[]){c, '\0'}), ch, stsFile->currStart);
  }
  return name;
}

void parseEventsBody(struct StsFile* stsFile, char** iter) {
  // TODO
}
