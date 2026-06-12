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
    print_field_value(String, value.name);
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
  else if (input->type == Sts_MetaDeclarationValueType_NULL) {
  }
  else {
    // TODO: ERROR
  }
  print_struct_return;
}
dec_print_json(Sts_MetaDeclarationValue) {
  print_json_struct_init;
  print_json_field_value(Sts_MetaDeclarationValueType, type);
  if (input->type == Sts_MetaDeclarationValueType_NAME) {
    print_json_field_value(String, value.name);
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
  else if (input->type == Sts_MetaDeclarationValueType_NULL) {
  }
  else {
    // TODO: ERROR
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
  print_enum(Sts_MetaDeclarationExpressionType_SUM);
  print_enum(Sts_MetaDeclarationExpressionType_SUB);
  print_enum(Sts_MetaDeclarationExpressionType_MUL);
  print_enum(Sts_MetaDeclarationExpressionType_DIV);
  print_enum(Sts_MetaDeclarationExpressionType_MOD);
  print_enum(Sts_MetaDeclarationExpressionType_POW);
  print_enum(Sts_MetaDeclarationExpressionType_INC);
  print_enum(Sts_MetaDeclarationExpressionType_DEC);
  print_enum(Sts_MetaDeclarationExpressionType_CHILD);
  
  print_enum_end;
}
dec_print_json(Sts_MetaDeclarationExpressionType) {
  print_json_enum(Sts_MetaDeclarationExpressionType_SUM);
  print_json_enum(Sts_MetaDeclarationExpressionType_SUB);
  print_json_enum(Sts_MetaDeclarationExpressionType_MUL);
  print_json_enum(Sts_MetaDeclarationExpressionType_DIV);
  print_json_enum(Sts_MetaDeclarationExpressionType_MOD);
  print_json_enum(Sts_MetaDeclarationExpressionType_POW);
  print_json_enum(Sts_MetaDeclarationExpressionType_INC);
  print_json_enum(Sts_MetaDeclarationExpressionType_DEC);
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

dec_print(Sts_MetaDeclarationTyping) {
  return String_const("{}");
}
dec_print_json(Sts_MetaDeclarationTyping) {
  return String_const("{}");
}

dec_print(Sts_MetaParamDeclaration) {
  print_struct_init;
  print_field_value(Sts_MetaDeclarationValue, name);
  print_field_value(Sts_MetaDeclarationValueList, values);
  print_struct_return;
}
dec_print_json(Sts_MetaParamDeclaration) {
  print_json_struct_init;
  print_json_field_value(Sts_MetaDeclarationValue, name);
  print_json_field_value(Sts_MetaDeclarationValueList, values);
  print_json_struct_return;
}

dec_print(Sts_MetaVariableDeclaration) {
  print_struct_init;
  print_field_value(bool, isInit);
  print_field_value(Sts_MetaDeclarationValue, name);
  print_field_value(Sts_MetaDeclarationTyping, typing);
  print_field_value(Sts_MetaDeclarationValue, value);
  print_struct_return;
}
dec_print_json(Sts_MetaVariableDeclaration) {
  print_json_struct_init;
  print_json_field_value(bool, isInit);
  print_json_field_value(Sts_MetaDeclarationValue, name);
  print_json_field_value(Sts_MetaDeclarationTyping, typing);
  print_json_field_value(Sts_MetaDeclarationValue, value);
  print_json_struct_return;
}

dec_print(Sts_MetaEventDeclaration) {
  print_struct_init;
  print_field_value(Sts_MetaDeclarationValue, name);
  print_field_value(Sts_MetaDeclarationValue, event);
  print_struct_return;
}
dec_print_json(Sts_MetaEventDeclaration) {
  print_json_struct_init;
  print_json_field_value(Sts_MetaDeclarationValue, name);
  print_json_field_value(Sts_MetaDeclarationValue, event);
  print_json_struct_return;
}

dec_print(Sts_MetaZoneExtendDeclaration) {
  print_struct_init;
  print_field_value(Sts_MetaDeclarationValue, zoneName);
  print_field_value(bool, isExport);
  print_struct_return;
}
dec_print_json(Sts_MetaZoneExtendDeclaration) {
  print_json_struct_init;
  print_json_field_value(Sts_MetaDeclarationValue, zoneName);
  print_json_field_value(bool, isExport);
  print_json_struct_return;
}

dec_print(Sts_MetaSuperRegexDeclarationElement) {
  print_struct_init;
  print_field_value(Sts_MetaDeclarationValue, token);
  print_field_value(Sts_MetaDeclarationValue, name);
  print_field_value(bool, isOptional);
  print_field_value(bool, isNonName);
  print_struct_return;
}
dec_print_json(Sts_MetaSuperRegexDeclarationElement) {
  print_json_struct_init;
  print_json_field_value(Sts_MetaDeclarationValue, token);
  print_json_field_value(Sts_MetaDeclarationValue, name);
  print_json_field_value(bool, isOptional);
  print_json_field_value(bool, isNonName);
  print_json_struct_return;
}

dec_print(Sts_MetaSuperRegexDeclarationElements) {
  print_glist(Sts_MetaSuperRegexDeclarationElements, Sts_MetaSuperRegexDeclarationElement, , &);
}
dec_print_json(Sts_MetaSuperRegexDeclarationElements) {
  print_json_glist(Sts_MetaSuperRegexDeclarationElements, Sts_MetaSuperRegexDeclarationElement, , &);
}

dec_print(Sts_MetaSuperRegexDeclaration) {
  print_struct_init;
  print_field_value(Sts_MetaSuperRegexDeclarationElements, elements);
  print_field_value(bool, isGhost);
  print_struct_return;
}
dec_print_json(Sts_MetaSuperRegexDeclaration) {
  print_json_struct_init;
  print_json_field_value(Sts_MetaSuperRegexDeclarationElements, elements);
  print_json_field_value(bool, isGhost);
  print_json_struct_return;
}

dec_print(Sts_MetaDeclarationType) {
  print_enum(Sts_MetaDeclarationType_PARAM);
  print_enum(Sts_MetaDeclarationType_VARIABLE);
  print_enum(Sts_MetaDeclarationType_EVENT);
  print_enum(Sts_MetaDeclarationType_ZONE_EXTEND);
  print_enum(Sts_MetaDeclarationType_SUPER_REGEX);
  print_enum_end;
}
dec_print_json(Sts_MetaDeclarationType) {
  print_json_enum(Sts_MetaDeclarationType_PARAM);
  print_json_enum(Sts_MetaDeclarationType_VARIABLE);
  print_json_enum(Sts_MetaDeclarationType_EVENT);
  print_json_enum(Sts_MetaDeclarationType_ZONE_EXTEND);
  print_json_enum(Sts_MetaDeclarationType_SUPER_REGEX);
  print_json_enum_end;
}

dec_print(Sts_MetaDeclaration) {
  print_struct_init;
  print_field_value(Sts_MetaDeclarationType, type);
  if (input->type == Sts_MetaDeclarationType_PARAM) {
    print_field_value(Sts_MetaParamDeclaration, value.param);
  } 
  if (input->type == Sts_MetaDeclarationType_VARIABLE) {
    print_field_value(Sts_MetaVariableDeclaration, value.variable);
  } 
  if (input->type == Sts_MetaDeclarationType_EVENT) {
    print_field_value(Sts_MetaEventDeclaration, value.event);
  } 
  if (input->type == Sts_MetaDeclarationType_ZONE_EXTEND) {
    print_field_value(Sts_MetaZoneExtendDeclaration, value.zoneExtend);
  } 
  if (input->type == Sts_MetaDeclarationType_SUPER_REGEX) {
    print_field_value(Sts_MetaSuperRegexDeclaration, value.superRegex);
  } 
  print_struct_return;
}
dec_print_json(Sts_MetaDeclaration) {
  print_json_struct_init;
  print_json_field_value(Sts_MetaDeclarationType, type);
  if (input->type == Sts_MetaDeclarationType_PARAM) {
    print_json_field_value(Sts_MetaParamDeclaration, value.param);
  } 
  if (input->type == Sts_MetaDeclarationType_VARIABLE) {
    print_json_field_value(Sts_MetaVariableDeclaration, value.variable);
  } 
  if (input->type == Sts_MetaDeclarationType_EVENT) {
    print_json_field_value(Sts_MetaEventDeclaration, value.event);
  } 
  if (input->type == Sts_MetaDeclarationType_ZONE_EXTEND) {
    print_json_field_value(Sts_MetaZoneExtendDeclaration, value.zoneExtend);
  } 
  if (input->type == Sts_MetaDeclarationType_SUPER_REGEX) {
    print_json_field_value(Sts_MetaSuperRegexDeclaration, value.superRegex);
  } 
  print_json_struct_return;
}

dec_print(Sts_MetaDeclarationList) {
  print_glist(Sts_MetaDeclarationList, Sts_MetaDeclaration, *,);
}
dec_print_json(Sts_MetaDeclarationList) {
  print_json_glist(Sts_MetaDeclarationList, Sts_MetaDeclaration, *,);
}

dec_print(Sts_MetaDeclarationValuesWeakList) {
  print_glist(Sts_MetaDeclarationWeakList, Sts_MetaDeclarationValue, *,);
}
dec_print_json(Sts_MetaDeclarationValuesWeakList) {
  print_json_glist(Sts_MetaDeclarationWeakList, Sts_MetaDeclarationValue, *,);
}

dec_print(Sts_MetaDeclarationValuesLinks) {
  print_gmap(Sts_MetaDeclarationValuesLinks, Sts_MetaDeclarationValuesWeakList, , &);
}
dec_print_json(Sts_MetaDeclarationValuesLinks) {
  print_json_gmap(Sts_MetaDeclarationValuesLinks, Sts_MetaDeclarationValuesWeakList, , &);
}

dec_print(Sts_MetaDeclarationsBlockType) {
  print_enum(Sts_MetaDeclarationsBlockType_TOKEN);
  print_enum(Sts_MetaDeclarationsBlockType_ZONE);
  print_enum(Sts_MetaDeclarationsBlockType_GROUP);
  print_enum(Sts_MetaDeclarationsBlockType_SUPER_TOKEN);
  print_enum_end;
}
dec_print_json(Sts_MetaDeclarationsBlockType) {
  print_json_enum(Sts_MetaDeclarationsBlockType_TOKEN);
  print_json_enum(Sts_MetaDeclarationsBlockType_ZONE);
  print_json_enum(Sts_MetaDeclarationsBlockType_GROUP);
  print_json_enum(Sts_MetaDeclarationsBlockType_SUPER_TOKEN);
  print_json_enum_end;
}

dec_print(Sts_MetaDeclarationsBlock) {
  print_struct_init;
  print_field_value(String, name);
  print_field_value(Sts_MetaDeclarationsBlockType, type);
  print_field_value(Sts_MetaDeclarationList, declarations);
  print_field_value(StringList, linkNames);
  print_field_value(Sts_MetaDeclarationValuesLinks, links);
  print_struct_return;
}
dec_print_json(Sts_MetaDeclarationsBlock) {
  print_json_struct_init;
  print_json_field_value(Sts_MetaDeclarationsBlockType, type);
  print_json_field_value(Sts_MetaDeclarationList, declarations);
  print_json_field_value(StringList, linkNames);
  print_json_field_value(Sts_MetaDeclarationValuesLinks, links);
  print_json_struct_return;
}

dec_print(Sts_MetaDeclarationsBlocks) {
  print_glist(Sts_MetaDeclarationsBlocks, Sts_MetaDeclarationsBlock,,&);
}
dec_print_json(Sts_MetaDeclarationsBlocks) {
  print_json_glist(Sts_MetaDeclarationsBlocks, Sts_MetaDeclarationsBlock,,&);
}

dec_print(Sts_MetaFile) {
  print_struct_init;
  print_field_value(Sts_MetaDeclarationsBlocks, decBlocks);
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
  print_json_field_value(Sts_MetaDeclarationsBlocks, decBlocks);
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
