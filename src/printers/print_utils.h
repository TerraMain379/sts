#pragma once

#include "strings.h"
#include "errors.h"
#include "stringbuilder.h"

#define print_struct_init \
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
  ViewString paramString; \
  String value; \

// valuePrefix = ""|"&"
#define _print_field(type, param, valuePrefix) \
  StringBuilder_addChar(&builder, '\n'); \
  StringBuilder_addString(&builder, tabs); \
  StringBuilder_addString(&builder, ViewString_of(#param)); \
  StringBuilder_addChar(&builder, ':'); \
  StringBuilder_addChar(&builder, ' '); \
  value = type##_print(valuePrefix input->param, depth+1); \
  StringBuilder_addString(&builder, ViewString_by(value)); \
  String_free(&value); \

#define print_field_value(type, param) _print_field(type, param, &)
#define print_field_ptr(type, param) \
  if (input->param) { \
    _print_field(type, param,); \
  } \
  else { \
    StringBuilder_addChar(&builder, '\n'); \
    StringBuilder_addString(&builder, tabs); \
    StringBuilder_addCharBuffer(&builder, #param); \
    StringBuilder_addCharBuffer(&builder, ": null"); \
  } \

#define print_struct_return \
  ViewString_free(&tabs); \
  StringBuilder_free(&tabsB); \
  return StringBuilder_take(&builder); \

#define print_enum_init  

#define print_enum(value) \
  if (*input == value) return String_by(#value);

#define print_enum_r(value, name) \
  if (*input == value) return String_by(#name);

#define print_enum_end \
  Errors_internal_unexpectedEnumType(ViewString_of("Print Module")); \
  non_call_return (String) {0};

#define print_glist(type, etype, type_postfix, value_prefix) \
  print_struct_init; \
  ViewString arrayPrefix = ViewString_of("- "); \
  for (size_t i = 0; i < input->size; i++) { \
    etype type_postfix element = (etype type_postfix) input->array[i]; \
    String value = etype##_print(value_prefix element, depth+1); \
    StringBuilder_addChar(&builder, '\n'); \
    StringBuilder_addString(&builder, tabs); \
    StringBuilder_addString(&builder, arrayPrefix); \
    StringBuilder_addString(&builder, ViewString_by(value)); \
    String_free(&value); \
  } \
  print_struct_return; \

#define print_gmap(type, etype, type_postfix, value_prefix) \
  print_struct_init; \
  type##_element* element = input->first; \
  while (element != null) { \
    const etype type_postfix elementValue = element->value; \
    String value = etype##_print(value_prefix elementValue, depth+1); \
    StringBuilder_addChar(&builder, '\n'); \
    StringBuilder_addString(&builder, tabs); \
    StringBuilder_addChar(&builder, '"'); \
    StringBuilder_addString(&builder, ViewString_by(element->key)); \
    StringBuilder_addChar(&builder, '"'); \
    StringBuilder_addChar(&builder, ':'); \
    StringBuilder_addChar(&builder, ' '); \
    StringBuilder_addString(&builder, ViewString_by(value)); \
    String_free(&value); \
    element = element->next; \
  } \
  print_struct_return; \

