#include "metablocks.h"

#define NAME Sts_MetaRegexLinks
#define TYPE OWNER(Sts_MetaRegex)
#define NULLV (Sts_MetaRegex) {0}
#define FREEFUN Sts_MetaRegex_free
#include "gmap.c.h"
#undef NAME
#undef TYPE
#undef NULLV
#undef FREEFUN

#define NAME Sts_MetaEvents
#define TYPE OWNER(Sts_MetaEvent)
#define NULLV (Sts_MetaEvent) {0}
#define FREEFUN Sts_MetaEvent_free
#include "gmap.c.h"
#undef NAME
#undef TYPE
#undef NULLV
#undef FREEFUN

#define NAME Sts_MetaElementVariables
#define TYPE OWNER(Sts_MetaElementVariable)
#define NULLV (Sts_MetaElementVariable) {0};
#define FREEFUN Sts_MetaElementVariable_free
#include "gmap.c.h"
#undef NAME
#undef TYPE
#undef NULLV
#undef FREEFUN

#define NAME Sts_MetaElementStaticParams
#define TYPE OWNER(Sts_MetaElementStaticParam)
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

#define NAME Sts_MetaDeclarationValueList
#define TYPE Sts_MetaDeclarationValue
#define NULLV (Sts_MetaDeclarationValue) {0}
#define FREEFUN Sts_MetaDeclarationValue_free
#include "glist.c.h"
#undef NAME
#undef TYPE
#undef NULLV
#undef FREEFUN

#define NAME Sts_MetaSuperRegexDeclarationElements
#define TYPE Sts_MetaSuperRegexDeclarationElement
#define NULLV (Sts_MetaSuperRegexDeclarationElement) {0}
#define FREEFUN Sts_MetaSuperRegexDeclarationElement_free
#include "glist.c.h"
#undef NAME
#undef TYPE
#undef NULLV
#undef FREEFUN

#define PNAME Sts_MetaDeclarationList
#define PTYPE OWNER(Sts_MetaDeclaration)
#define PFREEFUN Sts_MetaDeclaration_free
#define BASE_LIST List
#include "plist.c.h"
#undef PNAME
#undef PTYPE
#undef PFREEFUN
#undef BASE_LIST

#define PNAME Sts_MetaDeclarationValuesWeakList
#define PTYPE WEAK(Sts_MetaDeclarationValue)
#undef PFREEFUN
#define BASE_LIST ConstList
#include "plist.c.h"
#undef PNAME
#undef PTYPE
#undef BASE_LIST
dec_print(Sts_MetaDeclarationValuesWeakList);

#define NAME Sts_MetaDeclarationValuesLinks
#define TYPE Sts_MetaDeclarationValuesWeakList
#define NULLV (Sts_MetaDeclarationValuesWeakList) {0}
#define FREEFUN Sts_MetaDeclarationValuesWeakList_free
#include "gmap.c.h"
#undef NAME
#undef TYPE
#undef NULLV
#undef FREEFUN

#define NAME Sts_MetaDeclarationsBlocks
#define TYPE Sts_MetaDeclarationsBlock
#define NULLV (Sts_MetaDeclarationsBlock) {0}
#define FREEFUN Sts_MetaDeclarationsBlock_free
#include "glist.c.h"
#undef NAME
#undef TYPE
#undef NULLV
#undef FREEFUN


Sts_MetaDeclarationValuesWeakList* Sts_MetaDeclarationValuesLinks_getOrCreate(Sts_MetaDeclarationValuesLinks* valuesLinks, ViewString key) {
  if (!Sts_MetaDeclarationValuesLinks_contains(valuesLinks, key)) {
    Sts_MetaDeclarationValuesWeakList list;
    Sts_MetaDeclarationValuesWeakList_init(&list, 2);
    Sts_MetaDeclarationValuesLinks_set(valuesLinks, key, list);
  }
  return Sts_MetaDeclarationValuesLinks_get(valuesLinks, key);
}
void Sts_MetaDeclarationValuesLinks_registerDeclaratonValue(Sts_MetaDeclarationValuesLinks* valuesLinks, WEAK(Sts_MetaDeclarationValue*) decValue) {
  Sts_MetaDeclarationValuesWeakList* valuesWeakList = Sts_MetaDeclarationValuesLinks_getOrCreate(
    valuesLinks,
    ViewString_by(decValue->value.linkName)
  );
  Sts_MetaDeclarationValuesWeakList_add(valuesWeakList, decValue);
}


void Sts_MetaRegex_init(Sts_MetaRegex* metaRegex, OWNER(String) regex) {
  metaRegex->regex = regex;
}
void Sts_MetaRegex_free(Sts_MetaRegex* metaRegex) {
  String_free(&metaRegex->regex);
}

void Sts_MetaEvent_init(Sts_MetaEvent* event, OWNER(String) code) {
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

void Sts_MetaElement_init(Sts_MetaElement* element, OWNER(String) name) {
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

void Sts_MetaToken_init(Sts_MetaToken* token, OWNER(String) name) {
  Sts_MetaElement_init((Sts_MetaElement*) token, name);
}
void Sts_MetaToken_free(Sts_MetaToken* token) {
  Sts_MetaElement_free((Sts_MetaElement*) token);
}

void Sts_MetaDeclarationValue_free(Sts_MetaDeclarationValue* decValue) {
  Sts_MetaDeclarationValueType type = decValue->type;
  if (type == Sts_MetaDeclarationValueType_NAME) {
    String_free(&decValue->value.name);
  }
  else if (type == Sts_MetaDeclarationValueType_STRING) {
    String_free(&decValue->value.string);
  }
  else if (type == Sts_MetaDeclarationValueType_EXPRESSION) {
    Sts_MetaDeclarationExpression_free(decValue->value.expression);
    A_free(decValue->value.expression);
  }
  else if (type == Sts_MetaDeclarationValueType_LINK) {
    String_free(&decValue->value.linkName);
  }
}
void Sts_MetaDeclarationExpression_free(Sts_MetaDeclarationExpression* decExpression) {
  Sts_MetaDeclarationValue_free(&decExpression->value1);
  Sts_MetaDeclarationValue_free(&decExpression->value2);
}
void Sts_MetaParamDeclaration_free(Sts_MetaParamDeclaration* paramDec) {
  Sts_MetaDeclarationValue_free(&paramDec->name);
  Sts_MetaDeclarationValueList_freeElements(&paramDec->values);
  Sts_MetaDeclarationValueList_free(&paramDec->values);
}
void Sts_MetaVariableDeclaration_free(Sts_MetaVariableDeclaration* variableDec) {
  Sts_MetaDeclarationValue_free(&variableDec->name);
  Sts_MetaDeclarationValue_free(&variableDec->value);
  Sts_MetaDeclarationValue_free(&variableDec->typing);
}
void Sts_MetaEventDeclaration_free(Sts_MetaEventDeclaration* eventDec) {
  Sts_MetaDeclarationValue_free(&eventDec->name);
  Sts_MetaDeclarationValue_free(&eventDec->event);
}
void Sts_MetaZoneExtendDeclaration_free(Sts_MetaZoneExtendDeclaration* zoneExtendDec) {
  Sts_MetaDeclarationValue_free(&zoneExtendDec->zoneName);
}
void Sts_MetaSuperRegexDeclarationElement_free(Sts_MetaSuperRegexDeclarationElement* regexDecElement) {
  Sts_MetaDeclarationValue_free(&regexDecElement->token);
  Sts_MetaDeclarationValue_free(&regexDecElement->name);
}
void Sts_MetaSuperRegexDeclaration_free(Sts_MetaSuperRegexDeclaration* regexDec) {
  Sts_MetaSuperRegexDeclarationElements_freeElements(&regexDec->elements);
  Sts_MetaSuperRegexDeclarationElements_free(&regexDec->elements);
}
void Sts_MetaDeclaration_free(Sts_MetaDeclaration* declaration) {
  Sts_MetaDeclarationType type = declaration->type;
  if (type == Sts_MetaDeclarationType_PARAM) {
    Sts_MetaParamDeclaration_free(&declaration->value.param);
  }
  else if (type == Sts_MetaDeclarationType_VARIABLE) {
    Sts_MetaVariableDeclaration_free(&declaration->value.variable);
  }
  else if (type == Sts_MetaDeclarationType_EVENT) {
    Sts_MetaEventDeclaration_free(&declaration->value.event);
  }
  else if (type == Sts_MetaDeclarationType_ZONE_EXTEND) {
    Sts_MetaZoneExtendDeclaration_free(&declaration->value.zoneExtend);
  }
  else if (type == Sts_MetaDeclarationType_SUPER_REGEX) {
    Sts_MetaSuperRegexDeclaration_free(&declaration->value.superRegex);
  }
}

void Sts_MetaDeclarationsBlock_init(Sts_MetaDeclarationsBlock* decBlock, Sts_MetaDeclarationsBlockType type) {
  decBlock->name = (String) {0};
  decBlock->type = type;
  Sts_MetaDeclarationList_init(&decBlock->declarations, 5);
  StringList_init(&decBlock->linkNames, 1);
  Sts_MetaDeclarationValuesLinks_init(&decBlock->links);
}
void Sts_MetaDeclarationsBlock_free(Sts_MetaDeclarationsBlock* decBlock) {
  String_free(&decBlock->name);
  Sts_MetaDeclarationList_freeElements(&decBlock->declarations);
  Sts_MetaDeclarationList_free(&decBlock->declarations);
  StringList_freeElements(&decBlock->linkNames);
  StringList_free(&decBlock->linkNames);
  Sts_MetaDeclarationValuesLinks_freeElements(&decBlock->links);
  Sts_MetaDeclarationValuesLinks_free(&decBlock->links);
}

void Sts_MetaZone_init(Sts_MetaZone* zone, OWNER(String) name) {
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
  Sts_MetaDeclarationsBlocks_init(&metaFile->decBlocks, 50);
  Sts_MetaRegexLinks_init(&metaFile->regexes);
  Sts_OwnedMetaZonesMap_init(&metaFile->zones);
  Sts_OwnedMetaTokens_init(&metaFile->tokens);
  metaFile->mainZone = null;
  metaFile->properties.name = (String) {0};
  metaFile->properties.sources = (Sources) {0};
}
void Sts_MetaFile_free(Sts_MetaFile* metaFile) {
  Sts_MetaDeclarationsBlocks_freeElements(&metaFile->decBlocks);
  Sts_MetaDeclarationsBlocks_free(&metaFile->decBlocks);
  Sts_MetaRegexLinks_freeElements(&metaFile->regexes);
  Sts_MetaRegexLinks_free(&metaFile->regexes);
  Sts_OwnedMetaZonesMap_freeElements(&metaFile->zones);
  Sts_OwnedMetaZonesMap_free(&metaFile->zones);
  Sts_OwnedMetaTokens_freeElements(&metaFile->tokens);
  Sts_OwnedMetaTokens_free(&metaFile->tokens);
  String_free(&metaFile->properties.name);
  Sources_free(&metaFile->properties.sources);
}


void_errno Sts_MetaFile_regZone(Sts_MetaFile* metaFile, OWNER(Sts_MetaZone*) zone) {
  if (Sts_OwnedMetaZonesMap_contains(&metaFile->zones, ViewString_by(zone->name))) {
    errno = 1; return;
  }
  Sts_OwnedMetaZonesMap_set(&metaFile->zones, ViewString_by(zone->name), zone);
  errno = 0; return;
}
Sts_MetaZone* Sts_MetaFile_getZone(Sts_MetaFile* metaFile, ViewString name) {
  return Sts_OwnedMetaZonesMap_get(&metaFile->zones, name);
}
Sts_MetaZone* Sts_MetaFile_getOrCreateZone(Sts_MetaFile* metaFile, ViewString name) {
  Sts_MetaZone* zoneP = Sts_OwnedMetaZonesMap_get(&metaFile->zones, name);
  if (errno != 0 || zoneP == null) {
    Sts_MetaZone* zone = A_loc(sizeof(Sts_MetaZone));
    Sts_MetaZone_init(zone, String_copy(name));
    Sts_OwnedMetaZonesMap_set(&metaFile->zones, name, zone);
    return zone;
  }
  return zoneP;
}
void_errno Sts_MetaFile_delZone(Sts_MetaFile* metaFile, ViewString name) {
  Sts_OwnedMetaZonesMap_remove(&metaFile->zones, name);
}

void_errno Sts_MetaFile_regToken(Sts_MetaFile* metaFile, OWNER(Sts_MetaToken*) token) {
  if (Sts_OwnedMetaTokens_contains(&metaFile->tokens, ViewString_by(token->name))) {
    errno = 1; return;
  }
  Sts_OwnedMetaTokens_set(&metaFile->tokens, ViewString_by(token->name), token);
  errno = 0; return;
}
Sts_MetaToken* Sts_MetaFile_getToken(Sts_MetaFile* metaFile, ViewString name) {
  return Sts_OwnedMetaTokens_get(&metaFile->tokens, name);
}
void_errno Sts_MetaFile_delToken(Sts_MetaFile* metaFile, ViewString name) {
  Sts_OwnedMetaTokens_remove(&metaFile->tokens, name);
}
