#include "strings.h"

#include <string.h>

#include "allocator.h"

size_t getSize(BORROW(char) buffer) {
  return strlen(buffer);
}

String String_new(OWNER(char) buffer, size_t size, bool bufferOnHeap) {
  return (String) {
    .buffer = buffer,
    .size = size,
    .bufferOnHeap = bufferOnHeap
  };
}
String String_of(OWNER(char) buffer) {
  return (String) {
    .buffer = buffer,
    .size = getSize(buffer),
    .bufferOnHeap = true
  };
}
String String_by(BORROW(char) buffer) {
  size_t size = getSize(buffer);
  OWNER(char) newBuffer = A_loc(sizeof(char)*(size+1));
  strcpy(newBuffer, buffer);
  return (String) {
    .buffer = newBuffer,
    .size = size,
    .bufferOnHeap = true
  };
}

ViewString ViewString_new(WAKE(char) buffer, size_t size) {
  return (ViewString) {
    .buffer = buffer,
    .size = size
  };
}
ViewString ViewString_of(WAKE(char) buffer) {
  return (ViewString) {
    .buffer = buffer,
    .size = getSize(buffer)
  };
}
ViewString ViewString_by(BORROW(String) string) {
  return (ViewString) {
    .buffer = string->buffer,
    .size = getSize(buffer)
  };
}

void String_free(BORROW(String) string) {
  if (string->bufferOnHeap) {
    A_free(string->buffer);
  }
  string->buffer = 0;
  string->bufferOnHeap = false;
}
void ViewString_free(BORROW(ViewString) vstring) {
  vstring->buffer = 0;
}

bool ViewStrings_equals(BORROW(ViewString) const vstring1, BORROW(ViewString) const vstring2) {
  if (vstring1->size != vstring2->size) return false;
  WAKE(char) buffer1 = vstring1->buffer;
  WAKE(char) buffer2 = vstring2->buffer;
  for (size_t i = 0; i < vstring->size; i++) {
    if (buffer1[i] != buffer2[i]) {
      return false;
    }
  }
  return true;
}
bool Strings_equals(BORROW(String) const string1, BORROW(String) const string2) {
  return ViewStrings_equals(
    (ViewString*) string1,
    (ViewString*) string2
  );
}

OWNER(String) Strings_copy(BORROW(ViewString) const vstring) {
  return String_by(vstring->buffer);
}

inline bool Chars_isLetter(const char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}
inline bool Chars_isVoid(const char c) {
  return (c == ' ') || (c == '\t') || (c == '\n') || (c == '\r');
}
