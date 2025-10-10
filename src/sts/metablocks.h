typedef struct {
  String regex;
} StsRegex;
void StsRegex_create(StsRegex* regex, String regex);
void StsRegex_free(StsRegex* regex);

typedef struct {
  StsParamType type;
  void* value;
} StsParamValue;

#define NAME StsParams
#define TYPE StsParamValue*
#define NULLV 0
#include "gmap.h"
#undef NAME
#undef TYPE
#undef NULLV

typedef struct {
  String name;
  bool ghost;
  StsZones parentsZone;

  StsParams params;
  StsEvents events;
} StsTokenProt;
StsTokenProt_free(StsTokenProt* tokenProt);

#define NAME StsTokenProtList
#define TYPE StsTokenProt*
#define NULLV 0
#include "glist.h"
#undef NAME
#undef TYPE
#undef NULLV

typedef struct {
  StsTokenPrototypeList tokens;
  StsZoneList zones;
} StsFile;
