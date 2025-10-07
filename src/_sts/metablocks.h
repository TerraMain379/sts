#pragma once

#include "utils.h"
#include "strmap.h"


typedef struct {
  String regex;
} StsRegex;
void StsRegex_free(StsRegex* regex);

// StsRegexLinks
  #define NAME StsRegexLinks
  #define TYPE StsRegex
  #define NULLV {0}
  #define FREEFUN StsRegex_free
  #undef ISPOINTER
  #include "gmap.h"
  #undef TYPE
  #undef NAME
  #undef NULLV
  #undef FREEFUN
  #undef ISPOINTER
//

typedef struct {
  String name;
  StsRegex regex;
  StrMap events;
  bool ghost;
  int priority;

  // StsZone* parentZone;
  StsZone* openZone;
  StsZone* setZone;
  bool closeZone;

  StsFields fields;
  StsFields staticFields;
} StsTokenPrototype;

// StsZoneList
  #define NAME StsZoneList
  #define TYPE StsZone*
  #define NULLV 0
  #undef FREEFUN
  #define ISPOINTER true
  #include "glist.h"
  #undef TYPE
  #undef NAME
  #undef NULLV
  #undef FREEFUN
  #undef ISPOINTER
//

// StsTokenPrototypeList
  #define NAME StsTokenPrototypeList
  #define TYPE StsTokenPrototype*
  #define NULLV 0
  #undef FREEFUN
  #define ISPOINTER true
  #include "glist.h"
  #undef TYPE
  #undef NAME
  #undef NULLV
  #undef FREEFUN
  #undef ISPOINTER
//

typedef struct {
  String name;
  StsTokenPrototypeList tokens;
  StsZoneList expanders;
  
  StsFields fields;
  StsFields staticFields;
} StsZone;


typedef struct {
  StsZoneMap zones;
  StsRegexLinks regexLinks;
} StsFile;
