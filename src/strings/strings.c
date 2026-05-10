#include "strings.h"

#include <string.h>
#include <stdlib.h>

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
  strlcpy(newBuffer, buffer, size+1);
  return (String) {
    .buffer = newBuffer,
    .size = size,
    .bufferOnHeap = true
  };
}
String String_copy(BORROW(ViewString) const vstring) {
  return String_by(vstring->buffer);
}

ViewString ViewString_new(WEAK(char) buffer, size_t size) {
  return (ViewString) {
    .buffer = buffer,
    .size = size
  };
}
ViewString ViewString_of(WEAK(char) buffer) {
  return (ViewString) {
    .buffer = buffer,
    .size = getSize(buffer)
  };
}
ViewString ViewString_by(BORROW(String) string) {
  return (ViewString) {
    .buffer = string->buffer,
    .size = getSize(string->buffer)
  };
}

void String_free(String* string) {
  if (string->bufferOnHeap) {
    A_free(string->buffer);
  }
  string->buffer = null;
  string->bufferOnHeap = false;
}
void ViewString_free(ViewString* vstring) {
  vstring->buffer = null;
}

bool ViewStrings_equals(BORROW(ViewString) vstring1, BORROW(ViewString) vstring2) {
  if (vstring1->size != vstring2->size) return false;
  WEAK(char) buffer1 = vstring1->buffer;
  WEAK(char) buffer2 = vstring2->buffer;
  for (size_t i = 0; i < vstring1->size; i++) {
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


void Strings_strlcpy(char* dest, const char* src, const size_t bufferSize) {
  strlcpy(dest, src, bufferSize);
}
int Strings_atoi(const char* string) {
  return atoi(string);
}
