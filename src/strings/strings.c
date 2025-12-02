#include "strings.h"

#include <string.h>

#include "allocator.h"

inline String String_new(const char* const buffer, const size_t length, const bool bufferOnHeap) {
  return (String) {
    .buffer = buffer,
    .length = length,
    .bufferOnHeap = bufferOnHeap
  };
}
String String_const(const char* const str) {
  return (String) {
    .buffer = str,
    .length = Strings_getLen(str),
    .bufferOnHeap = false
  };
}
String String_of(const char* const str) {
  return (String) {
    .buffer = str,
    .length = Strings_getLen(str),
    .bufferOnHeap = true
  };
}
String String_by(char* str, size_t length) {
  char* buffer = A_loc((length + 1) * sizeof(char));
  strncpy(buffer, str, length);
  buffer[length] = '\0';
  return String_new(buffer, length, true);
}
String String_copy(const String* string) {
  size_t length = string->length;
  char* buffer = A_loc((length + 1) * sizeof(char));
  strncpy(buffer, string->buffer, length);
  buffer[length] = '\0';
  return String_new(buffer, length, true);
}
void String_free(String* string) {
  if (string->bufferOnHeap) A_free(string->buffer);
  string->buffer = 0;
  string->length = -1;
  string->bufferOnHeap = false;
}

bool Strings_equals(const String string1, const String string2) {
  if (string1.length != string2.length) return false;
  if (string1.length == 0) return true;
  char* ch1 = string1.buffer;
  char* ch2 = string2.buffer;
  size_t length = string1.length;
  for (size_t i = 0; i < length; i++) {
    if (*ch1 != *ch2) return false;
    ch1++;
    ch2++;
  }
  return true;
}
size_t Strings_getLen(const char* str) {
  for (int i = 0; ; i++) {
    if (*str == '\0') return i;
    str++;
  }
}

inline bool Chars_isLetter(char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}
inline bool Chars_isVoid(char c) {
  return c == ' ' || c == '\r' || c == '\n' || c == '\t';
}
