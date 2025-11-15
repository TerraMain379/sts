#pragma once

#include "utils.h"

typedef struct {
  char* buffer;
  size_t length;
  bool bufferOnHeap;
} String;

String String_new(char* buffer, size_t length, bool bufferOnHeap);
String String_const(const char* str); // heap = false
String String_of(char* str); // heap = true
String String_by(char* str, size_t length); // heap = true
String String_copy(const String* string); // heap = true
void String_free(String* string);

bool Strings_equals(const String string1, const String string2);
size_t Strings_getLen(const char* str);

inline bool Chars_isLetter(char c);
inline bool Chars_isVoid(char c);
