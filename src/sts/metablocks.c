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

#define PNAME Sts_MetaDeclarationValueWeakList
#define PTYPE WEAK(Sts_MetaDeclarationValue)
#undef PFREEFUN
#define BASE_LIST ConstList
#include "plist.c.h"
#undef PNAME
#undef PTYPE
#undef BASE_LIST

#define NAME Sts_MetaLineSuperRegexDeclarationElements
#define TYPE Sts_MetaLineSuperRegexDeclarationElement
#define NULLV (Sts_MetaLineSuperRegexDeclarationElement) {0}
#define FREEFUN Sts_MetaLineSuperRegexDeclarationElement_free
#include "glist.c.h"
#undef NAME
#undef TYPE
#undef NULLV
#undef FREEFUN

#define PNAME Sts_MetaLineDeclarationList
#define PTYPE OWNER(Sts_MetaLineDeclaration)
#define PFREEFUN Sts_MetaLineDeclaration_free
#define BASE_LIST List
#include "plist.c.h"
#undef PNAME
#undef PTYPE
#undef PFREEFUN
#undef BASE_LIST

#define NAME Sts_MetaDeclarationExtendElementList
#define TYPE OWNER(Sts_MetaDeclarationExtendElement)
#define NULLV (Sts_MetaDeclarationExtendElement) {0}
#define FREEFUN Sts_MetaDeclarationExtendElement_free
#include "glist.c.h"
#undef NAME
#undef TYPE
#undef NULLV
#undef FREEFUN

#define NAME Sts_MetaDeclarations
#define TYPE Sts_MetaDeclaration
#define NULLV (Sts_MetaDeclaration) {0}
#define FREEFUN Sts_MetaDeclaration_free
#include "glist.c.h"
#undef NAME
#undef TYPE
#undef NULLV
#undef FREEFUN


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

Sts_MetaDeclarationValue Sts_MetaDeclarationValue_byName(String name) {
  return (Sts_MetaDeclarationValue) {
    .type = Sts_MetaDeclarationValueType_NAME,
    .value = { .name = name },
  };
}
Sts_MetaDeclarationValue Sts_MetaDeclarationValue_byString(String string) {
  return (Sts_MetaDeclarationValue) {
    .type = Sts_MetaDeclarationValueType_STRING,
    .value = { .string = string },
  };
}
Sts_MetaDeclarationValue Sts_MetaDeclarationValue_byNumber(double number) {
  return (Sts_MetaDeclarationValue) {
    .type = Sts_MetaDeclarationValueType_NUMBER,
    .value = { .number = number },
  };
}
Sts_MetaDeclarationValue Sts_MetaDeclarationValue_byExpression(OWNER(Sts_MetaDeclarationExpression*) expression) {
  return (Sts_MetaDeclarationValue) {
    .type = Sts_MetaDeclarationValueType_EXPRESSION,
    .value = { .expression = expression },
  };
}
Sts_MetaDeclarationValue Sts_MetaDeclarationValue_byLinkName(String linkName) {
  return (Sts_MetaDeclarationValue) {
    .type = Sts_MetaDeclarationValueType_LINK,
    .value = { .linkName = linkName },
  };
}
void Sts_MetaDeclarationValue_initByName(Sts_MetaDeclarationValue* decValue, String name) {
  *decValue = Sts_MetaDeclarationValue_byName(name);
}
void Sts_MetaDeclarationValue_initByString(Sts_MetaDeclarationValue* decValue, String string) {
  *decValue = Sts_MetaDeclarationValue_byString(string);
}
void Sts_MetaDeclarationValue_initByNumber(Sts_MetaDeclarationValue* decValue, double number) {
  *decValue = Sts_MetaDeclarationValue_byNumber(number);
}
void Sts_MetaDeclarationValue_initByExpression(Sts_MetaDeclarationValue* decValue, OWNER(Sts_MetaDeclarationExpression*) expression) {
  *decValue = Sts_MetaDeclarationValue_byExpression(expression);
}
void Sts_MetaDeclarationValue_initByLinkName(Sts_MetaDeclarationValue* decValue, String linkName) {
  *decValue = Sts_MetaDeclarationValue_byLinkName(linkName);
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
void Sts_MetaLineParamDeclaration_free(Sts_MetaLineParamDeclaration* paramDec) {
  Sts_MetaDeclarationValue_free(&paramDec->name);
  Sts_MetaDeclarationValueList_freeElements(&paramDec->values);
  Sts_MetaDeclarationValueList_free(&paramDec->values);
}
void Sts_MetaLineVariableDeclaration_free(Sts_MetaLineVariableDeclaration* variableDec) {
  Sts_MetaDeclarationValue_free(&variableDec->name);
  Sts_MetaDeclarationValue_free(&variableDec->value);
  Sts_MetaDeclarationValue_free(&variableDec->typing);
}
void Sts_MetaLineEventDeclaration_free(Sts_MetaLineEventDeclaration* eventDec) {
  Sts_MetaDeclarationValue_free(&eventDec->name);
  Sts_MetaDeclarationValue_free(&eventDec->event);
}
void Sts_MetaLineExpandDeclaration_free(Sts_MetaLineExpandDeclaration* expandDec) {
  Sts_MetaDeclarationValue_free(&expandDec->zoneName);
}
void Sts_MetaLineSuperRegexDeclarationElement_free(Sts_MetaLineSuperRegexDeclarationElement* regexDecElement) {
  Sts_MetaDeclarationValue_free(&regexDecElement->token);
  Sts_MetaDeclarationValue_free(&regexDecElement->name);
}
void Sts_MetaLineSuperRegexDeclaration_free(Sts_MetaLineSuperRegexDeclaration* regexDec) {
  Sts_MetaLineSuperRegexDeclarationElements_freeElements(&regexDec->elements);
  Sts_MetaLineSuperRegexDeclarationElements_free(&regexDec->elements);
}
void Sts_MetaLineDeclaration_free(Sts_MetaLineDeclaration* lineDec) {
  Sts_MetaLineDeclarationType type = lineDec->type;
  if (type == Sts_MetaLineDeclarationType_PARAM) {
    Sts_MetaLineParamDeclaration_free(&lineDec->value.param);
  }
  else if (type == Sts_MetaLineDeclarationType_VARIABLE) {
    Sts_MetaLineVariableDeclaration_free(&lineDec->value.variable);
  }
  else if (type == Sts_MetaLineDeclarationType_EVENT) {
    Sts_MetaLineEventDeclaration_free(&lineDec->value.event);
  }
  else if (type == Sts_MetaLineDeclarationType_EXPAND) {
    Sts_MetaLineExpandDeclaration_free(&lineDec->value.expand);
  }
  else if (type == Sts_MetaLineDeclarationType_SUPER_REGEX) {
    Sts_MetaLineSuperRegexDeclaration_free(&lineDec->value.superRegex);
  }
}




void Sts_MetaDeclarationExtendElement_free(Sts_MetaDeclarationExtendElement* decName) {
  Sts_MetaDeclarationValue_free(&decName->name);
  Sts_MetaDeclarationValueList_freeElements(&decName->linksValues);
  Sts_MetaDeclarationValueList_free(&decName->linksValues);
}

void Sts_MetaDeclarationHead_init(Sts_MetaDeclarationHead* head, OWNER(Sts_MetaDeclarationValue) name) {
  head->name = name;
  StringList_init(&head->linkNames, 1);
  Sts_MetaDeclarationExtendElementList_init(&head->extenders, 1);
  head->isGeneric = false;
  head->isGhost = false;
}
void Sts_MetaDeclarationHead_free(Sts_MetaDeclarationHead* head) {
  Sts_MetaDeclarationValue_free(&head->name);
  StringList_freeElements(&head->linkNames);
  StringList_free(&head->linkNames);
  Sts_MetaDeclarationExtendElementList_freeElements(&head->extenders);
  Sts_MetaDeclarationExtendElementList_free(&head->extenders);
}

void Sts_MetaElementDeclaration_init(Sts_MetaElementDeclaration* elementDec, OWNER(Sts_MetaDeclarationValue) name, Sts_MetaElementDeclarationType type) {
  Sts_MetaDeclarationHead_init(&elementDec->head, name);
  elementDec->type = type;
  Sts_MetaLineDeclarationList_init(&elementDec->lineDeclarations, 8);
}
void Sts_MetaElementDeclaration_free(Sts_MetaElementDeclaration* elementDec) {
  Sts_MetaDeclarationHead_free(&elementDec->head);
  Sts_MetaLineDeclarationList_freeElements(&elementDec->lineDeclarations);
  Sts_MetaLineDeclarationList_free(&elementDec->lineDeclarations);
}

void Sts_MetaNamespaceDeclaration_init(Sts_MetaNamespaceDeclaration* namespaceDec, OWNER(Sts_MetaDeclarationValue) name) {
  Sts_MetaDeclarationHead_init(&namespaceDec->head, name);
  Sts_MetaDeclarations_init(&namespaceDec->declarations, 8);
}
void Sts_MetaNamespaceDeclaration_free(Sts_MetaNamespaceDeclaration* namespaceDec) {
  Sts_MetaDeclarationHead_free(&namespaceDec->head);
  Sts_MetaDeclarations_freeElements(&namespaceDec->declarations);
  Sts_MetaDeclarations_free(&namespaceDec->declarations);
}

Sts_MetaDeclaration Sts_MetaDeclaration_byElement(Sts_MetaElementDeclaration element) {
  return (Sts_MetaDeclaration) {
    .type = Sts_MetaDeclarationType_ELEMENT,
    .value = { .element = element },
  };
}
Sts_MetaDeclaration Sts_MetaDeclaration_byNamespace(Sts_MetaNamespaceDeclaration namespace) {
  return (Sts_MetaDeclaration) {
    .type = Sts_MetaDeclarationType_NAMESPACE,
    .value = { .namespace = namespace },
  };
}
void Sts_MetaDeclaration_initByElement(Sts_MetaDeclaration* declaration, Sts_MetaElementDeclaration element) {
  *declaration = Sts_MetaDeclaration_byElement(element);
}
void Sts_MetaDeclaration_initByNamespace(Sts_MetaDeclaration* declaration, Sts_MetaNamespaceDeclaration namespace) {
  *declaration = Sts_MetaDeclaration_byNamespace(namespace);
}
void Sts_MetaDeclaration_free(Sts_MetaDeclaration* declaration) {
  if (declaration->type == Sts_MetaDeclarationType_ELEMENT) {
    Sts_MetaElementDeclaration_free(&declaration->value.element);
  }
  else if (declaration->type == Sts_MetaDeclarationType_NAMESPACE) {
    Sts_MetaNamespaceDeclaration_free(&declaration->value.namespace);
  }
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
  Sts_MetaDeclarations_init(&metaFile->declarations, 50);
  Sts_MetaRegexLinks_init(&metaFile->regexes);
  Sts_OwnedMetaZonesMap_init(&metaFile->zones);
  Sts_OwnedMetaTokens_init(&metaFile->tokens);
  metaFile->mainZone = null;
  metaFile->properties.name = (String) {0};
  metaFile->properties.sources = (Sources) {0};
}
void Sts_MetaFile_free(Sts_MetaFile* metaFile) {
  Sts_MetaDeclarations_freeElements(&metaFile->declarations);
  Sts_MetaDeclarations_free(&metaFile->declarations);
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
