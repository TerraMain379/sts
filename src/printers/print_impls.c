#include "prints.h"
#include "print_utils.h"
#include "print_json_utils.h"

#include "allocator.h"


// ###########################
// #       collections       #
// ###########################
#include "stringlist.h"

dec_print(StringList) {
  print_glist(StringList, String,,&);
}
dec_print_json(StringList) {
  print_json_glist(StringList, String,,&);
}


// ##########################
// #       metablocks       #
// ##########################
#include "metablocks.h"

dec_print(Sts_MetaRegex) {
  print_struct_init;
  print_field_value(String, regex);
  print_struct_return;
}
dec_print_json(Sts_MetaRegex) {
  print_json_struct_init;
  print_json_field_value(String, regex);
  print_json_struct_return;
}

dec_print(Sts_MetaRegexLinks) {
  print_gmap(Sts_MetaRegexLinks, Sts_MetaRegex,,&);
}
dec_print_json(Sts_MetaRegexLinks) {
  print_json_gmap(Sts_MetaRegexLinks, Sts_MetaRegex,,&);
}

dec_print(Sts_MetaEvent) {
  print_struct_init;
  print_field_value(String, code);
  print_struct_return;
}
dec_print_json(Sts_MetaEvent) {
  print_json_struct_init;
  print_json_field_value(String, code);
  print_json_struct_return;
}

dec_print(Sts_MetaEvents) {
  print_gmap(Sts_MetaEvents, Sts_MetaEvent,,&);
}
dec_print_json(Sts_MetaEvents) {
  print_json_gmap(Sts_MetaEvents, Sts_MetaEvent,,&);
}

dec_print(Sts_MetaElementVariable) {
  print_struct_init;
  print_field_value(Stss_Type, type);
  print_field_ptr(Stss_UntypeValue, value);
  print_struct_return;
}
dec_print_json(Sts_MetaElementVariable) {
  print_json_struct_init;
  print_json_field_value(Stss_Type, type);
  print_json_field_ptr(Stss_UntypeValue, value);
  print_json_struct_return;
}

dec_print(Sts_MetaElementVariables) {
  print_gmap(Sts_MetaElementVariables, Sts_MetaElementVariable,,&);
}
dec_print_json(Sts_MetaElementVariables) {
  print_json_gmap(Sts_MetaElementVariables, Sts_MetaElementVariable,,&);
}

dec_print(Sts_MetaElementStaticParam) {
  print_struct_init;
  print_field_value(Stss_Type, type);
  print_field_ptr(Stss_UntypeValue, value);
  print_struct_return;
}
dec_print_json(Sts_MetaElementStaticParam) {
  print_json_struct_init;
  print_json_field_value(Stss_Type, type);
  print_json_field_ptr(Stss_UntypeValue, value);
  print_json_struct_return;
}

dec_print(Sts_MetaElementStaticParams) {
  print_gmap(Sts_MetaElementStaticParams, Sts_MetaElementStaticParam,,&);
}
dec_print_json(Sts_MetaElementStaticParams) {
  print_json_gmap(Sts_MetaElementStaticParams, Sts_MetaElementStaticParam,,&);
}

dec_print(Sts_MetaElement) {
  print_struct_init;
  print_field_value(String, name);
  print_field_value(Sts_MetaElementStaticParams, params);
  print_field_value(Sts_MetaElementVariables, variables);
  print_field_value(Sts_MetaEvents, events);
  print_struct_return;
}
dec_print_json(Sts_MetaElement) {
  print_json_struct_init;
  print_json_field_value(String, name);
  print_json_field_value(Sts_MetaElementStaticParams, params);
  print_json_field_value(Sts_MetaElementVariables, variables);
  print_json_field_value(Sts_MetaEvents, events);
  print_json_struct_return;
}

dec_print(Sts_MetaToken) {
  print_struct_init;
  print_field_value(String, name);
  print_field_value(Sts_MetaElementStaticParams, params);
  print_field_value(Sts_MetaElementVariables, variables);
  print_field_value(Sts_MetaEvents, events);
  print_struct_return;
}
dec_print_json(Sts_MetaToken) {
  print_json_struct_init;
  print_json_field_value(String, name);
  print_json_field_value(Sts_MetaElementStaticParams, params);
  print_json_field_value(Sts_MetaElementVariables, variables);
  print_json_field_value(Sts_MetaEvents, events);
  print_json_struct_return;
}

dec_print(Sts_OwnedMetaTokens) {
  print_gmap(Sts_OwnedMetaTokens, Sts_MetaToken,*,);
}
dec_print_json(Sts_OwnedMetaTokens) {
  print_json_gmap(Sts_OwnedMetaTokens, Sts_MetaToken,*,);
}

dec_print(Sts_MetaTokens) {
  print_gmap(Sts_MetaTokens, Sts_MetaToken,*,);
}
dec_print_json(Sts_MetaTokens) {
  print_json_gmap(Sts_MetaTokens, Sts_MetaToken,*,);
}

dec_print(Sts_MetaZone) {
  print_struct_init;
  print_field_value(String, name);
  print_field_value(Sts_MetaElementStaticParams, params);
  print_field_value(Sts_MetaElementVariables, variables);
  print_field_value(Sts_MetaEvents, events);
  print_field_value(Sts_MetaTokens, tokens);
  print_field_value(Sts_MetaZones, expandZones);
  print_struct_return;
}
dec_print_json(Sts_MetaZone) {
  print_json_struct_init;
  print_json_field_value(String, name);
  print_json_field_value(Sts_MetaElementStaticParams, params);
  print_json_field_value(Sts_MetaElementVariables, variables);
  print_json_field_value(Sts_MetaEvents, events);
  print_json_field_value(Sts_MetaTokens, tokens);
  print_json_field_value(Sts_MetaZones, expandZones);
  print_json_struct_return;
}

dec_print(Sts_OwnedMetaZonesMap) {
  print_gmap(Sts_OwnedMetaZonesMap, Sts_MetaZone,*,);
}
dec_print_json(Sts_OwnedMetaZonesMap) {
  print_json_gmap(Sts_OwnedMetaZonesMap, Sts_MetaZone,*,);
}

dec_print(Sts_MetaZones) {
  print_glist(Sts_MetaZones, Sts_MetaZone,*,);
}
dec_print_json(Sts_MetaZones) {
  print_json_glist(Sts_MetaZones, Sts_MetaZone,*,);
}

#define Sts_MetaNamespaceDeclaration__ptr Sts_MetaNamespaceDeclaration
dec_print(Sts_MetaNamespaceDeclaration__ptr) {
  print_struct_init;
  print_field_value(Sts_MetaDeclarationHead, head);
  print_struct_return;
}
dec_print_json(Sts_MetaNamespaceDeclaration__ptr) {
  print_json_struct_init;
  print_json_field_value(Sts_MetaDeclarationHead, head);
  print_json_struct_return;
}
#undef Sts_MetaNamespaceDeclaration__ptr


dec_print(Sts_MetaDeclarationValueName) {
  print_struct_init;
  print_field_value(String, name);
  print_field_ptr(Sts_MetaNamespaceDeclaration__ptr, parentNamespace);
  print_struct_return;
}
dec_print_json(Sts_MetaDeclarationValueName) {
  print_json_struct_init;
  print_json_field_value(String, name);
  print_json_field_ptr(Sts_MetaNamespaceDeclaration__ptr, parentNamespace);
  print_json_struct_return;
}

dec_print(Sts_MetaDeclarationValueType) {
  print_enum(Sts_MetaDeclarationValueType_NULL);
  print_enum(Sts_MetaDeclarationValueType_NAME);
  print_enum(Sts_MetaDeclarationValueType_STRING);
  print_enum(Sts_MetaDeclarationValueType_NUMBER);
  print_enum(Sts_MetaDeclarationValueType_EXPRESSION);
  print_enum(Sts_MetaDeclarationValueType_LINK);
  print_enum_end;
}
dec_print_json(Sts_MetaDeclarationValueType) {
  print_json_enum(Sts_MetaDeclarationValueType_NULL);
  print_json_enum(Sts_MetaDeclarationValueType_NAME);
  print_json_enum(Sts_MetaDeclarationValueType_STRING);
  print_json_enum(Sts_MetaDeclarationValueType_NUMBER);
  print_json_enum(Sts_MetaDeclarationValueType_EXPRESSION);
  print_json_enum(Sts_MetaDeclarationValueType_LINK);
  print_json_enum_end;
}

dec_print(Sts_MetaDeclarationValue) {
  print_struct_init;
  print_field_value(Sts_MetaDeclarationValueType, type);
  if (input->type == Sts_MetaDeclarationValueType_NAME) {
    print_field_value(Sts_MetaDeclarationValueName, value.name);
  }
  else if (input->type == Sts_MetaDeclarationValueType_STRING) {
    print_field_value(String, value.string);
  }
  else if (input->type == Sts_MetaDeclarationValueType_NUMBER) {
    print_field_value(double, value.number);
  }
  else if (input->type == Sts_MetaDeclarationValueType_EXPRESSION) {
    print_field_ptr(Sts_MetaDeclarationExpression, value.expression);
  }
  else if (input->type == Sts_MetaDeclarationValueType_LINK) {
    print_field_value(String, value.linkName);
  }
  else if (input->type == Sts_MetaDeclarationValueType_NULL) { }
  else {
    Errors_internal_unexpectedEnumType(ViewString_of("Sts_MetaDeclarationValue_print_json"));
    non_call_return (String) {};
  }
  print_struct_return;
}
dec_print_json(Sts_MetaDeclarationValue) {
  print_json_struct_init;
  print_json_field_value(Sts_MetaDeclarationValueType, type);
  if (input->type == Sts_MetaDeclarationValueType_NAME) {
    print_json_field_value(Sts_MetaDeclarationValueName, value.name);
  }
  else if (input->type == Sts_MetaDeclarationValueType_STRING) {
    print_json_field_value(String, value.string);
  }
  else if (input->type == Sts_MetaDeclarationValueType_NUMBER) {
    print_json_field_value(double, value.number);
  }
  else if (input->type == Sts_MetaDeclarationValueType_EXPRESSION) {
    print_json_field_ptr(Sts_MetaDeclarationExpression, value.expression);
  }
  else if (input->type == Sts_MetaDeclarationValueType_LINK) {
    print_json_field_value(String, value.linkName);
  }
  else if (input->type == Sts_MetaDeclarationValueType_NULL) { }
  else {
    Errors_internal_unexpectedEnumType(ViewString_of("Sts_MetaDeclarationValue_print_json"));
    non_call_return (String) {};
  }
  print_json_struct_return;
}

dec_print(Sts_MetaDeclarationValueList) {
  print_glist(Sts_MetaDeclarationValueList, Sts_MetaDeclarationValue, , &);
}
dec_print_json(Sts_MetaDeclarationValueList) {
  print_json_glist(Sts_MetaDeclarationValueList, Sts_MetaDeclarationValue, , &);
}

dec_print(Sts_MetaDeclarationExpressionType) {
  print_enum(Sts_MetaDeclarationExpressionType_ASSIGN);
  print_enum(Sts_MetaDeclarationExpressionType_SUM);
  print_enum(Sts_MetaDeclarationExpressionType_SUB);
  print_enum(Sts_MetaDeclarationExpressionType_MUL);
  print_enum(Sts_MetaDeclarationExpressionType_DIV);
  print_enum(Sts_MetaDeclarationExpressionType_MOD);
  print_enum(Sts_MetaDeclarationExpressionType_POW);
  print_enum(Sts_MetaDeclarationExpressionType_NOT);
  print_enum(Sts_MetaDeclarationExpressionType_INC);
  print_enum(Sts_MetaDeclarationExpressionType_DEC);
  print_enum(Sts_MetaDeclarationExpressionType_LOGICAL_OR);
  print_enum(Sts_MetaDeclarationExpressionType_LOGICAL_AND);
  print_enum(Sts_MetaDeclarationExpressionType_BITWISE_OR);
  print_enum(Sts_MetaDeclarationExpressionType_BITWISE_XOR);
  print_enum(Sts_MetaDeclarationExpressionType_BITWISE_AND);
  print_enum(Sts_MetaDeclarationExpressionType_LOGICAL_EQL);
  print_enum(Sts_MetaDeclarationExpressionType_LOGICAL_NOT_EQL);
  print_enum(Sts_MetaDeclarationExpressionType_LOGICAL_GT);
  print_enum(Sts_MetaDeclarationExpressionType_LOGICAL_LT);
  print_enum(Sts_MetaDeclarationExpressionType_LOGICAL_GTE);
  print_enum(Sts_MetaDeclarationExpressionType_LOGICAL_LTE);
  print_enum(Sts_MetaDeclarationExpressionType_TERN_COND_IF);
  print_enum(Sts_MetaDeclarationExpressionType_TERN_COND_ELSE);
  print_enum(Sts_MetaDeclarationExpressionType_CHILD);
  print_enum_end;
}
dec_print_json(Sts_MetaDeclarationExpressionType) {
  print_json_enum(Sts_MetaDeclarationExpressionType_ASSIGN);
  print_json_enum(Sts_MetaDeclarationExpressionType_SUM);
  print_json_enum(Sts_MetaDeclarationExpressionType_SUB);
  print_json_enum(Sts_MetaDeclarationExpressionType_MUL);
  print_json_enum(Sts_MetaDeclarationExpressionType_DIV);
  print_json_enum(Sts_MetaDeclarationExpressionType_MOD);
  print_json_enum(Sts_MetaDeclarationExpressionType_POW);
  print_json_enum(Sts_MetaDeclarationExpressionType_NOT);
  print_json_enum(Sts_MetaDeclarationExpressionType_INC);
  print_json_enum(Sts_MetaDeclarationExpressionType_DEC);
  print_json_enum(Sts_MetaDeclarationExpressionType_LOGICAL_OR);
  print_json_enum(Sts_MetaDeclarationExpressionType_LOGICAL_AND);
  print_json_enum(Sts_MetaDeclarationExpressionType_BITWISE_OR);
  print_json_enum(Sts_MetaDeclarationExpressionType_BITWISE_XOR);
  print_json_enum(Sts_MetaDeclarationExpressionType_BITWISE_AND);
  print_json_enum(Sts_MetaDeclarationExpressionType_LOGICAL_EQL);
  print_json_enum(Sts_MetaDeclarationExpressionType_LOGICAL_NOT_EQL);
  print_json_enum(Sts_MetaDeclarationExpressionType_LOGICAL_GT);
  print_json_enum(Sts_MetaDeclarationExpressionType_LOGICAL_LT);
  print_json_enum(Sts_MetaDeclarationExpressionType_LOGICAL_GTE);
  print_json_enum(Sts_MetaDeclarationExpressionType_LOGICAL_LTE);
  print_json_enum(Sts_MetaDeclarationExpressionType_TERN_COND_IF);
  print_json_enum(Sts_MetaDeclarationExpressionType_TERN_COND_ELSE);
  print_json_enum(Sts_MetaDeclarationExpressionType_CHILD);
  print_json_enum_end;
}

dec_print(Sts_MetaDeclarationExpression) {
  print_struct_init;
  print_field_value(Sts_MetaDeclarationExpressionType, type);
  print_field_value(Sts_MetaDeclarationValue, value1);
  print_field_value(Sts_MetaDeclarationValue, value2);
  print_struct_return;
}
dec_print_json(Sts_MetaDeclarationExpression) {
  print_json_struct_init;
  print_json_field_value(Sts_MetaDeclarationExpressionType, type);
  print_json_field_value(Sts_MetaDeclarationValue, value1);
  print_json_field_value(Sts_MetaDeclarationValue, value2);
  print_json_struct_return;
}

dec_print(Sts_MetaLineParamDeclaration) {
  print_struct_init;
  print_field_value(Sts_MetaDeclarationValue, name);
  print_field_value(Sts_MetaDeclarationValueList, values);
  print_struct_return;
}
dec_print_json(Sts_MetaLineParamDeclaration) {
  print_json_struct_init;
  print_json_field_value(Sts_MetaDeclarationValue, name);
  print_json_field_value(Sts_MetaDeclarationValueList, values);
  print_json_struct_return;
}

dec_print(Sts_MetaLineVariableDeclaration) {
  print_struct_init;
  print_field_value(bool, isInit);
  print_field_value(Sts_MetaDeclarationValue, name);
  print_field_value(Sts_MetaDeclarationValue, typing);
  print_field_value(Sts_MetaDeclarationValue, value);
  print_struct_return;
}
dec_print_json(Sts_MetaLineVariableDeclaration) {
  print_json_struct_init;
  print_json_field_value(bool, isInit);
  print_json_field_value(Sts_MetaDeclarationValue, name);
  print_json_field_value(Sts_MetaDeclarationValue, typing);
  print_json_field_value(Sts_MetaDeclarationValue, value);
  print_json_struct_return;
}

dec_print(Sts_MetaLineEventDeclaration) {
  print_struct_init;
  print_field_value(Sts_MetaDeclarationValue, name);
  print_field_value(Sts_MetaDeclarationValue, event);
  print_struct_return;
}
dec_print_json(Sts_MetaLineEventDeclaration) {
  print_json_struct_init;
  print_json_field_value(Sts_MetaDeclarationValue, name);
  print_json_field_value(Sts_MetaDeclarationValue, event);
  print_json_struct_return;
}

dec_print(Sts_MetaLineExpandDeclaration) {
  print_struct_init;
  print_field_value(Sts_MetaDeclarationValue, zoneName);
  print_field_value(bool, isExport);
  print_struct_return;
}
dec_print_json(Sts_MetaLineExpandDeclaration) {
  print_json_struct_init;
  print_json_field_value(Sts_MetaDeclarationValue, zoneName);
  print_json_field_value(bool, isExport);
  print_json_struct_return;
}

dec_print(Sts_MetaLineSuperRegexDeclarationElement) {
  print_struct_init;
  print_field_value(Sts_MetaDeclarationValue, token);
  print_field_value(Sts_MetaDeclarationValue, name);
  print_field_value(bool, isOptional);
  print_field_value(bool, isNonName);
  print_struct_return;
}
dec_print_json(Sts_MetaLineSuperRegexDeclarationElement) {
  print_json_struct_init;
  print_json_field_value(Sts_MetaDeclarationValue, token);
  print_json_field_value(Sts_MetaDeclarationValue, name);
  print_json_field_value(bool, isOptional);
  print_json_field_value(bool, isNonName);
  print_json_struct_return;
}

dec_print(Sts_MetaLineSuperRegexDeclarationElements) {
  print_glist(Sts_MetaLineSuperRegexDeclarationElements, Sts_MetaLineSuperRegexDeclarationElement, , &);
}
dec_print_json(Sts_MetaLineSuperRegexDeclarationElements) {
  print_json_glist(Sts_MetaLineSuperRegexDeclarationElements, Sts_MetaLineSuperRegexDeclarationElement, , &);
}

dec_print(Sts_MetaLineSuperRegexDeclaration) {
  print_struct_init;
  print_field_value(Sts_MetaLineSuperRegexDeclarationElements, elements);
  print_field_value(bool, isGhost);
  print_struct_return;
}
dec_print_json(Sts_MetaLineSuperRegexDeclaration) {
  print_json_struct_init;
  print_json_field_value(Sts_MetaLineSuperRegexDeclarationElements, elements);
  print_json_field_value(bool, isGhost);
  print_json_struct_return;
}

dec_print(Sts_MetaLineDeclarationType) {
  print_enum(Sts_MetaLineDeclarationType_PARAM);
  print_enum(Sts_MetaLineDeclarationType_VARIABLE);
  print_enum(Sts_MetaLineDeclarationType_EVENT);
  print_enum(Sts_MetaLineDeclarationType_EXPAND);
  print_enum(Sts_MetaLineDeclarationType_SUPER_REGEX);
  print_enum_end;
}
dec_print_json(Sts_MetaLineDeclarationType) {
  print_json_enum(Sts_MetaLineDeclarationType_PARAM);
  print_json_enum(Sts_MetaLineDeclarationType_VARIABLE);
  print_json_enum(Sts_MetaLineDeclarationType_EVENT);
  print_json_enum(Sts_MetaLineDeclarationType_EXPAND);
  print_json_enum(Sts_MetaLineDeclarationType_SUPER_REGEX);
  print_json_enum_end;
}

dec_print(Sts_MetaLineDeclaration) {
  print_struct_init;
  print_field_value(Sts_MetaLineDeclarationType, type);
  if (input->type == Sts_MetaLineDeclarationType_PARAM) {
    print_field_value(Sts_MetaLineParamDeclaration, value.param);
  }
  else if (input->type == Sts_MetaLineDeclarationType_VARIABLE) {
    print_field_value(Sts_MetaLineVariableDeclaration, value.variable);
  }
  else if (input->type == Sts_MetaLineDeclarationType_EVENT) {
    print_field_value(Sts_MetaLineEventDeclaration, value.event);
  }
  else if (input->type == Sts_MetaLineDeclarationType_EXPAND) {
    print_field_value(Sts_MetaLineExpandDeclaration, value.expand);
  }
  else if (input->type == Sts_MetaLineDeclarationType_SUPER_REGEX) {
    print_field_value(Sts_MetaLineSuperRegexDeclaration, value.superRegex);
  }
  else {
    Errors_internal_unexpectedEnumType(ViewString_of("Sts_MetaLineDeclaration_print"));
    non_call_return (String) {};
  }
  print_struct_return;
}
dec_print_json(Sts_MetaLineDeclaration) {
  print_json_struct_init;
  print_json_field_value(Sts_MetaLineDeclarationType, type);
  if (input->type == Sts_MetaLineDeclarationType_PARAM) {
    print_json_field_value(Sts_MetaLineParamDeclaration, value.param);
  }
  else if (input->type == Sts_MetaLineDeclarationType_VARIABLE) {
    print_json_field_value(Sts_MetaLineVariableDeclaration, value.variable);
  }
  else if (input->type == Sts_MetaLineDeclarationType_EVENT) {
    print_json_field_value(Sts_MetaLineEventDeclaration, value.event);
  }
  else if (input->type == Sts_MetaLineDeclarationType_EXPAND) {
    print_json_field_value(Sts_MetaLineExpandDeclaration, value.expand);
  }
  else if (input->type == Sts_MetaLineDeclarationType_SUPER_REGEX) {
    print_json_field_value(Sts_MetaLineSuperRegexDeclaration, value.superRegex);
  }
  else {
    Errors_internal_unexpectedEnumType(ViewString_of("Sts_MetaLineDeclaration_print_json"));
    non_call_return (String) {};
  }
  print_json_struct_return;
}

dec_print(Sts_MetaLineDeclarationList) {
  print_glist(Sts_MetaLineDeclarationList, Sts_MetaLineDeclaration, *,);
}
dec_print_json(Sts_MetaLineDeclarationList) {
  print_json_glist(Sts_MetaLineDeclarationList, Sts_MetaLineDeclaration, *,);
}

dec_print(Sts_MetaDeclarationValueWeakList) {
  print_glist(Sts_MetaDeclarationValueWeakList, Sts_MetaDeclarationValue, *,);
}
dec_print_json(Sts_MetaDeclarationValueWeakList) {
  print_json_glist(Sts_MetaDeclarationValueWeakList, Sts_MetaDeclarationValue, *,);
}

dec_print(Sts_MetaDeclarationExtendElement) {
  print_struct_init;
  print_field_value(Sts_MetaDeclarationValue, name);
  print_field_value(Sts_MetaDeclarationValueList, linksValues);
  print_struct_return;
}
dec_print_json(Sts_MetaDeclarationExtendElement) {
  print_json_struct_init;
  print_json_field_value(Sts_MetaDeclarationValue, name);
  print_json_field_value(Sts_MetaDeclarationValueList, linksValues);
  print_json_struct_return;
}

dec_print(Sts_MetaDeclarationExtendElementList) {
  print_glist(Sts_MetaDeclarationExtendElementList, Sts_MetaDeclarationExtendElement, , &);
}
dec_print_json(Sts_MetaDeclarationExtendElementList) {
  print_json_glist(Sts_MetaDeclarationExtendElementList, Sts_MetaDeclarationExtendElement, , &);
}

dec_print(Sts_MetaDeclarationHead) {
  print_struct_init;
  print_field_value(Sts_MetaDeclarationValue, name);
  print_field_value(StringList, linkNames);
  print_field_value(Sts_MetaDeclarationExtendElementList, extenders);
  print_struct_return;
}
dec_print_json(Sts_MetaDeclarationHead) {
  print_json_struct_init;
  print_json_field_value(Sts_MetaDeclarationValue, name);
  print_json_field_value(StringList, linkNames);
  print_json_field_value(Sts_MetaDeclarationExtendElementList, extenders);
  print_json_struct_return;
}

dec_print(Sts_MetaElementDeclarationType) {
  print_enum(Sts_MetaElementDeclarationType_TOKEN);
  print_enum(Sts_MetaElementDeclarationType_ZONE);
  print_enum(Sts_MetaElementDeclarationType_GROUP);
  print_enum(Sts_MetaElementDeclarationType_SUPER_TOKEN);
  print_enum_end;
}
dec_print_json(Sts_MetaElementDeclarationType) {
  print_json_enum(Sts_MetaElementDeclarationType_TOKEN);
  print_json_enum(Sts_MetaElementDeclarationType_ZONE);
  print_json_enum(Sts_MetaElementDeclarationType_GROUP);
  print_json_enum(Sts_MetaElementDeclarationType_SUPER_TOKEN);
  print_json_enum_end;
}

dec_print(Sts_MetaElementDeclaration) {
  print_struct_init;
  print_field_value(Sts_MetaDeclarationHead, head);
  print_field_value(Sts_MetaElementDeclarationType, type);
  print_field_value(Sts_MetaLineDeclarationList, lineDeclarations);
  print_struct_return;
}
dec_print_json(Sts_MetaElementDeclaration) {
  print_json_struct_init;
  print_json_field_value(Sts_MetaDeclarationHead, head);
  print_json_field_value(Sts_MetaElementDeclarationType, type);
  print_json_field_value(Sts_MetaLineDeclarationList, lineDeclarations);
  print_json_struct_return;
}

dec_print(Sts_MetaNamespaceDeclaration) {
  print_struct_init;
  print_field_value(Sts_MetaDeclarationHead, head);
  print_field_value(Sts_MetaDeclarations, declarations);
  print_struct_return;
}
dec_print_json(Sts_MetaNamespaceDeclaration) {
  print_json_struct_init;
  print_json_field_value(Sts_MetaDeclarationHead, head);
  print_json_field_value(Sts_MetaDeclarations, declarations);
  print_json_struct_return;
}

dec_print(Sts_MetaDeclarationType) {
  print_enum(Sts_MetaDeclarationType_ELEMENT);
  print_enum(Sts_MetaDeclarationType_NAMESPACE);
  print_enum_end;
}
dec_print_json(Sts_MetaDeclarationType) {
  print_json_enum(Sts_MetaDeclarationType_ELEMENT);
  print_json_enum(Sts_MetaDeclarationType_NAMESPACE);
  print_json_enum_end;
}

dec_print(Sts_MetaDeclaration) {
  print_struct_init;
  print_field_value(Sts_MetaDeclarationType, type);
  if (input->type == Sts_MetaDeclarationType_ELEMENT) {
    print_field_value(Sts_MetaElementDeclaration, value.element);
  }
  else if (input->type == Sts_MetaDeclarationType_NAMESPACE) {
    print_field_ptr(Sts_MetaNamespaceDeclaration, value.namespace);
  }
  else {
    Errors_internal_unexpectedEnumType(ViewString_of("Sts_MetaDeclaration_print"));
    non_call_return (String) {};
  }
  print_struct_return;
}
dec_print_json(Sts_MetaDeclaration) {
  print_json_struct_init;
  print_json_field_value(Sts_MetaDeclarationType, type);
  if (input->type == Sts_MetaDeclarationType_ELEMENT) {
    print_json_field_value(Sts_MetaElementDeclaration, value.element);
  }
  else if (input->type == Sts_MetaDeclarationType_NAMESPACE) {
    print_json_field_ptr(Sts_MetaNamespaceDeclaration, value.namespace);
  }
  else {
    Errors_internal_unexpectedEnumType(ViewString_of("Sts_MetaDeclaration_print_json"));
    non_call_return (String) {};
  }
  print_json_struct_return;
}

dec_print(Sts_MetaDeclarations) {
  print_glist(Sts_MetaDeclarations, Sts_MetaDeclaration, , &);
}
dec_print_json(Sts_MetaDeclarations) {
  print_json_glist(Sts_MetaDeclarations, Sts_MetaDeclaration, , &);
}

dec_print(Sts_MetaFile) {
  print_struct_init;
  print_field_ptr(Sts_MetaNamespaceDeclaration, baseNamespaceDeclaration);
  print_field_value(Sts_MetaRegexLinks, regexes);
  print_field_value(Sts_OwnedMetaZonesMap, zones);
  print_field_value(Sts_OwnedMetaTokens, tokens);
  print_field_ptr(Sts_MetaZone, mainZone);
  print_field_value(String, properties.name);
  print_field_value(Sources, properties.sources);
  print_struct_return;
}
dec_print_json(Sts_MetaFile) {
  print_json_struct_init;
  print_json_field_ptr(Sts_MetaNamespaceDeclaration, baseNamespaceDeclaration);
  print_json_field_value(Sts_MetaRegexLinks, regexes);
  print_json_field_value(Sts_OwnedMetaZonesMap, zones);
  print_json_field_value(Sts_OwnedMetaTokens, tokens);
  print_json_field_ptr(Sts_MetaZone, mainZone);
  print_json_field_value(String, properties.name);
  print_json_field_value(Sources, properties.sources);
  print_json_struct_return;
}

// ####################
// #       stss       #
// ####################
#include "stss.h"

dec_print(Stss_Type) {
  return String_by("<Stss_Type>");
}
dec_print_json(Stss_Type) {
  return String_by("\"<Stss_Type>\"");
}

dec_print(Stss_UntypeValue) {
  return String_by("<Stss_UntypeValue>");
}
dec_print_json(Stss_UntypeValue) {
  return String_by("\"<Stss_UntypeValue>\"");
}
