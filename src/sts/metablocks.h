#pragma once

#include "utils.h"
#include "string.h"
#include "sources.h"
#include "stss.h"

#define typedef_struct(name) typedef struct name name
#define typedef_enum(name) typedef enum name name
  typedef_struct(Sts_MetaRegex);
  typedef_struct(Sts_MetaRegexLinks);
  typedef_struct(Sts_MetaEvent);
  typedef_struct(Sts_MetaEvents);
  typedef_struct(Sts_MetaVariable);
  typedef_struct(Sts_MetaElementVariables);
  typedef_enum(Sts_MetaStaticParamType);
  typedef_struct(Sts_MetaStaticParam);
  typedef_struct(Sts_MetaStaticParams);

  typedef_struct(Sts_OwnedMetaTokens);
  typedef_struct(Sts_OwnedMetaTokens);

  typedef_struct(Sts_MetaZone);
  typedef_struct(Sts_MetaToken);
  typedef_struct(Sts_MetaFile);
#undef typedef_struct
#undef typedef_enum


struct Sts_MetaRegex {
  String regex;
};
void Sts_MetaRegex_init(Sts_MetaRegex* metaRegex, String regex);
void Sts_MetaRegex_free(Sts_MetaRegex* metaRegex);

#define NAME Sts_MetaRegexLinks
#define TYPE Sts_MetaRegex
#define NULLV (Sts_MetaRegex) {0}
#define FREEFUN Sts_MetaRegex_free
#include "gmap.h"
#undef NAME
#undef TYPE
#undef NULLV
#undef FREEFUN


struct Sts_MetaEvent {
  String code;
};
void Sts_MetaEvent_init(Sts_MetaEvent* event, String code);
void Sts_MetaEvent_free(Sts_MetaEvent* event);

#define NAME Sts_MetaEvents
#define TYPE Sts_MetaEvent
#define NULLV (Sts_MetaEvent) {0}
#define FREEFUN Sts_MetaEvent_free
#include "gmap.h"
#undef NAME
#undef TYPE
#undef NULLV
#undef FREEFUN


struct Sts_MetaElementVariable {
  Stss_Type type;
  OWNER(Stss_UntypeValue) value;
};
void Sts_MetaElementVariable_init(Sts_MetaVariable* variable);
void Sts_MetaElementVariable_free(Sts_MetaVariable* variable);

#define NAME Sts_MetaElementVariables
#define TYPE Sts_MetaElementVariable
#define NULLV (Sts_MetaElementVariable) {0};
#define FREEFUN Sts_MetaElementVariable_free
#include "gmap.h"
#undef NAME
#undef TYPE
#undef NULLV
#undef FREEFUN

struct Sts_MetaElementStaticParam {
  Stss_Type type;
  OWNER(Stss_UntypeValue) value;
};
void Sts_MetaStaticParam_init(Sts_MetaStaticParam* staticParam);
void Sts_MetaStaticParam_free(Sts_MetaStaticParam* staticParam);

#define NAME Sts_MetaStaticParams
#define TYPE Sts_MetaStaticParam
#define NULLV (Sts_MetaStaticParam) {0};
#define FREEFUN Sts_MetaStaticParam_free
#include "gmap.h"
#undef NAME
#undef TYPE
#undef NULLV
#undef FREEFUN


#define extends__Sts_MetaElement \
  String name; \
  Sts_MetaElementStaticParams params; \
  Sts_MetaElementVariables variables; \
  Sts_MetaEvents events;
struct Sts_MetaElement {
  extends__Sts_MetaElement;
}
void Sts_MetaElement_init(Sts_MetaElement* element, String name);
void Sts_MetaElement_free(Sts_MetaElement* element)


struct Sts_MetaToken {
  extends__Sts_MetaElement;
};
void_errno Sts_MetaToken_init(Sts_MetaToken* token, String name);
void Sts_MetaToken_free(Sts_MetaToken* token);

#define PNAME Sts_OwnedMetaTokens
#define PTYPE OWNER(Sts_MetaToken)
#define PFREEFUN Sts_MetaToken_free
#include "pmap.h"
#undef PNAME
#undef PTYPE
#undef PFREEFUN

#define PNAME Sts_MetaTokens
#define PTYPE WAKE(Sts_MetaToken)
#undef PFREEFUN
#include "pmap.h"
#undef PNAME
#undef PTYPE


struct Sts_MetaZone {
  extends__Sts_MetaElement;

  Sts_MetaTokens tokens;
  Sts_MetaZones expandZones;
};
void Sts_MetaZone_init(Sts_MetaZone* zone, String name);
void Sts_MetaZone_free(Sts_MetaZone* zone);

#define PNAME Sts_OwnedMetaZonesMap
#define PTYPE OWNER(Sts_MetaZone)
#define PFREEFUN Sts_MetaZone_free
#include "pmap.h"
#undef PNAME
#undef PTYPE
#undef PFREEFUN

#define PNAME Sts_MetaZones
#define PTYPE WAKE(Sts_MetaZone)
#undef PFREEFUN
#include "plist.h"
#undef PNAME
#undef PTYPE


struct Sts_MetaFile {
  Sts_MetaRegexLinks regexes;
  Sts_OwnedMetaZonesMap zones;
  Sts_OwnedMetaTokens tokens;

  Sts_MetaZone* mainZone;

  struct {
    String name;
    Sources sources;
  } properties;
};
void Sts_MetaFile_init(Sts_MetaFile* metaFile);
void Sts_MetaFile_free(Sts_MetaFile* metaFile);


void_errno Sts_MetaFile_regZone(Sts_MetaFile* metaFile, OWNER(Sts_MetaZone) zone);
Sts_MetaZone* Sts_MetaFile_getZone(Sts_MetaFile* metaFile, ViewString zoneName);
Sts_MetaZone* Sts_MetaFile_getOrCreateZone(Sts_MetaFile* metaFile, ViewString zoneName);
void_errno Sts_MetaFile_delZone(Sts_MetaFile* metaFile, ViewString zoneName);

void_errno Sts_MetaFile_regToken(Sts_MetaFile* metaFile, OWNER(Sts_MetaToken) token);
Sts_MetaToken* Sts_MetaFile_getToken(Sts_MetaFile* metaFile, ViewString tokenName);
void_errno Sts_MetaFile_delToken(Sts_MetaFile* metaFile, ViewString tokenName);
