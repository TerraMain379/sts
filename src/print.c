#include "print.h"

#include "errors.h"
#include "allocator.h"
#include "metablocks.h"
#include "stringbuilder.h"

#define _print_init_struct(enterPrefix) \
  StringBuilder tabsB; \
  StringBuilder_init(&tabsB); \
  StringBuilder_setCapacity(&tabsB, depth*2+2); \
  for (size_t i = 0; i < depth; i++) { \
    StringBuilder_addChar(&tabsB, ' '); \
    StringBuilder_addChar(&tabsB, ' '); \
  } \
  ViewString tabs = StringBuilder_get(&tabsB); \
  StringBuilder builder; \
  StringBuilder_init(&builder); \
  ViewString enterPrefixVs = ViewString_of(enterPrefix); \
  StringBuilder_addString(&builder, &enterPrefixVs); \
  ViewString paramString; \
  String value; \

#define print_init_struct _print_init_struct(" ")
  
// valuePrefix = ""|"&"
#define _print_field(type, param, valuePrefix) \
  StringBuilder_addChar(&builder, '\n'); \
  StringBuilder_addString(&builder, &tabs); \
  paramString = ViewString_of(#param); \
  StringBuilder_addString(&builder, (ViewString*) &paramString); \
  StringBuilder_addChar(&builder, ':'); \
  StringBuilder_addChar(&builder, ' '); \
  value = type##_print(valuePrefix input->param, depth+1); \
  StringBuilder_addString(&builder, (ViewString*) &value); \
  String_free(&value); \

#define print_field_value(type, param) _print_field(type, param, &)
#define print_field_ptr(type, param) _print_field(type, param,)

#define print_return \
  ViewString_free(&tabs); \
  StringBuilder_free(&tabsB); \
  return StringBuilder_take(&builder); \

#define print_enum(value) \
  if (*input == value) return String_by(#value);

#define print_enum_end \
  Errors_internal_unexpectedEnumType(ViewString_of("Print Module")); \
  non_call_return (String) {0};

#define _print_glist(type, etype, type_postfix, value_prefix) \
  _print_init_struct(" "); \
  ViewString arrayPrefix = ViewString_of("- "); \
  for (size_t i = 0; i < input->size; i++) { \
    etype type_postfix element = (etype type_postfix) input->array[i]; \
    String value = etype##_print(value_prefix element, depth+1); \
    StringBuilder_addChar(&builder, '\n'); \
    StringBuilder_addString(&builder, &tabs); \
    StringBuilder_addString(&builder, &arrayPrefix); \
    StringBuilder_addString(&builder, (ViewString*) &value); \
    String_free(&value); \
  } \
  print_return; \
  

#define print_glist_ptr(type, etype) _print_glist(type, etype,)
#define print_glist_value(type, etype) _print_glist(type, etype, &)

#define _print_gmap(type, etype, type_postfix, value_prefix) \
  _print_init_struct(" "); \
  type##_element* element = input->first; \
  while (element != null) { \
    etype type_postfix elementValue = element->value; \
    String value = etype##_print(value_prefix elementValue, depth+1); \
    StringBuilder_addChar(&builder, '\n'); \
    StringBuilder_addString(&builder, &tabs); \
    StringBuilder_addChar(&builder, '"'); \
    StringBuilder_addString(&builder, (ViewString*) &element->key); \
    StringBuilder_addChar(&builder, '"'); \
    StringBuilder_addChar(&builder, ':'); \
    StringBuilder_addChar(&builder, ' '); \
    StringBuilder_addString(&builder, (ViewString*) &value); \
    String_free(&value); \
    element = element->next; \
  } \
  print_return; \


#define print_gmap_ptr(type, etype) _print_gmap(type, etype,)
#define print_gmap_value(type, etype) _print_gmap(type, etype, &)


String bool_print(bool* input, size_t depth) {
  if (*input) return String_by("true");
  else return String_by("false");
}
String _Bool_print(bool* input, size_t depth) {
  if (*input) return String_by("true");
  else return String_by("false");
}
String double_print(double* input, size_t depth) {
  double value = *input;
  char* buffer = A_xloc(32);
  snprintf(buffer, 32, "%g", value);
  return String_of(buffer);
}


dec_print(String) {
  StringBuilder builder;
  StringBuilder_init(&builder);
  StringBuilder_setCapacity(&builder, input->size+3);
  StringBuilder_addChar(&builder, '"');
  StringBuilder_addString(&builder, (ViewString*) input);
  StringBuilder_addChar(&builder, '"');
  return StringBuilder_take(&builder);
}
dec_print(Sts_MetaRegex) {
  print_init_struct;
  print_field_value(String, regex);
  print_return;
}

dec_print(Sts_MetaDeclarationsBlock) {
  print_init_struct;
  print_field_value(Sts_MetaDeclarationsBlockType, type);
  print_field_value(Sts_MetaDeclarationList, declarations);
  print_field_value(StringList, linkNames);
  print_field_value(Sts_MetaDeclarationValuesLinks, links);
  print_return;
}
dec_print(Sts_MetaDeclaration) {
  print_init_struct;
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
  print_return;
}
dec_print(Sts_MetaParamDeclaration) {
  print_init_struct;
  print_field_value(Sts_MetaDeclarationValue, name);
  print_field_value(Sts_MetaDeclarationValueList, values);
  print_return;
}
dec_print(Sts_MetaVariableDeclaration) {
  print_init_struct;
  print_field_value(Sts_MetaDeclarationValue, name);
  print_field_value(Sts_MetaDeclarationValue, value);
  print_field_value(Sts_MetaDeclarationTyping, typing);
  print_return;
}
dec_print(Sts_MetaEventDeclaration) {
  print_init_struct;
  print_field_value(Sts_MetaDeclarationValue, name);
  print_field_value(Sts_MetaDeclarationValue, event);
  print_return;
}
dec_print(Sts_MetaZoneExtendDeclaration) {
  print_init_struct;
  print_field_value(Sts_MetaDeclarationValue, zoneName);
  print_field_value(bool, isExport);
  print_return;
}
dec_print(Sts_MetaSuperRegexDeclarationElement) {
  print_init_struct;
  print_field_value(Sts_MetaDeclarationValue, token);
  print_field_value(Sts_MetaDeclarationValue, name);
  print_field_value(bool, isOptional);
  print_field_value(bool, isNonName);
  print_return;
}
dec_print(Sts_MetaSuperRegexDeclaration) {
  print_init_struct;
  print_field_value(Sts_MetaSuperRegexDeclarationElements, elements);
  print_field_value(bool, isGhost);
  print_return;
}
dec_print(Sts_MetaDeclarationsBlockType) {
  print_enum(Sts_MetaDeclarationsBlockType_TOKEN);
  print_enum(Sts_MetaDeclarationsBlockType_ZONE);
  print_enum(Sts_MetaDeclarationsBlockType_GROUP);
  print_enum(Sts_MetaDeclarationsBlockType_SUPER_TOKEN);
  print_enum_end;
}
dec_print(Sts_MetaDeclarationType) {
  print_enum(Sts_MetaDeclarationType_PARAM);
  print_enum(Sts_MetaDeclarationType_VARIABLE);
  print_enum(Sts_MetaDeclarationType_EVENT);
  print_enum(Sts_MetaDeclarationType_ZONE_EXTEND);
  print_enum(Sts_MetaDeclarationType_SUPER_REGEX);
  print_enum_end;
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
dec_print(Sts_MetaDeclarationValueType) {
  print_enum(Sts_MetaDeclarationValueType_NULL);
  print_enum(Sts_MetaDeclarationValueType_NAME);
  print_enum(Sts_MetaDeclarationValueType_STRING);
  print_enum(Sts_MetaDeclarationValueType_NUMBER);
  print_enum(Sts_MetaDeclarationValueType_EXPRESSION);
  print_enum(Sts_MetaDeclarationValueType_LINK);
  print_enum_end;
}
dec_print(Sts_MetaDeclarationValue) {
  print_init_struct;
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
  print_return;
}
dec_print(Sts_MetaDeclarationExpression) {
  print_init_struct;
  print_field_value(Sts_MetaDeclarationExpressionType, type);
  print_field_value(Sts_MetaDeclarationValue, value1);
  print_field_value(Sts_MetaDeclarationValue, value2);
  print_return;
}
dec_print(Sts_MetaDeclarationTyping) {
  return String_of("");
}
dec_print(StringList) {
  _print_glist(StringList, String, , &);
}
dec_print(Sts_MetaDeclarationValueList) {
  _print_glist(Sts_MetaDeclarationValueList, Sts_MetaDeclarationValue, , &);
}
dec_print(Sts_MetaDeclarationList) {
  _print_glist(Sts_MetaDeclarationList, Sts_MetaDeclaration, *,);
}
dec_print(Sts_MetaDeclarationValuesLinks) {
  _print_gmap(Sts_MetaDeclarationValuesLinks, Sts_MetaDeclarationValuesWeakList, , &);
}
dec_print(Sts_MetaDeclarationValuesWeakList) {
  _print_glist(Sts_MetaDeclarationWeakList, Sts_MetaDeclarationValue, *,);
}
dec_print(Sts_MetaSuperRegexDeclarationElements) {
  _print_glist(Sts_MetaSuperRegexDeclarationElements, Sts_MetaSuperRegexDeclarationElement, , &);
}
