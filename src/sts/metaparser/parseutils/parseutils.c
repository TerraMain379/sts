#include "modules/utils.h"

#include "allocator.h"


String readName(Iter* iter) {
  char* buffer = A_loc(16);
  size_t bufferSize = 16;
  size_t nameSize = 0;

  Iter_foreachChars(char c, iter) {
    if (!Chars_isLetter(c)) break;
    if (bufferSize == nameSize) {
      bufferSize *= 2;
      buffer = A_reloc(buffer, bufferSize);
    }
    bufferSize[nameSize] = c;
    nameSize++;
  }
  buffer[nameSize] = '\0';
  nameSize++;
  buffer = A_reloc(buffer, nameSize);
  return String_by(buffer, nameSize);
}
void skipVoid(Iter* iter, bool strict) {
  char c;
  if (strict) {
    c = Iter_currChar(iter)
    if (!Chars_isVoid(c)) return;
  }
  Iter_foreachChars(c, iter) {
    if (!Chars_isVoid(c)) return;
  }
}
void readChar(Context* ctx, char c) {
  if (Iter_readChar(ctx->iter) != c) {
    // TODO: ERROR 
  }
}
