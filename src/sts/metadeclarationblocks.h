#pragma once

#include "utils.h"
#include "prints.h"
#include "sources.h"
#include "stss.h"
#include "map.h"
#include "constmap.h"
#include "constlist.h"
#include "stringlist.h"
#include "stringmap.h"

#define typedef_struct(name) typedef struct name name; dec_prints(name);
#define typedef_enum(name) typedef enum name name; dec_prints(name);
#define typedef_gmap(name) typedef struct name name; typedef struct name##_element name##_element; dec_prints(name);
#define typedef_glist(name) typedef struct name name; dec_prints(name);
#define typedef_pmap(name) ;
#define typedef_plist(name) ;
  typedef_struct(Sts_MetaDeclarationValueName);
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
  typedef_struct(Sts_MetaDeclarationFile);
#undef typedef_struct
#undef typedef_enum
#undef typedef_gmap
#undef typedef_glist
#undef typedef_pmap
#undef typedef_plist



struct Sts_MetaDeclarationValueName {
  String name;
  MUT_WEAK(Sts_MetaNamespaceDeclaration*) parentNamespace; // we keep a reference to the namespace in order to correctly expand the names after inheritance.
};
void Sts_MetaDeclarationValueName_free(Sts_MetaDeclarationValueName* decValueName);
enum Sts_MetaDeclarationValueType {
  Sts_MetaDeclarationValueType_NULL = 0,
  Sts_MetaDeclarationValueType_NAME,
  Sts_MetaDeclarationValueType_STRING,
  Sts_MetaDeclarationValueType_NUMBER,
  Sts_MetaDeclarationValueType_EXPRESSION,
  Sts_MetaDeclarationValueType_LINK
};
struct Sts_MetaDeclarationValue {
  Sts_MetaDeclarationValueType type;
  union {
    Sts_MetaDeclarationValueName name;
    String string;
    double number;
    OWNER(Sts_MetaDeclarationExpression*) expression;
    String linkName;
  } value;
};
Sts_MetaDeclarationValue Sts_MetaDeclarationValue_byName(Sts_MetaDeclarationValueName decValueName);
Sts_MetaDeclarationValue Sts_MetaDeclarationValue_byString(String string);
Sts_MetaDeclarationValue Sts_MetaDeclarationValue_byNumber(double number);
Sts_MetaDeclarationValue Sts_MetaDeclarationValue_byExpression(OWNER(Sts_MetaDeclarationExpression*) expression);
Sts_MetaDeclarationValue Sts_MetaDeclarationValue_byLinkName(String linkName);
void Sts_MetaDeclarationValue_initByName(Sts_MetaDeclarationValue* decValue, Sts_MetaDeclarationValueName decValueName);
void Sts_MetaDeclarationValue_initByString(Sts_MetaDeclarationValue* decValue, String string);
void Sts_MetaDeclarationValue_initByNumber(Sts_MetaDeclarationValue* decValue, double number);
void Sts_MetaDeclarationValue_initByExpression(Sts_MetaDeclarationValue* decValue, OWNER(Sts_MetaDeclarationExpression*) expression);
void Sts_MetaDeclarationValue_initByLinkName(Sts_MetaDeclarationValue* decValue, String linkName);
void Sts_MetaDeclarationValue_free(Sts_MetaDeclarationValue* decValue);

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
struct Sts_MetaDeclarationExpression {
  Sts_MetaDeclarationExpressionType type;
  Sts_MetaDeclarationValue value1;
  Sts_MetaDeclarationValue value2;
};
void Sts_MetaDeclarationExpression_free(Sts_MetaDeclarationExpression* decExpression);


struct Sts_MetaLineParamDeclaration {
  Sts_MetaDeclarationValue name;
  Sts_MetaDeclarationValueList values;
  bool isGhost;
};
void Sts_MetaLineParamDeclaration_free(Sts_MetaLineParamDeclaration* paramDec);

struct Sts_MetaLineVariableDeclaration {
  Sts_MetaDeclarationValue name;
  Sts_MetaDeclarationValue value;
  Sts_MetaDeclarationValue typing;
  bool isInit;
};
void Sts_MetaLineVariableDeclaration_free(Sts_MetaLineVariableDeclaration* variableDec);

struct Sts_MetaLineEventDeclaration {
  Sts_MetaDeclarationValue name;
  Sts_MetaDeclarationValue event;
};
void Sts_MetaLineEventDeclaration_free(Sts_MetaLineEventDeclaration* eventDec);

struct Sts_MetaLineExpandDeclaration {
  Sts_MetaDeclarationValue zoneName;
  bool isExport;
};
void Sts_MetaLineExpandDeclaration_free(Sts_MetaLineExpandDeclaration* expandDec);

struct Sts_MetaLineSuperRegexDeclarationElement {
  Sts_MetaDeclarationValue token;
  Sts_MetaDeclarationValue name;
  bool isOptional;
  bool isNonName;
};
void Sts_MetaLineSuperRegexDeclarationElement_free(Sts_MetaLineSuperRegexDeclarationElement* regexDecElement);

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

struct Sts_MetaLineSuperRegexDeclaration {
  Sts_MetaLineSuperRegexDeclarationElements elements;
  bool isGhost;
};
void Sts_MetaLineSuperRegexDeclaration_free(Sts_MetaLineSuperRegexDeclaration* regexDec);

enum Sts_MetaLineDeclarationType {
  Sts_MetaLineDeclarationType_PARAM,
  Sts_MetaLineDeclarationType_VARIABLE,
  Sts_MetaLineDeclarationType_EVENT,
  Sts_MetaLineDeclarationType_EXPAND,
  Sts_MetaLineDeclarationType_SUPER_REGEX
};
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


struct Sts_MetaDeclarationHead {
  Sts_MetaDeclarationValue name;
  StringList linkNames;
  Sts_MetaDeclarationExtendElementList extenders;
  bool isGeneric;
  bool isGhost;
};
void Sts_MetaDeclarationHead_init(Sts_MetaDeclarationHead* head, OWNER(Sts_MetaDeclarationValue) name);
void Sts_MetaDeclarationHead_free(Sts_MetaDeclarationHead* head);


enum Sts_MetaElementDeclarationType {
  Sts_MetaElementDeclarationType_TOKEN,
  Sts_MetaElementDeclarationType_ZONE,
  Sts_MetaElementDeclarationType_GROUP,
  Sts_MetaElementDeclarationType_SUPER_TOKEN
};


struct Sts_MetaElementDeclaration {
  Sts_MetaDeclarationHead head;
  Sts_MetaElementDeclarationType type;
  Sts_MetaLineDeclarationList lineDeclarations;
};
void Sts_MetaElementDeclaration_init(Sts_MetaElementDeclaration* elementDec, OWNER(Sts_MetaDeclarationValue) name, Sts_MetaElementDeclarationType type);
void Sts_MetaElementDeclaration_free(Sts_MetaElementDeclaration* elementDec);

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
//

struct Sts_MetaNamespaceDeclaration {
  Sts_MetaDeclarationHead head;
  Sts_MetaDeclarations declarations;
};
void Sts_MetaNamespaceDeclaration_init(Sts_MetaNamespaceDeclaration* namespaceDec, OWNER(Sts_MetaDeclarationValue) name);
void Sts_MetaNamespaceDeclaration_free(Sts_MetaNamespaceDeclaration* namespaceDec);

enum Sts_MetaDeclarationType {
  Sts_MetaDeclarationType_ELEMENT,
  Sts_MetaDeclarationType_NAMESPACE,
};

struct Sts_MetaDeclaration {
  Sts_MetaDeclarationType type;
  union {
    Sts_MetaElementDeclaration element;
    Sts_MetaNamespaceDeclaration* namespace;
  } value;
};
Sts_MetaDeclaration Sts_MetaDeclaration_byElement(Sts_MetaElementDeclaration element);
Sts_MetaDeclaration Sts_MetaDeclaration_byNamespace(Sts_MetaNamespaceDeclaration* namespace);
void Sts_MetaDeclaration_initByElement(Sts_MetaDeclaration* declaration, Sts_MetaElementDeclaration element);
void Sts_MetaDeclaration_initByNamespace(Sts_MetaDeclaration* declaration, Sts_MetaNamespaceDeclaration* namespace);
void Sts_MetaDeclaration_free(Sts_MetaDeclaration* declaration);

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


struct Sts_MetaDeclarationFile {
  Sts_MetaNamespaceDeclaration* baseNamespaceDeclaration;
  StringMap regexes;
  Sts_MetaDeclarationValue mainZone;
};
void Sts_MetaDeclarationFile_init(Sts_MetaDeclarationFile* decFile);
void Sts_MetaDeclarationFile_free(Sts_MetaDeclarationFile* decFile);
