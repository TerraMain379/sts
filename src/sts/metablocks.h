#pragma once

#include "utils.h"
#include "prints.h"
#include "sources.h"
#include "stss.h"
#include "map.h"
#include "constmap.h"
#include "constlist.h"
#include "stringlist.h"

#define typedef_struct(name) typedef struct name name
#define typedef_enum(name) typedef enum name name
  typedef_struct(Sts_MetaRegex);
  typedef_struct(Sts_MetaRegexLinks);
  typedef_struct(Sts_MetaEvent);
  typedef_struct(Sts_MetaEvents);
  typedef_struct(Sts_MetaElementVariable);
  typedef_struct(Sts_MetaElementVariables);
  typedef_enum(Sts_MetaStaticParamType);
  typedef_struct(Sts_MetaElementStaticParam);
  typedef_struct(Sts_MetaElementStaticParams);
  typedef_struct(Sts_MetaElement);

  // typedef_struct(Sts_OwnedMetaTokens);
  // typedef_struct(Sts_MetaTokens);
  // typedef_struct(Sts_OwnedMetaZonesMap);
  // typedef_struct(Sts_MetaZones);

  typedef_enum(Sts_MetaDeclarationValueType);
  typedef_struct(Sts_MetaDeclarationValue);
  typedef_enum(Sts_MetaDeclarationExpressionType);
  typedef_struct(Sts_MetaDeclarationExpression);
  typedef_struct(Sts_MetaParamDeclaration);
  typedef_struct(Sts_MetaVariableDeclaration);
  typedef_struct(Sts_MetaEventDeclaration);
  typedef_struct(Sts_MetaZoneExtendDeclaration);
  typedef_struct(Sts_MetaSuperRegexDeclarationElement);
  typedef_struct(Sts_MetaSuperRegexDeclaration);
  typedef_enum(Sts_MetaDeclarationType);
  typedef_struct(Sts_MetaDeclaration);
  typedef_enum(Sts_MetaDeclarationsBlockType);
  typedef_struct(Sts_MetaDeclarationsBlock);

  typedef_struct(Sts_MetaZone);
  typedef_struct(Sts_MetaToken);
  typedef_struct(Sts_MetaFile);
#undef typedef_struct
#undef typedef_enum


struct Sts_MetaRegex {
  String regex;
};
void Sts_MetaRegex_init(Sts_MetaRegex* metaRegex, OWNER(String) regex);
void Sts_MetaRegex_free(Sts_MetaRegex* metaRegex);
dec_prints(Sts_MetaRegex);

#define NAME Sts_MetaRegexLinks
#define TYPE OWNER(Sts_MetaRegex)
#define NULLV (Sts_MetaRegex) {0}
#define FREEFUN Sts_MetaRegex_free
#include "gmap.h"
#undef NAME
#undef TYPE
#undef NULLV
#undef FREEFUN
dec_prints(Sts_MetaRegexLinks);


struct Sts_MetaEvent {
  String code;
};
void Sts_MetaEvent_init(Sts_MetaEvent* event, OWNER(String) code);
void Sts_MetaEvent_free(Sts_MetaEvent* event);
dec_prints(Sts_MetaEvent);

#define NAME Sts_MetaEvents
#define TYPE OWNER(Sts_MetaEvent)
#define NULLV (Sts_MetaEvent) {0}
#define FREEFUN Sts_MetaEvent_free
#include "gmap.h"
#undef NAME
#undef TYPE
#undef NULLV
#undef FREEFUN
dec_prints(Sts_MetaEvents);


struct Sts_MetaElementVariable {
  OWNER(Stss_Type) type;
  OWNER(Stss_UntypeValue*) value;
};
void Sts_MetaElementVariable_init(Sts_MetaElementVariable* variable);
void Sts_MetaElementVariable_free(Sts_MetaElementVariable* variable);
dec_prints(Sts_MetaElementVariable);

#define NAME Sts_MetaElementVariables
#define TYPE OWNER(Sts_MetaElementVariable)
#define NULLV (Sts_MetaElementVariable) {0};
#define FREEFUN Sts_MetaElementVariable_free
#include "gmap.h"
#undef NAME
#undef TYPE
#undef NULLV
#undef FREEFUN
dec_prints(Sts_MetaElementVariables);

struct Sts_MetaElementStaticParam {
  OWNER(Stss_Type) type;
  OWNER(Stss_UntypeValue*) value;
};
void Sts_MetaElementStaticParam_init(Sts_MetaElementStaticParam* staticParam);
void Sts_MetaElementStaticParam_free(Sts_MetaElementStaticParam* staticParam);
dec_prints(Sts_MetaElementStaticParam);

#define NAME Sts_MetaElementStaticParams
#define TYPE OWNER(Sts_MetaElementStaticParam)
#define NULLV (Sts_MetaElementStaticParam) {0};
#define FREEFUN Sts_MetaElementStaticParams_free
#include "gmap.h"
#undef NAME
#undef TYPE
#undef NULLV
#undef FREEFUN
dec_prints(Sts_MetaElementStaticParams);


#define extends__Sts_MetaElement \
  String name; \
  Sts_MetaElementStaticParams params; \
  Sts_MetaElementVariables variables; \
  Sts_MetaEvents events;
struct Sts_MetaElement {
  extends__Sts_MetaElement;
};
void Sts_MetaElement_init(Sts_MetaElement* element, OWNER(String) name);
void Sts_MetaElement_free(Sts_MetaElement* element);
dec_prints(Sts_MetaElement);


struct Sts_MetaToken {
  extends__Sts_MetaElement;
};
void Sts_MetaToken_init(Sts_MetaToken* token, OWNER(String) name);
void Sts_MetaToken_free(Sts_MetaToken* token);
dec_prints(Sts_MetaToken);

#define PNAME Sts_OwnedMetaTokens
// TODO: check ptr
#define PTYPE OWNER(Sts_MetaToken)
#define PFREEFUN Sts_MetaToken_free
#define BASE_MAP Map
#include "pmap.h"
#undef PNAME
#undef PTYPE
#undef PFREEFUN
#undef BASE_MAP
dec_prints(Sts_OwnedMetaTokens);

#define PNAME Sts_MetaTokens
#define PTYPE WEAK(Sts_MetaToken)
#undef PFREEFUN
#define BASE_MAP ConstMap
#include "pmap.h"
#undef PNAME
#undef PTYPE
#undef BASE_MAP
dec_prints(Sts_MetaTokens);


void Sts_MetaZone_init(Sts_MetaZone* zone, OWNER(String) name);
void Sts_MetaZone_free(Sts_MetaZone* zone);
dec_prints(Sts_MetaZone);

#define PNAME Sts_OwnedMetaZonesMap
// TODO: check ptr
#define PTYPE OWNER(Sts_MetaZone)
#define PFREEFUN Sts_MetaZone_free
#define BASE_MAP Map
#include "pmap.h"
#undef PNAME
#undef PTYPE
#undef PFREEFUN
#undef BASE_MAP
dec_prints(Sts_OwnedMetaZonesMap);

#define PNAME Sts_MetaZones
// TODO: check ptr
#define PTYPE WEAK(Sts_MetaZone)
#undef PFREEFUN
#define BASE_LIST ConstList
#include "plist.h"
#undef PNAME
#undef PTYPE
#undef BASE_LIST
dec_prints(Sts_MetaZones);

struct Sts_MetaZone {
  extends__Sts_MetaElement;

  Sts_MetaTokens tokens;
  Sts_MetaZones expandZones;
};


enum Sts_MetaDeclarationValueType {
  Sts_MetaDeclarationValueType_NULL = 0,
  Sts_MetaDeclarationValueType_NAME,
  Sts_MetaDeclarationValueType_STRING,
  Sts_MetaDeclarationValueType_NUMBER,
  Sts_MetaDeclarationValueType_EXPRESSION,
  Sts_MetaDeclarationValueType_LINK
};
dec_prints(Sts_MetaDeclarationValueType);
struct Sts_MetaDeclarationValue {
  Sts_MetaDeclarationValueType type;
  union {
    String name;
    String string;
    double number;
    OWNER(Sts_MetaDeclarationExpression*) expression;
    String linkName;
  } value;
};
void Sts_MetaDeclarationValue_free(Sts_MetaDeclarationValue* decValue);
dec_prints(Sts_MetaDeclarationValue);

#define NAME Sts_MetaDeclarationValueList
#define TYPE Sts_MetaDeclarationValue
#define NULLV (Sts_MetaDeclarationValue) {0}
#define FREEFUN Sts_MetaDeclarationValue_free
#include "glist.h"
#undef NAME
#undef TYPE
#undef NULLV
#undef FREEFUN
dec_prints(Sts_MetaDeclarationValueList);

enum Sts_MetaDeclarationExpressionType {
  Sts_MetaDeclarationExpressionType_ASSIGN,

  Sts_MetaDeclarationExpressionType_SUM,
  Sts_MetaDeclarationExpressionType_SUB,
  Sts_MetaDeclarationExpressionType_MUL,
  Sts_MetaDeclarationExpressionType_DIV,
  Sts_MetaDeclarationExpressionType_MOD,
  Sts_MetaDeclarationExpressionType_POW,

  Sts_MetaDeclarationExpressionType_NOT,
  Sts_MetaDeclarationExpressionType_INC,
  Sts_MetaDeclarationExpressionType_DEC,

  Sts_MetaDeclarationExpressionType_LOGICAL_OR,
  Sts_MetaDeclarationExpressionType_LOGICAL_AND,
  Sts_MetaDeclarationExpressionType_BITWISE_OR,
  Sts_MetaDeclarationExpressionType_BITWISE_XOR,
  Sts_MetaDeclarationExpressionType_BITWISE_AND,

  Sts_MetaDeclarationExpressionType_LOGICAL_EQL,
  Sts_MetaDeclarationExpressionType_LOGICAL_NOT_EQL,
  Sts_MetaDeclarationExpressionType_LOGICAL_GT,
  Sts_MetaDeclarationExpressionType_LOGICAL_LT,
  Sts_MetaDeclarationExpressionType_LOGICAL_GTE,
  Sts_MetaDeclarationExpressionType_LOGICAL_LTE,

  Sts_MetaDeclarationExpressionType_TERN_COND_IF,
  Sts_MetaDeclarationExpressionType_TERN_COND_ELSE,

  Sts_MetaDeclarationExpressionType_CHILD,
};
dec_prints(Sts_MetaDeclarationExpressionType);
struct Sts_MetaDeclarationExpression {
  Sts_MetaDeclarationExpressionType type;
  Sts_MetaDeclarationValue value1;
  Sts_MetaDeclarationValue value2;
};
void Sts_MetaDeclarationExpression_free(Sts_MetaDeclarationExpression* decExpression);
dec_prints(Sts_MetaDeclarationExpression);


struct Sts_MetaParamDeclaration {
  Sts_MetaDeclarationValue name;
  Sts_MetaDeclarationValueList values;
};
void Sts_MetaParamDeclaration_free(Sts_MetaParamDeclaration* paramDec);
dec_prints(Sts_MetaParamDeclaration);

struct Sts_MetaVariableDeclaration {
  Sts_MetaDeclarationValue name;
  Sts_MetaDeclarationValue value;
  Sts_MetaDeclarationValue typing;
  bool isInit;
};
void Sts_MetaVariableDeclaration_free(Sts_MetaVariableDeclaration* variableDec);
dec_prints(Sts_MetaVariableDeclaration);

struct Sts_MetaEventDeclaration {
  Sts_MetaDeclarationValue name;
  Sts_MetaDeclarationValue event;
};
void Sts_MetaEventDeclaration_free(Sts_MetaEventDeclaration* eventDec);
dec_prints(Sts_MetaEventDeclaration);

struct Sts_MetaZoneExtendDeclaration {
  Sts_MetaDeclarationValue zoneName;
  bool isExport;
};
void Sts_MetaZoneExtendDeclaration_free(Sts_MetaZoneExtendDeclaration* zoneExtendDec);
dec_prints(Sts_MetaZoneExtendDeclaration);

struct Sts_MetaSuperRegexDeclarationElement {
  Sts_MetaDeclarationValue token;
  Sts_MetaDeclarationValue name;
  bool isOptional;
  bool isNonName;
};
void Sts_MetaSuperRegexDeclarationElement_free(Sts_MetaSuperRegexDeclarationElement* regexDecElement);
dec_prints(Sts_MetaSuperRegexDeclarationElement);

#define NAME Sts_MetaSuperRegexDeclarationElements
#define TYPE Sts_MetaSuperRegexDeclarationElement
#define NULLV (Sts_MetaSuperRegexDeclarationElement) {0}
#define FREEFUN Sts_MetaSuperRegexDeclarationElement_free
#include "glist.h"
#undef NAME
#undef TYPE
#undef NULLV
#undef FREEFUN
dec_prints(Sts_MetaSuperRegexDeclarationElements);

struct Sts_MetaSuperRegexDeclaration {
  Sts_MetaSuperRegexDeclarationElements elements;
  bool isGhost;
};
void Sts_MetaSuperRegexDeclaration_free(Sts_MetaSuperRegexDeclaration* regexDec);
dec_prints(Sts_MetaSuperRegexDeclaration);

enum Sts_MetaDeclarationType {
  Sts_MetaDeclarationType_PARAM,
  Sts_MetaDeclarationType_VARIABLE,
  Sts_MetaDeclarationType_EVENT,
  Sts_MetaDeclarationType_ZONE_EXTEND,
  Sts_MetaDeclarationType_SUPER_REGEX
};
dec_prints(Sts_MetaDeclarationType);
struct Sts_MetaDeclaration {
  Sts_MetaDeclarationType type;
  union {
    Sts_MetaParamDeclaration param;
    Sts_MetaVariableDeclaration variable;
    Sts_MetaEventDeclaration event;
    Sts_MetaZoneExtendDeclaration zoneExtend;
    Sts_MetaSuperRegexDeclaration superRegex;
  } value;
};
void Sts_MetaDeclaration_free(Sts_MetaDeclaration* declaration);
dec_prints(Sts_MetaDeclaration);

#define PNAME Sts_MetaDeclarationList
#define PTYPE OWNER(Sts_MetaDeclaration)
#define PFREEFUN Sts_MetaDeclaration_free
#define BASE_LIST List
#include "plist.h"
#undef PNAME
#undef PTYPE
#undef PFREEFUN
#undef BASE_LIST
dec_prints(Sts_MetaDeclarationList);

#define PNAME Sts_MetaDeclarationValuesWeakList
#define PTYPE WEAK(Sts_MetaDeclarationValue)
#undef PFREEFUN
#define BASE_LIST ConstList
#include "plist.h"
#undef PNAME
#undef PTYPE
#undef BASE_LIST
dec_prints(Sts_MetaDeclarationValuesWeakList);

#define NAME Sts_MetaDeclarationValuesLinks
#define TYPE Sts_MetaDeclarationValuesWeakList
#define NULLV (Sts_MetaDeclarationValuesWeakList) {0}
#define FREEFUN Sts_MetaDeclarationValuesWeakList_free
#include "gmap.h"
#undef NAME
#undef TYPE
#undef NULLV
#undef FREEFUN
dec_prints(Sts_MetaDeclarationValuesLinks);
Sts_MetaDeclarationValuesWeakList* Sts_MetaDeclarationValuesLinks_getOrCreate(Sts_MetaDeclarationValuesLinks* valuesLinks, BORROW(ViewString) key);
void Sts_MetaDeclarationValuesLinks_registerDeclaratonValue(Sts_MetaDeclarationValuesLinks* valuesLinks, WEAK(Sts_MetaDeclarationValue*) decValue);

enum Sts_MetaDeclarationsBlockType {
  Sts_MetaDeclarationsBlockType_TOKEN,
  Sts_MetaDeclarationsBlockType_ZONE,
  Sts_MetaDeclarationsBlockType_GROUP,
  Sts_MetaDeclarationsBlockType_SUPER_TOKEN
};
dec_prints(Sts_MetaDeclarationsBlockType);
struct Sts_MetaDeclarationsBlock {
  String name;
  Sts_MetaDeclarationsBlockType type;
  Sts_MetaDeclarationList declarations;
  StringList linkNames;
  Sts_MetaDeclarationValuesLinks links;
};
void Sts_MetaDeclarationsBlock_init(Sts_MetaDeclarationsBlock* decBlock, Sts_MetaDeclarationsBlockType type);
void Sts_MetaDeclarationsBlock_free(Sts_MetaDeclarationsBlock* decBlock);
dec_prints(Sts_MetaDeclarationsBlock);

#define NAME Sts_MetaDeclarationsBlocks
#define TYPE Sts_MetaDeclarationsBlock
#define NULLV (Sts_MetaDeclarationsBlock) {0}
#define FREEFUN Sts_MetaDeclarationsBlock_free
#include "glist.h"
#undef NAME
#undef TYPE
#undef NULLV
#undef FREEFUN
dec_prints(Sts_MetaDeclarationsBlocks);


struct Sts_MetaFile {
  Sts_MetaDeclarationsBlocks decBlocks;
  Sts_MetaRegexLinks regexes;
  Sts_OwnedMetaZonesMap zones;
  Sts_OwnedMetaTokens tokens;

  MUT_WEAK(Sts_MetaZone*) mainZone;

  struct {
    String name;
    Sources sources;
  } properties;
};
void Sts_MetaFile_init(Sts_MetaFile* metaFile);
void Sts_MetaFile_free(Sts_MetaFile* metaFile);
dec_prints(Sts_MetaFile);


void_errno Sts_MetaFile_regZone(Sts_MetaFile* metaFile, OWNER(Sts_MetaZone*) zone);
Sts_MetaZone* Sts_MetaFile_getZone(Sts_MetaFile* metaFile, BORROW(ViewString) name);
Sts_MetaZone* Sts_MetaFile_getOrCreateZone(Sts_MetaFile* metaFile, BORROW(ViewString) name);
void_errno Sts_MetaFile_delZone(Sts_MetaFile* metaFile, BORROW(ViewString) name);

void_errno Sts_MetaFile_regToken(Sts_MetaFile* metaFile, OWNER(Sts_MetaToken*) token);
Sts_MetaToken* Sts_MetaFile_getToken(Sts_MetaFile* metaFile, BORROW(ViewString) name);
void_errno Sts_MetaFile_delToken(Sts_MetaFile* metaFile, BORROW(ViewString) name);
