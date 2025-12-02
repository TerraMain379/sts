#pragma once

#include "utils.h"

typedef struct {
  const char* const buffer;
  const size_t length;
  const bool bufferOnHeap;
} String;

String String_new(const char* const buffer, const size_t length, const bool bufferOnHeap);
String String_const(const char* const str); // heap = false
String String_of(const char* const str); // heap = true
String String_by(const char* const str, const size_t length); // heap = true
String String_copy(const String string); // heap = true
void String_free(String* string);

bool Strings_equals(const String string1, const String string2);
size_t Strings_getLen(const char* const str);

inline bool Chars_isLetter(const char c);
inline bool Chars_isVoid(const char c);
