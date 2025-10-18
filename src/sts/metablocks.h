typedef struct {
  String regex;
} StsRegex;
void StsRegex_free(StsRegex* regex);

typedef enum {
  number,
  string,
  boolean,
  token,
  tokenProt,
  zone
} StsParamType;
typedef struct {
  StsParamType type;
  void* value;
} StsParamValue;
#define PNAME StsParams
#define PTYPE StsParamValue*
#include "pmap.h"
#undef PNAME
#undef PTYPE
// StsParamValue StsParamValue_byNumber(double number);
// StsParamValue StsParamValue_byString(String string);
// StsParamValue StsParamValue_byBoolean(bool boolean);

typedef struct {
  String code;
} StsEvent;
#define PNAME StsEvents
#define PTYPE StsEvent*
#include "pmap.h"
#undef PNAME
#undef PTYPE

typedef struct {
  String name;
  bool ghost;
  StsZones parentsZone;

  StsParams params;
  StsEvents events;
} StsTokenProt;
StsTokenProt_free(StsTokenProt* tokenProt);
#define PNAME StsTokenProtList
#define PTYPE StsTokenProt*
#include "plist.h"
#undef PNAME
#undef PTYPE

typedef struct {
  String name;

} StsZone;
#define PNAME StsZoneList
#define PTYPE StsZone*
#include "plist.h"
#undef PNAME
#undef PTYPE

typedef struct {
  StsTokenProtList tokens;
  StsZoneList zones;
} StsFile;
