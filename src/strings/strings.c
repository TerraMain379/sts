#include "strings.h"

#include <string.h>
#include <stdlib.h>

#include "allocator.h"

String String_new(OWNER(char*) buffer, size_t size, bool bufferOnHeap) {
  return (String) {
    .buffer = buffer,
    .size = size,
    .bufferOnHeap = bufferOnHeap
  };
}
String String_of(OWNER(char*) buffer) {
  return (String) {
    .buffer = buffer,
    .size = Strings_getLen(buffer),
    .bufferOnHeap = true
  };
}
String String_by(BORROW(char*) buffer) {
  size_t size = Strings_getLen(buffer);
  if (size == 0) return (String) {
    .buffer = 0,
    .size = -1,
    .bufferOnHeap = false,
  };
  OWNER(char*) newBuffer = A_loc(sizeof(char)*(size+1));
  strlcpy(newBuffer, buffer, size+1);
  return (String) {
    .buffer = newBuffer,
    .size = size,
    .bufferOnHeap = true
  };
}
String String_const(OWNER(char*) buffer) {
  return (String) {
    .buffer = buffer,
    .size = Strings_getLen(buffer),
    .bufferOnHeap = false
  };
}
String String_copy(BORROW(ViewString) vstring) {
  return String_by(vstring.buffer);
}
String String_copyString(BORROW(String) string) {
  return String_by(string.buffer);
}

ViewString ViewString_new(WEAK(char*) buffer, size_t size) {
  return (ViewString) {
    .buffer = buffer,
    .size = size
  };
}
ViewString ViewString_of(WEAK(char*) buffer) {
  return (ViewString) {
    .buffer = buffer,
    .size = Strings_getLen(buffer)
  };
}
ViewString ViewString_by(BORROW(String) string) {
  return (ViewString) {
    .buffer = string.buffer,
    .size = Strings_getLen(string.buffer)
  };
}

void String_free(String* string) {
  if (string == null) return;
  if (string->bufferOnHeap) {
    A_free(string->buffer);
  }
  string->buffer = null;
  string->bufferOnHeap = false;
}
void ViewString_free(ViewString* vstring) {
  if (vstring == null) return;
  vstring->buffer = null;
}

bool ViewStrings_equals(BORROW(ViewString) vstring1, BORROW(ViewString) vstring2) {
  if (vstring1.size != vstring2.size) return false;
  WEAK(char*) buffer1 = vstring1.buffer;
  WEAK(char*) buffer2 = vstring2.buffer;
  for (size_t i = 0; i < vstring1.size; i++) {
    if (buffer1[i] != buffer2[i]) {
      return false;
    }
  }
  return true;
}
bool Strings_equals(BORROW(String) string1, BORROW(String) string2) {
  return ViewStrings_equals(
    ViewString_by(string1),
    ViewString_by(string2)
  );
}
size_t Strings_getLen(BORROW(char*) str) {
  if (!str) return 0;
  return strlen(str);
}


void_errno Strings_strcpy(MUT_BORROW(char*) dest, size_t destSize, BORROW(char*) src, const size_t srcSize) {
  if (dest == null || src == null) {
    errno = 1; return;
  }
  if (destSize == 0 || srcSize == 0) {
    if (destSize > 0) dest[0] = '\0';
    errno = 0; return;
  }
  size_t size = destSize - 1 < srcSize
    ? destSize - 1
    : srcSize;

  char* res = memccpy(dest, src, '\0', size);

  if (res == null) {
    dest[size] = '\0';
  }
  errno = 0; return;
}
int Strings_atoi(BORROW(char*) string) {
  return atoi(string);
}
type_errno(long) Strings_strtol(BORROW(char*) string, int basis, char** retEndPtr) {
  errno = 0;
  return strtol(string, retEndPtr, basis);
}
