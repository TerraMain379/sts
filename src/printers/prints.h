#pragma once

#include "utils.h"
#include "strings.h"

extern size_t print_maxDepth;

#define dec_print(type) String type##_print(const type* input, size_t depth)
#define dec_print_json(type) String type##_print_json(const type* input, size_t depth)
#define dec_prints(type) \
  dec_print(type); \
  dec_print_json(type); \


String char_print(const char* input, size_t depth);
String bool_print(const bool* input, size_t depth);
String _Bool_print(const bool* input, size_t depth);
String int_print(const int* input, size_t depth);
String long_print(const long* input, size_t depth);
String float_print(const float* input, size_t depth);
String double_print(const double* input, size_t depth);
String size_t_print(const size_t* input, size_t depth);
dec_print(String);

String char_print_json(const char* input, size_t depth);
String bool_print_json(const bool* input, size_t depth);
String _Bool_print_json(const bool* input, size_t depth);
String int_print_json(const int* input, size_t depth);
String long_print_json(const long* input, size_t depth);
String float_print_json(const float* input, size_t depth);
String double_print_json(const double* input, size_t depth);
String size_t_print_json(const size_t* input, size_t depth);
dec_print_json(String);

