#include "mpmodules/utils.h"

#include "allocator.h"

String Utils_Iter_readName(Context* ctx) {
  Iter* iter = &ctx->iter;
  char* buffer = A_loc(16);
  size_t bufferSize = 16;
  size_t nameSize = 0;

  char c; Iter_foreachChars(c, iter) {
    if (!Chars_isLetter(c) && !Chars_isDigit(c)) break;
    if (bufferSize == nameSize) {
      bufferSize *= 2;
      buffer = A_reloc(buffer, bufferSize);
    }
    buffer[nameSize] = c;
    nameSize++;
  }
  buffer[nameSize] = '\0';
  nameSize++;
  buffer = A_reloc(buffer, nameSize);
  return String_new(buffer, nameSize, true);
}
void Utils_Iter_skipVoid(Context* ctx, bool strict) {
  Iter* iter = &ctx->iter;
  char c;
  if (strict) {
    c = Iter_currChar(iter);
    if (!Chars_isVoid(c)) {
      // TODO: error
      errno = 1; return;
    }
  }
  Iter_foreachChars(c, iter) {
    if (!Chars_isVoid(c)) {
      errno = 0; return;
    }
  }
}
void Utils_Iter_readChar(Context* ctx, char c) {
  Iter* iter = &ctx->iter;
  if (Iter_nextChar(iter) != c) {
    // TODO: ERROR 
  }
}
String Utils_Iter_readString(Context* ctx) {
  return (String) {0};
  // TODO:
}
