#include "metablocks.h"

#define NAME Sts_MetaRegexes
#define TYPE Sts_MetaRegex
#define NULLV (Sts_MetaRegex) {0}
#include "gmap.c.h"
#undef NAME
#undef TYPE
#undef NULLV

#define NAME Sts_MetaEvents
#define TYPE Sts_MetaEvent
#define NULLV (Sts_MetaEvent) {0}
#include "gmap.c.h"
#undef NAME
#undef TYPE
#undef NULLV

#define NAME Sts_MetaVariables
#define TYPE Sts_MetaVariable
#define NULLV (Sts_MetaVariable) {0};
#include "glist.c.h"
#undef NAME
#undef TYPE
#undef NULLV

#define NAME Sts_MetaStaticParams
#define TYPE Sts_MetaStaticParam
#define NULLV (Sts_MetaStaticParam) {0};
#include "gmap.c.h"
#undef NAME
#undef TYPE
#undef NULLV

#define NAME Sts_MetaSuperTokenBodyBlocks
#define TYPE Sts_MetaSuperTokenBodyBlock
#define NULLV (Sts_MetaSuperTokenBodyBlock) {0}
#include "glist.c.h"
#undef NAME
#undef TYPE
#undef NULLV


void Sts_MetaRegex_init(Sts_MetaRegex* metaRegex, String regex) {
  metaRegex->regex = regex;
}
void Sts_MetaRegex_free(Sts_MetaRegex* metaRegex) {
  String_free(&regex->regex);
}
void Sts_MetaRegexes_freeElements(Sts_MetaRegexes* regexes) {
  Sts_MetaRegexes_element* el = regexes->first;
  while (el != 0) {
    Sts_MetaRegex* regex = &el->value;
    Sts_MetaRegex_free(regex);
    el = el->next;
  }
}


void Sts_MetaEvent_init(Sts_MetaEvent* event, String code) {
  event->code = code;
}
void Sts_MetaEvent_free(Sts_MetaEvent* event) {
  String_free(&event->code);
}
void Sts_MetaEvents_freeElements(Sts_MetaEvents* events) {
  Sts_MetaEvents_element* el = events->first;
  while (el != 0) {
    Sts_MetaEvent event = el->value;
    Sts_MetaEvent_free(&event);
    el = el->next;
  }
}

void Sts_MetaVariable_free(Sts_MetaVariable* variable) {
  String_free(&variable->name);
  Stss_Type_free(&variable->type);
  Stss_UntypeValue_free(&variable->defaultValue);
}
void Sts_MetaVariables_freeElements(Sts_MetaVariables* variables) {
  size_t size = variables->size;
  for (size_t i = 0; i < size; i++) {
    Sts_MetaVariable_free(&variables->array[i]);
  }
}

void Sts_MetaStaticParam_non(Sts_MetaStaticParam* staticParam) {
  staticParam->type = Sts_MetaStaticParamType_NON
}
void Sts_MetaStaticParam_name(Sts_MetaStaticParam* staticParam, String name) {
  staticParam->type = Sts_MetaStaticParamType_NAME;
  staticParam->value->name = name;
}
void Sts_MetaStaticParam_string(Sts_MetaStaticParam* staticParam, String string) {
  staticParam->type = Sts_MetaStaticParamType_STRING;
  staticParam->value->name = string;
}
void Sts_MetaStaticParam_number(Sts_MetaStaticParam* staticParam, double number) {
  staticParam->type = Sts_MetaStaticParamType_NUMBER;
  staticParam->value->name = number;
}
void Sts_MetaStaticParam_free(Sts_MetaStaticParam* staticParam) {
  Sts_MetaStaticParamType type = staticParam->type;
  if (type == Sts_MetaStaticParamType_NAME) String_free(&staticParam->value.name);
  else if (type == Sts_MetaStaticParamType_STRING) String_free(&staticParam->value.string);
}
void Sts_MetaStaticParams_freeElements(Sts_MetaStaticParams* staticParams) {
  Sts_MetaStaticParams_element* el = staticParams->first;
  while (el != 0) {
    Sts_MetaStaticParam staticParam = el->value;
    Sts_MetaStaticParam_free(&staticParam);
    el = el->next;
  }
}

void_errno Sts_MetaZone_init(Sts_MetaZone* zone, String name) {
  zone->name = name;
  Sts_MetaTokens_init(&zone->tokens);
  Sts_MetaZones_init(&zone->expandZones, 1);

  Sts_MetaStaticParams_init(&zone->staticParams);
  Sts_MetaVariables_init(&zone->variables, 1);
  Sts_MetaEvents_init(&zone->events);

  errno = 0; return;
}
void Sts_MetaZone_free(Sts_MetaZone* zone) {
  String_free(&zone->name);
  Sts_MetaTokens_free(&zone->tokens);
  Sts_MetaZones_free(&zone->expandZones);

  Sts_MetaStaticParams_freeElements(&zone->staticParams);
  Sts_MetaStaticParams_free(&zone->staticParams);
  Sts_MetaVariables_freeElements(&zone->variables);
  Sts_MetaVariables_free(&zone->variables);
  Sts_MetaEvents_freeElements(&zone->events);
  Sts_MetaEvents_free(&zone->events);
}
void Sts_MetaZonesMap_freeElements(Sts_MetaZonesMap* zonesMap) {
  Sts_MetaZonesMap_element* el = zonesMap->first;
  while (el != 0) {
    Sts_MetaZone* zone = el->value;
    Sts_MetaZone_free(zone);
    el = el->next;
  }
}

void_errno Sts_MetaToken_init(Sts_MetaToken* token, String name) {
  // if (Sts_MetaTokens_contains(tokens, name)) {
  //   errno = 1; return;
  // }
  token->name = name;
  token->regex = (String) {0};
  Sts_MetaZones_init(&token->parentZones, 100);
  token->ghost = false;
  token->openZone = 0;
  token->setZone = 0;
  token->isCloseZone = false;

  Sts_MetaStaticParams_init(&token->staticParams);
  Sts_MetaVariables_init(&token->variables, 1);
  Sts_MetaEvents_init(&token->events);

  errno = 0; return;
}
void Sts_MetaToken_free(Sts_MetaToken* token) {
  String_free(&token->name);
  String_free(&token->regex);
  Sts_MetaZones_free(&token->parentZones);

  Sts_MetaStaticParams_freeElements(&token->staticParams);
  Sts_MetaStaticParams_free(&token->staticParams);
  Sts_MetaVariables_freeElements(&token->variables);
  Sts_MetaVariables_free(&token->variables);
  Sts_MetaEvents_freeElements(&token->events);
  Sts_MetaEvents_free(&token->events);
}
void Sts_MetaTokens_freeElements(Sts_MetaTokens* tokens) {
  Sts_MetaTokens_element* el = tokens->first;
  while (el != 0) {
    Sts_MetaToken* token = el->value;
    Sts_MetaToken_free(token);
    el = el->next;
  }
}

void Sts_MetaSuperTokenBodyBlock_init(Sts_MetaSuperTokenBodyBlock* block, Sts_MetaToken* token) {
  block->token = token;
  block->name = (String) {0};
  block->strict = true;
}
void Sts_MetaSuperTokenBodyBlock_free(Sts_MetaSuperTokenBodyBlock* block) {
  String_free(&block->name);
}
void Sts_MetaSuperTokenBodyBlocks_freeElements(Sts_MetaSuperTokenBodyBlocks* blocks) {
  size_t size = blocks->size;
  for (size_t i = 0; i < size; i++) {
    Sts_MetaSuperTokenBodyBlock_free(&blocks->array[i]);
  }
}

void Sts_MetaSuperTokenBody_init(Sts_MetaSuperTokenBody* body, Sts_MetaSuperTokenBodyBlocks blocks) {
  body->blocks = blocks;
  body->ghost = false;
}
void Sts_MetaSuperTokenBody_free(Sts_MetaSuperTokenBody* body) {
  Sts_MetaSuperTokenBodyBlocks_freeElements(&body->blocks);
}

void_errno Sts_MetaSuperToken_init(Sts_MetaSuperToken* superToken, String name) {
  superToken->name = name;
  superToken->ghost = false;
  superToken->openTrigger = (String) {0};
  superToken->closeTrigger = (String) {0};
  superToken->body = 0;

  Sts_MetaStaticParams_init(&superToken->staticParams);
  Sts_MetaVariables_init(&superToken->variables, 1);
  Sts_MetaEvents_init(&superToken->events);
  errno = 0; return;
}
void Sts_MetaSuperToken_free(Sts_MetaSuperToken* superToken) {
  String_free(&superToken->name);
  String_free(&superToken->openTrigger);
  String_free(&superToken->closeTrigger);
  Sts_MetaSuperTokenBody_free(superToken->body);

  Sts_MetaStaticParams_freeElements(&superToken->staticParams);
  Sts_MetaStaticParams_free(&superToken->staticParams);
  Sts_MetaVariables_freeElements(&superToken->variables);
  Sts_MetaVariables_free(&superToken->variables);
  Sts_MetaEvents_freeElements(&superToken->events);
  Sts_MetaEvents_free(&superToken->events);
}
void Sts_MetaSuperTokens_freeElements(Sts_MetaSuperTokens* tokens) {
  Sts_MetaSuperTokens_element* el = tokens->first;
  while (el != 0) {
    Sts_MetaSuperToken* token = el->value;
    Sts_MetaSuperToken_free(token);
    el = el->next;
  }
}

void Sts_MetaFile_init(Sts_MetaFile* metaFile) {
  Sts_MetaRegexes_init(&metaFile->regexes);
  Sts_MetaZonesMap_init(&metaFile->zones);
  Sts_MetaTokens_init(&metaFile->tokens);
  Sts_MetaSuperTokens_init(&metaFile->superTokens);
  metaFile->mainZone = 0;
  metaFile->properties.name = (String) {0};
  metaFile->properties.sources = (Sources) {0};
}
void Sts_MetaFile_free(Sts_MetaFile* metaFile) {
  Sts_MetaRegexes_freeElements(&metaFile->regexes);
  Sts_MetaRegexes_free(&metaFile->regexes);
  Sts_MetaZonesMap_freeElements(&metaFile->zones);
  Sts_MetaZonesMap_free(&metaFile->zones);
  Sts_MetaTokens_freeElements(&metaFile->tokens);
  Sts_MetaTokens_free(&metaFile->tokens);
  Sts_MetaSuperTokens_freeElements(&metaFile->superTokens);
  Sts_MetaSuperTokens_free(&metaFile->superTokens);
  String_free(&metaFile->properties.name);
  Sources_free(&metaFile->properties.sources);
}


void_errno Sts_MetaFile_regZone(Sts_MetaFile* metaFile, Sts_MetaZone* zone) {
  if (Sts_MetaZonesMap_contains(metaFile->zones, zone->name)) {
    errno = 1; return;
  }
  Sts_MetaZonesMap_set(metaFile->zones, zone->name, zone);
  errno = 0; return;
}
void_errno Sts_MetaFile_regToken(Sts_MetaFile* metaFile, Sts_MetaToken* token) {
  if (Sts_MetaZonesMap_contains(metaFile->zones, token->name)) {
    errno = 1; return;
  }
  Sts_MetaZonesMap_set(metaFile->zones, token->name, token);
  errno = 0; return;
}
void_errno Sts_MetaFile_regSuperToken(Sts_MetaFile* metaFile, Sts_MetaSuperToken* superToken) {
  if (Sts_MetaSuperTokens_contains(metaFile->superTokens, superToken->name)) {
    errno = 1; return;
  }
  Sts_MetaSuperTokens_set(metaFile->superTokens, superToken->name, superToken);
  errno = 0; return;
}

Sts_MetaZone* Sts_MetaFile_getOrCreateZone(Sts_MetaFile* metaFile, const String name) {
  Sts_MetaZone* zone = Sts_MetaZonesMap_get(metaFile->zones, name);
  if (errno != 0) {
    Sts_MetaZone_init(zone);
    Sts_MetaZonesMap_set(metaFile->zones, name, zone);
  }
  return zone;
}
