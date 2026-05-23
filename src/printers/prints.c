#include "prints.h"

#include "allocator.h"

String char_print(const char* input, size_t depth) {
  char chs[2] = {*input, '\0'};
  return String_by(chs);
}
String bool_print(const bool* input, size_t depth) {
  if (*input) return String_by("true");
  else return String_by("false");
}
String _Bool_print(const bool* input, size_t depth) {
  if (*input) return String_by("true");
  else return String_by("false");
}
String int_print(const int* input, size_t depth) {
  int value = *input;
  char* buffer = A_xloc(32);
  snprintf(buffer, 32, "%i", value);
  return String_of(buffer);
}
String long_print(const long* input, size_t depth) {
  long value = *input;
  char* buffer = A_xloc(32);
  snprintf(buffer, 32, "%li", value);
  return String_of(buffer);
}
String float_print(const float* input, size_t depth) {
  float value = *input;
  char* buffer = A_xloc(32);
  snprintf(buffer, 32, "%f", value);
  return String_of(buffer);
}
String double_print(const double* input, size_t depth) {
  double value = *input;
  char* buffer = A_xloc(32);
  snprintf(buffer, 32, "%lf", value);
  return String_of(buffer);
}
String size_t_print(const size_t* input, size_t depth) {
  size_t value = *input;
  char* buffer = A_xloc(32);
  snprintf(buffer, 32, "%zu", value);
  return String_of(buffer);
}
dec_print(String) {
  return ViewStrings_toJson(* ((ViewString*) input), true);
}

String char_print_json(const char* input, size_t depth) {
  char chs[2] = {*input, '\0'};
  return String_by(chs);
}
String bool_print_json(const bool* input, size_t depth) {
  if (*input) return String_by("true");
  else return String_by("false");
}
String _Bool_print_json(const bool* input, size_t depth) {
  if (*input) return String_by("true");
  else return String_by("false");
}
String int_print_json(const int* input, size_t depth) {
  int value = *input;
  char* buffer = A_xloc(32);
  snprintf(buffer, 32, "%i", value);
  return String_of(buffer);
}
String long_print_json(const long* input, size_t depth) {
  long value = *input;
  char* buffer = A_xloc(32);
  snprintf(buffer, 32, "%li", value);
  return String_of(buffer);
}
String float_print_json(const float* input, size_t depth) {
  float value = *input;
  char* buffer = A_xloc(32);
  snprintf(buffer, 32, "%f", value);
  return String_of(buffer);
}
String double_print_json(const double* input, size_t depth) {
  double value = *input;
  char* buffer = A_xloc(32);
  snprintf(buffer, 32, "%lf", value);
  return String_of(buffer);
}
String size_t_print_json(const size_t* input, size_t depth) {
  size_t value = *input;
  char* buffer = A_xloc(32);
  snprintf(buffer, 32, "%zu", value);
  return String_of(buffer);
}
dec_print_json(String) {
  return ViewStrings_toJson(* ((ViewString*) input), true);
}

