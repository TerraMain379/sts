#pragma once

#include "utils.h"

typedef struct ViewString {
  WEAK(char) buffer;
  size_t size;
} ViewString;

typedef struct String /* extends ViewString */ {
  OWNER(char) buffer;
  size_t size;
  bool bufferOnHeap;
} String;

String String_new(OWNER(char) buffer, size_t size, bool bufferOnHeap);
String String_of(OWNER(char) buffer); // use buffer; bufferOnHeap = true
String String_by(BORROW(char) buffer); // copy buffer; bufferOnHeap = true
String String_copy(BORROW(ViewString) vstring); // bufferOnHeap = true

ViewString ViewString_new(WEAK(char) buffer, size_t size);
ViewString ViewString_of(WEAK(char) buffer);
ViewString ViewString_by(BORROW(String) string);

void String_free(String* string);
void ViewString_free(ViewString* vstring);

bool ViewStrings_equals(BORROW(ViewString) vstring1, BORROW(ViewString) vstring2);
bool Strings_equals(BORROW(String) string1, BORROW(String) string2);


static inline bool Chars_isLetter(const char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}
static inline bool Chars_isDigit(const char c) {
  return c >= '0' && c <= '9';
}
static inline bool Chars_isVoid(const char c) {
  return (c == ' ') || (c == '\t') || (c == '\n') || (c == '\r');
}


void Strings_strlcpy(char* dest, const char* src, const size_t bufferSize);
