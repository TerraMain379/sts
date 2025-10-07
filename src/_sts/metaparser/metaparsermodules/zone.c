#include "metaparsermodules/zone.h"

#include "metaparsermodules/utils.h"
#include "metaparsermodules/param.h"
#include "errors.h"
#include "allocator.h"

void parseZone(struct StsFile* stsFile, char** iter, bool isModificator);
String parseZoneName(struct StsFile* stsFile, char** iter);
struct StsZone* parseZoneBody(struct StsFile* stsFile, char** iter, bool isModificator);
bool parseZoneParam(struct StsFile* stsFile, struct StsZone* stsZone, char** iter);
void parseZoneExpand(struct StsFile* stsFile, struct StsZone* stsZone, char** iter);
int parseParamType(struct StsFile* stsFile, char** iter);
void parseMainZone(struct StsFile* stsFile, char** iter);


void parseRelatedToZone(struct StsFile* stsFile, char** iter) {
  char* ch = *iter;
  ch++;
  char c = *ch;

  if (c == '-') { // main zone
    ch++;
    parseMainZone(stsFile, &ch);
  }
  else if (isLetter(c)) { // zone
    parseZone(stsFile, &ch, 0);
  }
  else if (isVoid(c)) { // zone (-  /*spaces*/  name)
    skipVoid(&ch);
    if (isLetter(*ch)) {
      parseZone(stsFile, &ch, 0);
    }
    else { // invalid name
      char name[2] = {*ch, '\0'};
      Errors_metaparser_invalidName(String_const(name), ch, String_const("zone"), stsFile->currStart);
    }
  }
  else if (c == '~') { // zone-modificator
    ch++;
    parseZone(stsFile, &ch, 1);
  }
  else { // unkown token
    char token[2] = {'-', c};
    Errors_metaparser_unkownToken(String_const(token), ch, stsFile->currStart);
  }
  *iter = ch;
}

void parseZone(struct StsFile* stsFile, char** iter, bool isModificator) {
  ++*iter;
  String name = parseZoneName(stsFile, iter);
  skipVoid(iter);
  struct StsZone* stsZone = parseZoneBody(stsFile, iter, isModificator);
  // TODO: 
}
String parseZoneName(struct StsFile* stsFile, char** iter) {
  skipVoid(iter);
  char* ch = *iter;
  if (!isLetter(*ch)) parseErrorsProcessing(stsFile, ch, (char[]){*ch, '\0'}, 1);

  *iter = ch;
  String name = readName(stsFile, iter);
  return name;
}
struct StsZone* parseZoneBody(struct StsFile* stsFile, char** iter, bool isModificator) {
  char* ch = *iter;
  ch++;
  struct StsZone* stsZone = A_loc(sizeof(struct StsZone));
  StsZone_init(stsZone);

  for (;;) {
    skipVoid(&ch);
    if (parseZoneParam(stsFile, stsZone, &ch)) break;
  }
  *iter = ch;
  return stsZone;
}
bool parseZoneParam(struct StsFile* stsFile, struct StsZone* stsZone, char** iter) {
  char c = **iter;
  if (c == ')') {
    return 1; // exit from parse param loop
  }
  else if (c == '<') {
    parseZoneExpand(stsFile, stsZone, iter);
  }
  else if (isLetter(c)) {
    struct StsParamModifiers modifiers;
    String name = parseParamName(stsFile, iter, &modifiers);
    if (modifiers.container) { // {}
    
    }
    else if (!modifiers.folder) { // :
      
    }
    else { // (

    }
    int type = parseParamType(stsFile, iter);
  }

  return 0;
}
int parseParamType(struct StsFile* stsFile, char** iter) {
  return 0; // TODO: 
}
void parseZoneExpand(struct StsFile* stsFile, struct StsZone* stsZone, char** iter) {
  char* ch = *iter;
  ch++;
  skipVoid(&ch);
  size_t len;
  String expander = readName(stsFile, iter);
  
}
void parseMainZone(struct StsFile* stsFile, char** iter) {

}
