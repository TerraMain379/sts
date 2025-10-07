#include "metaparsermodules/regexlink.h"

#include "metaparsermodules/utils.h"
#include "utils.h"
#include "errors.h"
#include "allocator.h"
#include "strings.h"

String parseRegexLinkName(struct StsFile* stsFile, char** iter);
String parseRegexLinkBody(struct StsFile* stsFile, char** iter);
static void addRegexLink(struct StsFile* stsFile, String name, String regex, char** iter);

void parseRegexLink(struct StsFile* stsFile, char** iter) {
  String name = parseRegexLinkName(stsFile, iter);
  String regex = parseRegexLinkBody(stsFile, iter);
  addRegexLink(stsFile, name, regex, iter);
  String_free(&name);
}
String parseRegexLinkName(struct StsFile* stsFile, char** iter) {
  ++*iter;
  skipVoid(iter);

  if (isLetter(**iter)) {
    String name = readName(stsFile, iter);
    return name;
  }
  else parseErrorsProcessing(stsFile, *iter, (char[]){'/', **iter, '\0'}, 1);
}
String parseRegexLinkBody(struct StsFile* stsFile, char** iter) {
  skipVoid(iter);
  char* ch = *iter;
  char c = *ch;
  if (c != '"') parseErrorsProcessing(stsFile, *iter, (char[]){c, '\0'}, 1);

  ch++;
  String regex = readRegex(stsFile, iter);
  ch++;
  skipVoid(&ch);
  if (*ch != '/') {
    Errors_metaparser_unkownToken(String_const((char[]){c, '\0'}), ch, stsFile->currStart);
  }
  ch++;
  *iter = ch;
  return regex;
}
static void addRegexLink(struct StsFile* stsFile, String name, String regex, char** iter) {
  bool isReplace = StrMap_set(&stsFile->regexLinks, name, regex, true);
  if (isReplace) {
    // TODO Warnings_metaparser_redefiningRegex(name, name, *iter);
  }
}
