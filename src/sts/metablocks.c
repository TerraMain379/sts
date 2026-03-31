#include "metablocks.h"

#define NAME Sts_MetaRegexLinks
#define TYPE Sts_MetaRegex
#define NULLV (Sts_MetaRegex) {0}
#define FREEFUN Sts_MetaRegex_free
#include "gmap.c.h"
#undef NAME
#undef TYPE
#undef NULLV
#undef FREEFUN

#define NAME Sts_MetaEvents
#define TYPE Sts_MetaEvent
#define NULLV (Sts_MetaEvent) {0}
#define FREEFUN Sts_MetaEvent_free
#include "gmap.c.h"
#undef NAME
#undef TYPE
#undef NULLV
#undef FREEFUN

#define NAME Sts_MetaElementVariables
#define TYPE Sts_MetaElementVariable
#define NULLV (Sts_MetaElementVariable) {0};
#define FREEFUN Sts_MetaElementVariable_free
#include "gmap.c.h"
#undef NAME
#undef TYPE
#undef NULLV
#undef FREEFUN

#define NAME Sts_MetaElementStaticParams
#define TYPE Sts_MetaElementStaticParam
#define NULLV (Sts_MetaElementStaticParam) {0};
#define FREEFUN Sts_MetaElementStaticParam_free
#include "gmap.c.h"
#undef NAME
#undef TYPE
#undef NULLV
#undef FREEFUN

#define PNAME Sts_OwnedMetaTokens
#define PTYPE OWNER(Sts_MetaToken)
#define PFREEFUN Sts_MetaToken_free
#define BASE_MAP Map
#include "pmap.c.h"
#undef PNAME
#undef PTYPE
#undef PFREEFUN
#undef BASE_MAP

#define PNAME Sts_MetaTokens
#define PTYPE WEAK(Sts_MetaToken)
#undef PFREEFUN
#define BASE_MAP ConstMap
#include "pmap.c.h"
#undef PNAME
#undef PTYPE
#undef BASE_MAP

#define PNAME Sts_OwnedMetaZonesMap
#define PTYPE OWNER(Sts_MetaZone)
#define PFREEFUN Sts_MetaZone_free
#define BASE_MAP Map
#include "pmap.c.h"
#undef PNAME
#undef PTYPE
#undef PFREEFUN
#undef BASE_MAP

#define PNAME Sts_MetaZones
#define PTYPE WEAK(Sts_MetaZone)
#undef PFREEFUN
#define BASE_LIST ConstList
#include "plist.c.h"
#undef PNAME
#undef PTYPE
#undef BASE_LIST


void Sts_MetaRegex_init(Sts_MetaRegex* metaRegex, String regex) {
  metaRegex->regex = regex;
}
void Sts_MetaRegex_free(Sts_MetaRegex* metaRegex) {
  String_free(&metaRegex->regex);
}

void Sts_MetaEvent_init(Sts_MetaEvent* event, String code) {
  event->code = code;
}
void Sts_MetaEvent_free(Sts_MetaEvent* event) {
  String_free(&event->code);
}

void Sts_MetaElementVariable_init(Sts_MetaElementVariable* variable) {
  // todo
}
void Sts_MetaElementVariable_free(Sts_MetaElementVariable* variable) {
  Stss_Type_free(&variable->type);
  Stss_UntypeValue_free(variable->value);
}

void Sts_MetaElementStaticParam_init(Sts_MetaElementStaticParam* staticParam) {
  // todo
}
void Sts_MetaElementStaticParam_free(Sts_MetaElementStaticParam* staticParam) {
  Stss_Type_free(&staticParam->type);
  Stss_UntypeValue_free(staticParam->value);
}

void Sts_MetaElement_init(Sts_MetaElement* element, String name) {
  element->name = name;
  Sts_MetaElementStaticParams_init(&element->params);
  Sts_MetaElementVariables_init(&element->variables);
  Sts_MetaEvents_init(&element->events);
}
void Sts_MetaElement_free(Sts_MetaElement* element) {
  String_free(&element->name);
  Sts_MetaElementStaticParams_freeElements(&element->params);
  Sts_MetaElementStaticParams_free(&element->params);
  Sts_MetaElementVariables_freeElements(&element->variables);
  Sts_MetaElementVariables_free(&element->variables);
  Sts_MetaEvents_freeElements(&element->events);
  Sts_MetaEvents_free(&element->events);
}

void Sts_MetaToken_init(Sts_MetaToken* token, String name) {
  Sts_MetaElement_init((Sts_MetaElement*) token, name);
}
void Sts_MetaToken_free(Sts_MetaToken* token) {
  Sts_MetaElement_free((Sts_MetaElement*) token);
}


void Sts_MetaZone_init(Sts_MetaZone* zone, String name) {
  Sts_MetaElement_init((Sts_MetaElement*) zone, name);
  Sts_MetaTokens_init(&zone->tokens);
  Sts_MetaZones_init(&zone->expandZones, 1);
}
void Sts_MetaZone_free(Sts_MetaZone* zone) {
  Sts_MetaElement_free((Sts_MetaElement*) zone);
  Sts_MetaTokens_freeElements(&zone->tokens);
  Sts_MetaTokens_free(&zone->tokens);
  Sts_MetaZones_freeElements(&zone->expandZones);
  Sts_MetaZones_free(&zone->expandZones);
}

void Sts_MetaFile_init(Sts_MetaFile* metaFile) {
  Sts_MetaRegexLinks_init(&metaFile->regexes);
  Sts_OwnedMetaZonesMap_init(&metaFile->zones);
  Sts_OwnedMetaTokens_init(&metaFile->tokens);
  metaFile->mainZone = null;
  metaFile->properties.name = (String) {0};
  metaFile->properties.sources = (Sources) {0};
}
void Sts_MetaFile_free(Sts_MetaFile* metaFile) {
  Sts_MetaRegexLinks_freeElements(&metaFile->regexes);
  Sts_MetaRegexLinks_free(&metaFile->regexes);
  Sts_OwnedMetaZonesMap_freeElements(&metaFile->zones);
  Sts_OwnedMetaZonesMap_free(&metaFile->zones);
  Sts_OwnedMetaTokens_freeElements(&metaFile->tokens);
  Sts_OwnedMetaTokens_free(&metaFile->tokens);
  String_free(&metaFile->properties.name);
  Sources_free(&metaFile->properties.sources);
}


void_errno Sts_MetaFile_regZone(Sts_MetaFile* metaFile, OWNER(Sts_MetaZone) zone) {
  if (Sts_OwnedMetaZonesMap_contains(&metaFile->zones, (ViewString*) &zone->name)) {
    errno = 1; return;
  }
  Sts_OwnedMetaZonesMap_set(&metaFile->zones, (ViewString*) &zone->name, zone);
  errno = 0; return;
}
Sts_MetaZone* Sts_MetaFile_getZone(Sts_MetaFile* metaFile, ViewString* name) {
  Sts_MetaZone** zoneP = Sts_OwnedMetaZonesMap_get(&metaFile->zones, name);
  if (errno != 0 || zoneP == null) return 0;
  return *zoneP;
}
Sts_MetaZone* Sts_MetaFile_getOrCreateZone(Sts_MetaFile* metaFile, ViewString* name) {
  Sts_MetaZone** zoneP = Sts_OwnedMetaZonesMap_get(&metaFile->zones, name);
  if (errno != 0 || zoneP == null) {
    Sts_MetaZone* zone = A_loc(sizeof(Sts_MetaZone));
    Sts_MetaZone_init(zone, String_copy(name));
    Sts_OwnedMetaZonesMap_set(&metaFile->zones, name, zone);
    return zone;
  }
  return *zoneP;
}
void_errno Sts_MetaFile_delZone(Sts_MetaFile* metaFile, ViewString* name) {
  Sts_OwnedMetaZonesMap_remove(&metaFile->zones, name);
}

void_errno Sts_MetaFile_regToken(Sts_MetaFile* metaFile, Sts_MetaToken* token) {
  if (Sts_OwnedMetaTokens_contains(&metaFile->tokens, (ViewString*) &token->name)) {
    errno = 1; return;
  }
  Sts_OwnedMetaTokens_set(&metaFile->tokens, (ViewString*) &token->name, token);
  errno = 0; return;
}
Sts_MetaToken* Sts_MetaFile_getToken(Sts_MetaFile* metaFile, ViewString* name) {
  Sts_MetaToken** tokenP = Sts_OwnedMetaTokens_get(&metaFile->tokens, name);
  if (errno != 0 || tokenP == null) return 0;
  return *tokenP;
}
void_errno Sts_MetaFile_delToken(Sts_MetaFile* metaFile, ViewString* name) {
  Sts_OwnedMetaTokens_remove(&metaFile->tokens, name);
}
