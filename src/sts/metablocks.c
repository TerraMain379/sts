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

#define NAME Sts_MetaVariables
#define TYPE Sts_MetaVariable
#define NULLV (Sts_MetaVariable) {0};
#define FREEFUN Sts_MetaVariable_free
#include "glist.c.h"
#undef NAME
#undef TYPE
#undef NULLV
#undef FREEFUN

#define NAME Sts_MetaStaticParams
#define TYPE Sts_MetaStaticParam
#define NULLV (Sts_MetaStaticParam) {0};
#define FREEFUN Sts_MetaStaticParam_free
#include "gmap.c.h"
#undef NAME
#undef TYPE
#undef NULLV
#undef FREEFUN


void Sts_MetaRegex_init(Sts_MetaRegex* metaRegex, String regex) {
  metaRegex->regex = regex;
}
void Sts_MetaRegex_free(Sts_MetaRegex* metaRegex) {
  String_free(&regex->regex);
}

void Sts_MetaEvent_init(Sts_MetaEvent* event, String code) {
  event->code = code;
}
void Sts_MetaEvent_free(Sts_MetaEvent* event) {
  String_free(&event->code);
}

void Sts_MetaVariable_init(Sts_MetaVariable* variable) {
  // todo
}
void Sts_MetaVariable_free(Sts_MetaVariable* variable) {
  Stss_Type_free(&variable->type);
  Stss_UntypeValue_free(&variable->defaultValue);
}

void Sts_MetaStaticParam_init(Sts_MetaStaticParam* staticParam) {
  // todo
}
void Sts_MetaStaticParam_free(Sts_MetaStaticParam* staticParam) {
  Sts_MetaStaticParamType type = staticParam->type;
  if (type == Sts_MetaStaticParamType_NAME) String_free(&staticParam->value.name);
  else if (type == Sts_MetaStaticParamType_STRING) String_free(&staticParam->value.string);
}

void Sts_MetaElement_init(Sts_MetaElement* element, String name) {
  element->name = name;
  Sts_MetaElementStaticParams_init(element->params);
  Sts_MetaElementVariables_init(element->variables);
  Sts_MetaEvents_init(element->events);
}
void Sts_MetaElement_free(Sts_MetaElement* element) {
  String_free(element->name);
  Sts_MetaElementStaticParams_freeElements(element->params);
  Sts_MetaElementStaticParams_free(element->params);
  Sts_MetaElementVariables_freeElements(element->variables);
  Sts_MetaElementVariables_free(element->variables);
  Sts_MetaEvents_freeElements(element->events);
  Sts_MetaEvents_free(element->events);
}

void Sts_MetaToken_init(Sts_MetaToken* token, String name) {
  Sts_MetaElement_init((Sts_MetaElement*) zone);
}
void Sts_MetaToken_free(Sts_MetaToken* token) {
  Sts_MetaElement_free((Sts_MetaElement*) zone);
}


void Sts_MetaZone_init(Sts_MetaZone* zone, String name) {
  Sts_MetaElement_init((Sts_MetaElement*) zone);
  Sts_MetaTokens_init(&zone->tokens);
  Sts_MetaZones_init(&zone->expandZones, 1);
}
void Sts_MetaZone_free(Sts_MetaZone* zone) {
  Sts_MetaElement_free((Sts_MetaElement*) zone);
  Sts_MetaTokens_free(&zone->tokens);
  Sts_MetaZones_free(&zone->expandZones);
}

void Sts_MetaFile_init(Sts_MetaFile* metaFile) {
  Sts_MetaRegexLink_init(&metaFile->regexes);
  Sts_MetaZonesMap_init(&metaFile->zones);
  Sts_MetaTokens_init(&metaFile->tokens);
  metaFile->mainZone = 0;
  metaFile->properties.name = (String) {0};
  metaFile->properties.sources = (Sources) {0};
}
void Sts_MetaFile_free(Sts_MetaFile* metaFile) {
  Sts_MetaRegexLink_freeElements(&metaFile->regexes);
  Sts_MetaRegexLink_free(&metaFile->regexes);
  Sts_MetaZonesMap_freeElements(&metaFile->zones);
  Sts_MetaZonesMap_free(&metaFile->zones);
  Sts_MetaTokens_freeElements(&metaFile->tokens);
  Sts_MetaTokens_free(&metaFile->tokens);
  String_free(&metaFile->properties.name);
  Sources_free(&metaFile->properties.sources);
}


void_errno Sts_MetaFile_regZone(Sts_MetaFile* metaFile, OWNER(Sts_MetaZone) zone) {
  if (Sts_MetaZonesMap_contains(metaFile->zones, zone->name)) {
    errno = 1; return;
  }
  Sts_MetaZonesMap_set(metaFile->zones, zone->name, zone);
  errno = 0; return;
}
Sts_MetaZone* Sts_MetaFile_getZone(Sts_MetaFile* metaFile, ViewString zoneName) {
  return Sts_MetaZonesMap_get(metaFile->zones, zoneName);
}
Sts_MetaZone* Sts_MetaFile_getOrCreateZone(Sts_MetaFile* metaFile, ViewString name) {
  Sts_MetaZone* zone = Sts_MetaZonesMap_get(metaFile->zones, zoneName);
  if (zone == 0) {
    zone = A_loc(sizeof(Sts_MetaZone));
    Sts_MetaZone_init(zone, zoneName);
    Sts_MetaZonesMap_set(metaFile->zones, zoneName, zone);
  }
  return zone;
}
void_errno Sts_MetaFile_delZone(Sts_MetaFile* metaFile, ViewString zoneName) {
  Sts_MetaZonesMap_remove(metaFile->zones, zoneName);
}

void_errno Sts_MetaFile_regToken(Sts_MetaFile* metaFile, Sts_MetaToken* token) {
  if (Sts_OwnedMetaTokens_contains(metaFile->tokens, token->name)) {
    errno = 1; return;
  }
  Sts_OwnedMetaTokens_set(metaFile->tokens, token->name, token);
  errno = 0; return;
}
Sts_MetaToken* Sts_MetaFile_getToken(Sts_MetaFile* metaFile, ViewString tokenName) {
  return Sts_OwnedMetaTokens_get(metaFile->tokens, tokenName);
}
void_errno Sts_MetaFile_delToken(Sts_MetaFile* metaFile, ViewString tokenName) {
  Sts_OwnedMetaTokens_remove(metaFile->tokens, tokenName);
}
