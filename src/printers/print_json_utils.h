#pragma once

#include "strings.h"
#include "errors.h"
#include "stringbuilder.h"

#define print_json_struct_init \
  StringBuilder builder; \
  StringBuilder_init(&builder); \
  StringBuilder_addChar(&builder, '{'); \
  ViewString paramString; \
  String value; \
  bool first = true; \

// valuePrefix = ""|"&"
#define _print_json_field(type, param, valuePrefix) \
  if (!first) { \
    StringBuilder_addChar(&builder, ','); \
  } \
  StringBuilder_addChar(&builder, '"'); \
  StringBuilder_addCharBuffer(&builder, #param); \
  StringBuilder_addChar(&builder, '"'); \
  StringBuilder_addChar(&builder, ':'); \
  value = type##_print_json(valuePrefix input->param, depth+1); \
  StringBuilder_addString(&builder, ViewString_by(value)); \
  String_free(&value); \
  first = false; \

#define print_json_field_value(type, param) _print_json_field(type, param, &)
// #define print_json_field_ptr(type, param) _print_json_field(type, param,)
#define print_json_field_ptr(type, param) \
  if (input->param) { \
    _print_json_field(type, param,); \
  } \
  else { \
    if (!first) { \
      StringBuilder_addChar(&builder, ','); \
    } \
    StringBuilder_addChar(&builder, '"'); \
    StringBuilder_addCharBuffer(&builder, #param); \
    StringBuilder_addChar(&builder, '"'); \
    StringBuilder_addChar(&builder, ':'); \
    StringBuilder_addCharBuffer(&builder, "null"); \
  } \

#define print_json_struct_return \
  StringBuilder_addChar(&builder, '}'); \
  return StringBuilder_take(&builder); \

#define print_json_enum_init  

#define print_json_enum(value) \
  if (*input == (value)) return ViewStrings_toJson(ViewString_of(#value), true); \

#define print_json_enum_r(value, name) \
  if (*input == (value)) return ViewStrings_toJson(ViewString_of(#name), true); \

#define print_json_enum_end \
  Errors_internal_unexpectedEnumType(ViewString_of("Print JSON Module")); \
  non_call_return (String) {0};

#define print_json_glist(type, etype, type_postfix, value_prefix) \
  StringBuilder builder; \
  StringBuilder_init(&builder); \
  StringBuilder_addChar(&builder, '['); \
  ViewString paramString; \
  String value; \
  bool first = true; \
  for (size_t i = 0; i < input->size; i++) { \
    if (!first) { \
      StringBuilder_addChar(&builder, ','); \
    } \
    etype type_postfix element = (etype type_postfix) input->array[i]; \
    String value = etype##_print_json(value_prefix element, depth+1); \
    StringBuilder_addString(&builder, ViewString_by(value)); \
    String_free(&value); \
    first = false; \
  } \
  StringBuilder_addChar(&builder, ']'); \
  return StringBuilder_take(&builder); \
  
#define print_json_gmap(type, etype, type_postfix, value_prefix) \
  print_json_struct_init; \
  type##_element* element = input->first; \
  while (element != null) { \
    const etype type_postfix elementValue = element->value; \
    String value = etype##_print_json(value_prefix elementValue, depth+1); \
    if (!first) StringBuilder_addChar(&builder, ','); \
    StringBuilder_addChar(&builder, '"'); \
    StringBuilder_addString(&builder, ViewString_by(element->key)); \
    StringBuilder_addChar(&builder, '"'); \
    StringBuilder_addChar(&builder, ':'); \
    StringBuilder_addString(&builder, ViewString_by(value)); \
    String_free(&value); \
    element = element->next; \
    first = false; \
  } \
  print_json_struct_return; \


