#pragma once

#include <stdint.h>

#include "strings.h"
#include "strmap.h"
#include "map.h"
#include "list.h"
#include "utils.h"

// SourceList
  #define TYPE struct Source
  #define NAME SourceList
  #define NULLV {0}
  #undef FREEFUN 
  #undef ISPOINTER
  #include "glist.h"
  #undef TYPE
  #undef NAME
  #undef NULLV
  #undef FREEFUN
  #undef ISPOINTER
// end SourceList

// StsZoneMap
  #define TYPE struct StsZone
  #define NAME StsZoneMap
  #define NULLV {0}
  #define FREEFUN StsZone_free
  #undef ISPOINTER
  #include "gmap.h"
  #undef TYPE
  #undef NAME
  #undef NULLV
  #undef FREEFUN
  #undef ISPOINTER
// end StsZoneMap

// Fields (FieldList)
#define TYPE Meta_Field
#define NAME Meta_Fields
#define NULLV {0}
#undef FREEFUN
#undef ISPOINTER
#include "glist.h"
#undef TYPE
#undef NAME
#undef NULLV
#undef FREEFUN
#undef ISPOINTER
// end Fields

struct Meta_Field {
  
}

struct Meta_AbstractElement {
  struct Fields fields;
}


struct StsFile {
  String name;
  struct StrMap regexLinks;
  struct StsZoneMap zones;
  struct SourceList sourses;
  char* currStart;
};

void StsFile_init(struct StsFile* stsFile, String name);
void StsFile_free(struct StsFile* stsFile);


struct StsZone {
  struct List expanders; //<StsZone*>
  struct List unkownParams; //<StsParam*>
  struct List variables; //<StsVariable*>
  struct StrMap events; //<String>
};

void StsZone_init(struct StsZone* stsZone);
void StsZone_free(struct StsZone* stsZone);

struct StsParamType {
  uint8_t v;
};
struct StsParamModifiers {
  bool negative;
  bool dog;
  bool container;
  bool folder;
};
struct StsParam {
  struct StsParamType type;
  struct StsParamModifiers modifiers;
};
