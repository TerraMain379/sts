#pragma once

#include "utils.h"

typedef struct ViewString {
  WAKE(char) buffer;
  size_t size;
} ViewString;

typedef struct String /* extends ViewString */ {
  OWNER(char) buffer;
  size_t size;
  bool bufferOnHeap;
} String;

String String_new(OWNER(char) buffer, size_t size, bool bufferOnHeap);
String String_of(OWNER(char) buffer);
String String_by(BORROW(char) buffer);

ViewString ViewString_new(WAKE(char) buffer, size_t size);
ViewString ViewString_of(WAKE(char) buffer);
ViewString ViewString_by(BORROW(String) string);

void String_free(BORROW(String) string);
void ViewString_free(BORROW(ViewString) vstring);

bool ViewStrings_equals(BORROW(ViewString) vstring1, BORROW(ViewString) vstring2);
bool Strings_equals(BORROW(String) string1, BORROW(String) string2);

OWNER(String) Strings_copy(BORROW(ViewString) vstring);

inline bool Chars_isLetter(const char c);
inline bool Chars_isVoid(const char c);
