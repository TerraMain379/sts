#pragma once

#include "utils.h"
#include "string.h"
#include "sources.h"
#include "stss.h"

typedef struct Sts_MetaRegex Sts_MetaRegex;
typedef struct Sts_MetaEvent Sts_MetaEvent;
typedef struct Sts_MetaVariable Sts_MetaVariable;
typedef enum Sts_MetaStaticParamType Sts_MetaStaticParamType;
typedef struct Sts_MetaStaticParam Sts_MetaStaticParam;
typedef struct Sts_MetaZone Sts_MetaZone;
typedef struct Sts_MetaToken Sts_MetaToken;
typedef struct Sts_MetaSuperTokenBodyBlock Sts_MetaSuperTokenBodyBlock;
typedef struct Sts_MetaSuperTokenBody Sts_MetaSuperTokenBody;
typedef struct Sts_MetaSuperToken Sts_MetaSuperToken;
typedef struct Sts_MetaFile Sts_MetaFile;




struct Sts_MetaRegex {
  String regex;
};
void Sts_MetaRegex_init(Sts_MetaRegex* metaRegex, String regex);
void Sts_MetaRegex_free(Sts_MetaRegex* metaRegex);

#define NAME Sts_MetaRegexes
#define TYPE Sts_MetaRegex
#define NULLV (Sts_MetaRegex) {0}
#include "gmap.h"
#undef NAME
#undef TYPE
#undef NULLV
void Sts_MetaRegexes_freeElements(Sts_MetaRegexes* regexes);


struct Sts_MetaEvent {
  String code;
};
void Sts_MetaEvent_init(Sts_MetaEvent* event, String code);
void Sts_MetaEvent_free(Sts_MetaEvent* event);

#define NAME Sts_MetaEvents
#define TYPE Sts_MetaEvent
#define NULLV (Sts_MetaEvent) {0}
#include "gmap.h"
#undef NAME
#undef TYPE
#undef NULLV
void Sts_MetaEvents_freeElements(Sts_MetaEvents* events);


struct Sts_MetaVariable {
  String name;
  Stss_Type type;
  Stss_UntypeValue defaultValue;
};
void Sts_MetaVariable_free(Sts_MetaVariable* variable);

#define NAME Sts_MetaVariables
#define TYPE Sts_MetaVariable
#define NULLV (Sts_MetaVariable) {0};
#include "glist.h"
#undef NAME
#undef TYPE
#undef NULLV
void Sts_MetaVariables_freeElements(Sts_MetaVariables* variables);


enum Sts_MetaStaticParamType {
  Sts_MetaStaticParamType_NON = 0,
  Sts_MetaStaticParamType_NAME,
  Sts_MetaStaticParamType_STRING,
  Sts_MetaStaticParamType_NUMBER
};

struct Sts_MetaStaticParam {
  union {
    String name;
    String string;
    double number;
  } value;
  Sts_MetaStaticParamType type;
};
void Sts_MetaStaticParam_non(Sts_MetaStaticParam* staticParam);
void Sts_MetaStaticParam_name(Sts_MetaStaticParam* staticParam, String name);
void Sts_MetaStaticParam_string(Sts_MetaStaticParam* staticParam, String string);
void Sts_MetaStaticParam_number(Sts_MetaStaticParam* staticParam, double number);
void Sts_MetaStaticParam_free(Sts_MetaStaticParam* staticParam);

#define NAME Sts_MetaStaticParams
#define TYPE Sts_MetaStaticParam
#define NULLV (Sts_MetaStaticParam) {0};
#include "gmap.h"
#undef NAME
#undef TYPE
#undef NULLV
void Sts_MetaStaticParams_freeElements(Sts_MetaStaticParams* staticParams);


// moved to resolve declaration order constraints
  #define PNAME Sts_MetaTokens
  #define PTYPE Sts_MetaToken
  #include "pmap.h"
  #undef PNAME
  #undef PTYPE
// 
// moved to resolve declaration order constraints
  #define PNAME Sts_MetaZones
  #define PTYPE Sts_MetaZone
  #include "plist.h"
  #undef PNAME
  #undef PTYPE
//
// moved to resolve declaration order constraints
  #define PNAME Sts_MetaZonesMap
  #define PTYPE Sts_MetaZone
  #include "pmap.h"
  #undef PNAME
  #undef PTYPE
//
struct Sts_MetaZone {
  String name;

  Sts_MetaTokens tokens;
  Sts_MetaZones expandZones;

  Sts_MetaStaticParams staticParams;
  Sts_MetaVariables variables;
  Sts_MetaEvents events;
};
void_errno Sts_MetaZone_init(Sts_MetaZone* zone, String name);
void Sts_MetaZone_free(Sts_MetaZone* zone);

// moved to resolve declaration order constraints
// #define PNAME Sts_MetaZones
// #define PTYPE Sts_MetaZone
// #include "plist.h"
// #undef PNAME
// #undef PTYPE

// moved to resolve declaration order constraints
// #define PNAME Sts_MetaZonesMap
// #define PTYPE Sts_MetaZone
// #include "pmap.h"
// #undef PNAME
// #undef PTYPE
void Sts_MetaZonesMap_freeElements(Sts_MetaZonesMap* zonesMap);


struct Sts_MetaToken {
  String name;
  String regex;
  Sts_MetaZones parentZones;
  bool ghost;

  Sts_MetaZone* openZone;
  Sts_MetaZone* setZone;
  bool isCloseZone;
  
  Sts_MetaStaticParams staticParams;
  Sts_MetaVariables variables;
  Sts_MetaEvents events;
};
void_errno Sts_MetaToken_init(Sts_MetaToken* token, String name);
void Sts_MetaToken_free(Sts_MetaToken* token);

// moved to resolve declaration order constraints
// #define PNAME Sts_MetaTokens
// #define PTYPE Sts_MetaToken
// #include "pmap.h"
// #undef PNAME
// #undef PTYPE
void Sts_MetaTokens_freeElements(Sts_MetaTokens* tokens);


struct Sts_MetaSuperTokenBodyBlock {
  Sts_MetaToken* token;
  String name;
  bool strict;
};
void Sts_MetaSuperTokenBodyBlock_init(Sts_MetaSuperTokenBodyBlock* block, Sts_MetaToken* token);
void Sts_MetaSuperTokenBodyBlock_free(Sts_MetaSuperTokenBodyBlock* block);

#define NAME Sts_MetaSuperTokenBodyBlocks
#define TYPE Sts_MetaSuperTokenBodyBlock
#define NULLV (Sts_MetaSuperTokenBodyBlock) {0}
#include "glist.h"
#undef NAME
#undef TYPE
#undef NULLV
void Sts_MetaSuperTokenBodyBlocks_freeElements(Sts_MetaSuperTokenBodyBlocks* blocks);

struct Sts_MetaSuperTokenBody {
  Sts_MetaSuperTokenBodyBlocks blocks;
  bool ghost;
};
void Sts_MetaSuperTokenBody_init(Sts_MetaSuperTokenBody* body, Sts_MetaSuperTokenBodyBlocks blocks);
void Sts_MetaSuperTokenBody_free(Sts_MetaSuperTokenBody* body);


// moved to resolve declaration order constraints
  #define PNAME Sts_MetaSuperTokens
  #define PTYPE Sts_MetaSuperToken
  #include "pmap.h"
  #undef PNAME
  #undef PTYPE
//
struct Sts_MetaSuperToken {
  String name;
  bool ghost;

  String openTrigger;
  String closeTrigger;
  Sts_MetaSuperTokenBody* body;

  Sts_MetaStaticParams staticParams;
  Sts_MetaVariables variables;
  Sts_MetaEvents events;
};
void_errno Sts_MetaSuperToken_init(Sts_MetaSuperToken* superToken, String name);
void Sts_MetaSuperToken_free(Sts_MetaSuperToken* superToken);

// moved to resolve declaration order constraints
// #define PNAME Sts_MetaSuperTokens
// #define PTYPE Sts_MetaSuperToken
// #include "pmap.h"
// #undef PNAME
// #undef PTYPE
void Sts_MetaSuperTokens_freeElements(Sts_MetaSuperTokens* tokens);


struct Sts_MetaFile {
  Sts_MetaRegexes regexes;
  Sts_MetaZonesMap zones;
  Sts_MetaTokens tokens;
  Sts_MetaSuperTokens superTokens;

  Sts_MetaZone* mainZone;

  struct {
    String name;
    Sources sources;
  } properties;
};
void Sts_MetaFile_init(Sts_MetaFile* metaFile);
void Sts_MetaFile_free(Sts_MetaFile* metaFile);

// Sts_MetaZone Sts_MetaFile_getZone(Sts_MetaFile* metaFile, String name);
// Sts_MetaToken Sts_MetaFile_getToken(Sts_MetaFile* metaFile, String name);
// Sts_MetaSuperToken Sts_MetaFile_getSuperToken(Sts_MetaFile* metaFile, String name);


void_errno Sts_MetaFile_regZone(Sts_MetaFile* metaFile, Sts_MetaZone* zone);
void_errno Sts_MetaFile_regToken(Sts_MetaFile* metaFile, Sts_MetaToken* token);
void_errno Sts_MetaFile_regSuperToken(Sts_MetaFile* metaFile, Sts_MetaSuperToken* superToken);

Sts_MetaZone* Sts_MetaFile_getOrCreateZone(Sts_MetaFile* metaFile, const String name);
