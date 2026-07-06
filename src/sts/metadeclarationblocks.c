#include "metadeclarationblocks.h"

#include "allocator.h"

void Sts_MetaDeclarationValueName_free(Sts_MetaDeclarationValueName* decValueName) {
  String_free(&decValueName->name);
  decValueName->parentNamespace = null;
}

Sts_MetaDeclarationValue Sts_MetaDeclarationValue_byName(Sts_MetaDeclarationValueName decValueName) {
  return (Sts_MetaDeclarationValue) {
    .type = Sts_MetaDeclarationValueType_NAME,
    .value = { .name = decValueName },
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
void Sts_MetaDeclarationValue_initByName(Sts_MetaDeclarationValue* decValue, Sts_MetaDeclarationValueName decValueName) {
  *decValue = Sts_MetaDeclarationValue_byName(decValueName);
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
    Sts_MetaDeclarationValueName_free(&decValue->value.name);
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

Sts_MetaLineDeclaration Sts_MetaLineDeclaration_byParam(Sts_MetaLineParamDeclaration param) {
  return (Sts_MetaLineDeclaration) {
    .type = Sts_MetaLineDeclarationType_PARAM,
    .value = { .param = param },
  };
}
Sts_MetaLineDeclaration Sts_MetaLineDeclaration_byVariable(Sts_MetaLineVariableDeclaration variable) {
  return (Sts_MetaLineDeclaration) {
    .type = Sts_MetaLineDeclarationType_VARIABLE,
    .value = { .variable = variable },
  };
}
Sts_MetaLineDeclaration Sts_MetaLineDeclaration_byEvent(Sts_MetaLineEventDeclaration event) {
  return (Sts_MetaLineDeclaration) {
    .type = Sts_MetaLineDeclarationType_EVENT,
    .value = { .event = event },
  };
}
Sts_MetaLineDeclaration Sts_MetaLineDeclaration_byExpand(Sts_MetaLineExpandDeclaration expand) {
  return (Sts_MetaLineDeclaration) {
    .type = Sts_MetaLineDeclarationType_EXPAND,
    .value = { .expand = expand },
  };
}
Sts_MetaLineDeclaration Sts_MetaLineDeclaration_bySuperRegex(Sts_MetaLineSuperRegexDeclaration superRegex) {
  return (Sts_MetaLineDeclaration) {
    .type = Sts_MetaLineDeclarationType_SUPER_REGEX,
    .value = { .superRegex = superRegex },
  };
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
Sts_MetaDeclaration Sts_MetaDeclaration_byNamespace(Sts_MetaNamespaceDeclaration* namespace) {
  return (Sts_MetaDeclaration) {
    .type = Sts_MetaDeclarationType_NAMESPACE,
    .value = { .namespace = namespace },
  };
}
void Sts_MetaDeclaration_initByElement(Sts_MetaDeclaration* declaration, Sts_MetaElementDeclaration element) {
  *declaration = Sts_MetaDeclaration_byElement(element);
}
void Sts_MetaDeclaration_initByNamespace(Sts_MetaDeclaration* declaration, Sts_MetaNamespaceDeclaration* namespace) {
  *declaration = Sts_MetaDeclaration_byNamespace(namespace);
}
void Sts_MetaDeclaration_free(Sts_MetaDeclaration* declaration) {
  if (declaration->type == Sts_MetaDeclarationType_ELEMENT) {
    Sts_MetaElementDeclaration_free(&declaration->value.element);
  }
  else if (declaration->type == Sts_MetaDeclarationType_NAMESPACE) {
    Sts_MetaNamespaceDeclaration_free(declaration->value.namespace);
    A_free(declaration->value.namespace);
  }
}

void Sts_MetaDeclarationFile_init(Sts_MetaDeclarationFile* decFile) {
  decFile->baseNamespaceDeclaration = A_xloc(sizeof(Sts_MetaNamespaceDeclaration));
  Sts_MetaDeclarations_init(&decFile->baseNamespaceDeclaration->declarations, 50);
  decFile->baseNamespaceDeclaration->head = (Sts_MetaDeclarationHead) {
    .name = {0},
    .linkNames = {0},
    .extenders = {0},
    .isGeneric = false,
    .isGhost = false,
  };
  StringMap_init(&decFile->regexes);
  decFile->mainZone = (Sts_MetaDeclarationValue) {0};
}
void Sts_MetaDeclarationFile_free(Sts_MetaDeclarationFile* decFile) {
  Sts_MetaNamespaceDeclaration_free(decFile->baseNamespaceDeclaration);
  A_free(decFile->baseNamespaceDeclaration);
  StringMap_free(&decFile->regexes);
  Sts_MetaDeclarationValue_free(&decFile->mainZone);
}
