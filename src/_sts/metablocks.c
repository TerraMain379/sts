#include "metablocks.h"

#include "allocator.h"


void StsFile_init(struct StsFile* stsFile, String name) {
  stsFile->name = name;
  StrMap_init(& stsFile->regexLinks);
  Map_init(& stsFile->zones);
}
void StsFile_free(struct StsFile* stsFile) {
  String_free(& stsFile->name);
  // StrMap_freeElements(& stsFile->regexLinks);
  StrMap_free(& stsFile->regexLinks);
  Map_free(& stsFile->zones);
}

void StsZone_init(struct StsZone* stsZone) {
  List_init(&stsZone->expanders, 1);
  List_init(&stsZone->unkownParams, 1);
  List_init(&stsZone->variables, 1);
  StrMap_init(& stsZone->events);
}
void StsZone_free(struct StsZone* stsZone) {
  List_free(&stsZone->expanders);
  List_free(&stsZone->unkownParams);
  List_free(&stsZone->variables);
  // StrMap_freeElements(& stsZone->events);
  StrMap_free(& stsZone->events);
}
