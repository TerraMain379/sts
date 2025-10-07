#include "strings.h"

#include <string.h>

#include "allocator.h"

inline String String_new(char* buffer, size_t length, bool bufferOnHeap) {
  return (String) {
    .buffer = buffer,
    .length = length,
    .bufferOnHeap = bufferOnHeap
  };
}
String String_const(const char* str) {
  return (String) {
    .buffer = str,
    .length = Strings_getLen(str),
    .bufferOnHeap = false
  };
}
String String_of(char* str) {
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


/*
bool String_equals(String string1, String string2) {
  if (string1.length != string2.length) return false;
  
  size_t length = string1.length;
  
  uintptr_t ptr1 = string1.buffer;
  uintptr_t ptr2 = string2.buffer;
  size_t i = 0;
  if (length >= 8 && ptr1 % 4 == ptr2 % 4) {
    while (ptr1 % 4 != 0) {
      char c1 = *(char*) ptr1;
      char c2 = *(char*) ptr2;
      if (c1 != c2) return false;
      ptr1++;
      ptr2++;
      i++;
    }
    while (i+3 < length) {
      int v1 = *(int*) ptr1;
      int v2 = *(int*) ptr2;
      if (v1 != v2) {
        return false;
      }
      ptr1+=4;
      ptr2+=4;
      i+=4;
    }
    while (i < length) {
      char c1 = *(char*) ptr1;
      char c2 = *(char*) ptr2;
      if (c1 != c2) return false;
      ptr1++;
      ptr2++;
      i++;
    }
  }
  else if (length == 0) return true;
  else if (length == 1) {
    return string1.buffer[0] == string2.buffer[1];
  }
  else {
    switch (length % 8) {
      case 0: while (i < length) {
        if ((char) *ptr1 != (char) *ptr2) return false; i++;
        case 1: if ((char) *ptr1 != (char) *ptr2) return false; i++;
        case 2: if ((char) *ptr1 != (char) *ptr2) return false; i++;
        case 3: if ((char) *ptr1 != (char) *ptr2) return false; i++;
        case 4: if ((char) *ptr1 != (char) *ptr2) return false; i++;
        case 5: if ((char) *ptr1 != (char) *ptr2) return false; i++;
        case 6: if ((char) *ptr1 != (char) *ptr2) return false; i++;
        case 7: if ((char) *ptr1 != (char) *ptr2) return false; i++;
      }
    }
    return true;
  }
}
*/
