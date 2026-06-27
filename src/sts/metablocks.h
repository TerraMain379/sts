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
#define typedef_gmap(name) typedef struct name name; typedef struct name##_element name##_element;
#define typedef_glist(name) typedef struct name name;
#define typedef_pmap(name) ;
#define typedef_plist(name) ;
  typedef_struct(Sts_MetaRegex);
  typedef_gmap(Sts_MetaRegexLinks);
  typedef_struct(Sts_MetaEvent);
  typedef_gmap(Sts_MetaEvents);
  typedef_struct(Sts_MetaElementVariable);
  typedef_gmap(Sts_MetaElementVariables);
  typedef_enum(Sts_MetaStaticParamType);
  typedef_struct(Sts_MetaElementStaticParam);
  typedef_gmap(Sts_MetaElementStaticParams);
  typedef_struct(Sts_MetaElement);
  typedef_struct(Sts_MetaToken);
  typedef_pmap(Sts_OwnedMetaTokens);
  typedef_pmap(Sts_MetaTokens);
  typedef_struct(Sts_MetaZone);
  typedef_pmap(Sts_OwnedMetaZonesMap);
  typedef_plist(Sts_MetaZones);

  typedef_enum(Sts_MetaDeclarationValueType);
  typedef_struct(Sts_MetaDeclarationValue);
  typedef_glist(Sts_MetaDeclarationValueList);
  typedef_plist(Sts_MetaDeclarationValueWeakList);
  typedef_enum(Sts_MetaDeclarationExpressionType);
  typedef_struct(Sts_MetaDeclarationExpression);
  typedef_struct(Sts_MetaLineParamDeclaration);
  typedef_struct(Sts_MetaLineVariableDeclaration);
  typedef_struct(Sts_MetaLineEventDeclaration);
  typedef_struct(Sts_MetaLineExpandDeclaration);
  typedef_struct(Sts_MetaLineSuperRegexDeclarationElement);
  typedef_glist(Sts_MetaLineSuperRegexDeclarationElements);
  typedef_struct(Sts_MetaLineSuperRegexDeclaration);
  typedef_enum(Sts_MetaLineDeclarationType);
  typedef_struct(Sts_MetaLineDeclaration);
  typedef_plist(Sts_MetaLineDeclarationList);
  typedef_struct(Sts_MetaDeclarationExtendElement);
  typedef_glist(Sts_MetaDeclarationExtendElementList);
  typedef_struct(Sts_MetaDeclarationHead);
  typedef_enum(Sts_MetaElementDeclarationType);
  typedef_struct(Sts_MetaElementDeclaration);
  typedef_struct(Sts_MetaNamespaceDeclaration);
  typedef_enum(Sts_MetaDeclarationType);
  typedef_struct(Sts_MetaDeclaration);
  typedef_glist(Sts_MetaDeclarations);

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
#undef TYPEDEFS
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
#undef TYPEDEFS
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
#undef TYPEDEFS
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
#undef TYPEDEFS
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
Sts_MetaDeclarationValue Sts_MetaDeclarationValue_byName(String name);
Sts_MetaDeclarationValue Sts_MetaDeclarationValue_byString(String string);
Sts_MetaDeclarationValue Sts_MetaDeclarationValue_byNumber(double number);
Sts_MetaDeclarationValue Sts_MetaDeclarationValue_byExpression(OWNER(Sts_MetaDeclarationExpression*) expression);
Sts_MetaDeclarationValue Sts_MetaDeclarationValue_byLinkName(String linkName);
void Sts_MetaDeclarationValue_initByName(Sts_MetaDeclarationValue* decValue, String name);
void Sts_MetaDeclarationValue_initByString(Sts_MetaDeclarationValue* decValue, String string);
void Sts_MetaDeclarationValue_initByNumber(Sts_MetaDeclarationValue* decValue, double number);
void Sts_MetaDeclarationValue_initByExpression(Sts_MetaDeclarationValue* decValue, OWNER(Sts_MetaDeclarationExpression*) expression);
void Sts_MetaDeclarationValue_initByLinkName(Sts_MetaDeclarationValue* decValue, String linkName);
void Sts_MetaDeclarationValue_free(Sts_MetaDeclarationValue* decValue);
dec_prints(Sts_MetaDeclarationValue);

#define NAME Sts_MetaDeclarationValueList
#define TYPE OWNER(Sts_MetaDeclarationValue)
#define NULLV (Sts_MetaDeclarationValue) {0}
#define FREEFUN Sts_MetaDeclarationValue_free
#undef TYPEDEFS
#include "glist.h"
#undef NAME
#undef TYPE
#undef NULLV
#undef FREEFUN
dec_prints(Sts_MetaDeclarationValueList);

#define PNAME Sts_MetaDeclarationValueWeakList
#define PTYPE WEAK(Sts_MetaDeclarationValue)
#undef PFREEFUN
#define BASE_LIST ConstList
#include "plist.h"
#undef PNAME
#undef PTYPE
#undef BASE_LIST
dec_prints(Sts_MetaDeclarationValueWeakList);

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


struct Sts_MetaLineParamDeclaration {
  Sts_MetaDeclarationValue name;
  Sts_MetaDeclarationValueList values;
  bool isGhost;
};
void Sts_MetaLineParamDeclaration_free(Sts_MetaLineParamDeclaration* paramDec);
dec_prints(Sts_MetaLineParamDeclaration);

struct Sts_MetaLineVariableDeclaration {
  Sts_MetaDeclarationValue name;
  Sts_MetaDeclarationValue value;
  Sts_MetaDeclarationValue typing;
  bool isInit;
};
void Sts_MetaLineVariableDeclaration_free(Sts_MetaLineVariableDeclaration* variableDec);
dec_prints(Sts_MetaLineVariableDeclaration);

struct Sts_MetaLineEventDeclaration {
  Sts_MetaDeclarationValue name;
  Sts_MetaDeclarationValue event;
};
void Sts_MetaLineEventDeclaration_free(Sts_MetaLineEventDeclaration* eventDec);
dec_prints(Sts_MetaLineEventDeclaration);

struct Sts_MetaLineExpandDeclaration {
  Sts_MetaDeclarationValue zoneName;
  bool isExport;
};
void Sts_MetaLineExpandDeclaration_free(Sts_MetaLineExpandDeclaration* expandDec);
dec_prints(Sts_MetaLineExpandDeclaration);

struct Sts_MetaLineSuperRegexDeclarationElement {
  Sts_MetaDeclarationValue token;
  Sts_MetaDeclarationValue name;
  bool isOptional;
  bool isNonName;
};
void Sts_MetaLineSuperRegexDeclarationElement_free(Sts_MetaLineSuperRegexDeclarationElement* regexDecElement);
dec_prints(Sts_MetaLineSuperRegexDeclarationElement);

#define NAME Sts_MetaLineSuperRegexDeclarationElements
#define TYPE Sts_MetaLineSuperRegexDeclarationElement
#define NULLV (Sts_MetaLineSuperRegexDeclarationElement) {0}
#define FREEFUN Sts_MetaLineSuperRegexDeclarationElement_free
#undef TYPEDEFS
#include "glist.h"
#undef NAME
#undef TYPE
#undef NULLV
#undef FREEFUN
dec_prints(Sts_MetaLineSuperRegexDeclarationElements);

struct Sts_MetaLineSuperRegexDeclaration {
  Sts_MetaLineSuperRegexDeclarationElements elements;
  bool isGhost;
};
void Sts_MetaLineSuperRegexDeclaration_free(Sts_MetaLineSuperRegexDeclaration* regexDec);
dec_prints(Sts_MetaLineSuperRegexDeclaration);

enum Sts_MetaLineDeclarationType {
  Sts_MetaLineDeclarationType_PARAM,
  Sts_MetaLineDeclarationType_VARIABLE,
  Sts_MetaLineDeclarationType_EVENT,
  Sts_MetaLineDeclarationType_EXPAND,
  Sts_MetaLineDeclarationType_SUPER_REGEX
};
dec_prints(Sts_MetaLineDeclarationType);
struct Sts_MetaLineDeclaration {
  Sts_MetaLineDeclarationType type;
  union {
    Sts_MetaLineParamDeclaration param;
    Sts_MetaLineVariableDeclaration variable;
    Sts_MetaLineEventDeclaration event;
    Sts_MetaLineExpandDeclaration expand;
    Sts_MetaLineSuperRegexDeclaration superRegex;
  } value;
};
Sts_MetaLineDeclaration Sts_MetaLineDeclaration_byParam(Sts_MetaLineParamDeclaration param);
Sts_MetaLineDeclaration Sts_MetaLineDeclaration_byVariable(Sts_MetaLineVariableDeclaration variable);
Sts_MetaLineDeclaration Sts_MetaLineDeclaration_byEvent(Sts_MetaLineEventDeclaration event);
Sts_MetaLineDeclaration Sts_MetaLineDeclaration_byExpand(Sts_MetaLineExpandDeclaration expand);
Sts_MetaLineDeclaration Sts_MetaLineDeclaration_bySuperRegex(Sts_MetaLineSuperRegexDeclaration superRegex);
void Sts_MetaLineDeclaration_free(Sts_MetaLineDeclaration* lineDec);
dec_prints(Sts_MetaLineDeclaration);

#define PNAME Sts_MetaLineDeclarationList
#define PTYPE OWNER(Sts_MetaLineDeclaration)
#define PFREEFUN Sts_MetaLineDeclaration_free
#define BASE_LIST List
#include "plist.h"
#undef PNAME
#undef PTYPE
#undef PFREEFUN
#undef BASE_LIST
dec_prints(Sts_MetaLineDeclarationList);



struct Sts_MetaDeclarationExtendElement {
  Sts_MetaDeclarationValue name;
  Sts_MetaDeclarationValueList linksValues;
};
void Sts_MetaDeclarationExtendElement_free(Sts_MetaDeclarationExtendElement* extendElement);
dec_prints(Sts_MetaDeclarationExtendElement);

#define NAME Sts_MetaDeclarationExtendElementList
#define TYPE OWNER(Sts_MetaDeclarationExtendElement)
#define NULLV (Sts_MetaDeclarationExtendElement) {0}
#define FREEFUN Sts_MetaDeclarationExtendElement_free
#undef TYPEDEFS
#include "glist.h"
#undef NAME
#undef TYPE
#undef NULLV
#undef FREEFUN
dec_prints(Sts_MetaDeclarationExtendElementList);


struct Sts_MetaDeclarationHead {
  Sts_MetaDeclarationValue name;
  StringList linkNames;
  Sts_MetaDeclarationExtendElementList extenders;
  bool isGeneric;
  bool isGhost;
};
void Sts_MetaDeclarationHead_init(Sts_MetaDeclarationHead* head, OWNER(Sts_MetaDeclarationValue) name);
void Sts_MetaDeclarationHead_free(Sts_MetaDeclarationHead* head);
dec_prints(Sts_MetaDeclarationHead);


enum Sts_MetaElementDeclarationType {
  Sts_MetaElementDeclarationType_TOKEN,
  Sts_MetaElementDeclarationType_ZONE,
  Sts_MetaElementDeclarationType_GROUP,
  Sts_MetaElementDeclarationType_SUPER_TOKEN
};
dec_prints(Sts_MetaElementDeclarationType);


struct Sts_MetaElementDeclaration {
  Sts_MetaDeclarationHead head;
  Sts_MetaElementDeclarationType type;
  Sts_MetaLineDeclarationList lineDeclarations;
};
void Sts_MetaElementDeclaration_init(Sts_MetaElementDeclaration* elementDec, OWNER(Sts_MetaDeclarationValue) name, Sts_MetaElementDeclarationType type);
void Sts_MetaElementDeclaration_free(Sts_MetaElementDeclaration* elementDec);
dec_prints(Sts_MetaElementDeclaration);

// moved because C limits the possibilities of logical ordering of structures
#define NAME Sts_MetaDeclarations
#define TYPE OWNER(Sts_MetaDeclaration)
#define NULLV (Sts_MetaDeclaration) {0}
#define FREEFUN Sts_MetaDeclaration_free
#undef TYPEDEFS
#include "glist.h"
#undef NAME
#undef TYPE
#undef NULLV
#undef FREEFUN
dec_prints(Sts_MetaDeclarations);
//

struct Sts_MetaNamespaceDeclaration {
  Sts_MetaDeclarationHead head;
  Sts_MetaDeclarations declarations;
};
void Sts_MetaNamespaceDeclaration_init(Sts_MetaNamespaceDeclaration* namespaceDec, OWNER(Sts_MetaDeclarationValue) name);
void Sts_MetaNamespaceDeclaration_free(Sts_MetaNamespaceDeclaration* namespaceDec);
dec_prints(Sts_MetaNamespaceDeclaration);

enum Sts_MetaDeclarationType {
  Sts_MetaDeclarationType_ELEMENT,
  Sts_MetaDeclarationType_NAMESPACE,
};
dec_prints(Sts_MetaDeclarationType);

struct Sts_MetaDeclaration {
  Sts_MetaDeclarationType type;
  union {
    Sts_MetaElementDeclaration element;
    Sts_MetaNamespaceDeclaration namespace;
  } value;
};
Sts_MetaDeclaration Sts_MetaDeclaration_byElement(Sts_MetaElementDeclaration element);
Sts_MetaDeclaration Sts_MetaDeclaration_byNamespace(Sts_MetaNamespaceDeclaration namespace);
void Sts_MetaDeclaration_initByElement(Sts_MetaDeclaration* declaration, Sts_MetaElementDeclaration element);
void Sts_MetaDeclaration_initByNamespace(Sts_MetaDeclaration* declaration, Sts_MetaNamespaceDeclaration namespace);
void Sts_MetaDeclaration_free(Sts_MetaDeclaration* declaration);
dec_prints(Sts_MetaDeclaration);

// moved because C limits the possibilities of logical ordering of structures
// #define NAME Sts_MetaDeclarations
// #define TYPE Sts_MetaDeclaration
// #define NULLV (Sts_MetaDeclaration) {0}
// #define FREEFUN Sts_MetaDeclaration_free
// #undef TYPEDEFS
// #include "glist.h"
// #undef NAME
// #undef TYPE
// #undef NULLV
// #undef FREEFUN
// dec_prints(Sts_MetaDeclarations);


struct Sts_MetaFile {
  Sts_MetaDeclarations declarations;
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
