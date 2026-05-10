#include "mpmodules/utils.h"

#include "allocator.h"
#include "stringbuilder.h"

String Utils_Iter_readName(Context* ctx) {
  Iter* iter = &ctx->iter;
  char* buffer = A_xloc(16);
  size_t bufferSize = 16;
  size_t nameSize = 0;

  char c; Iter_foreachChars(c, iter) {
    if (!Chars_isLetter(c) && !Chars_isDigit(c) && c != '_') break;
    if (bufferSize == nameSize) {
      bufferSize *= 2;
      buffer = A_reloc(buffer, bufferSize);
    }
    buffer[nameSize] = c;
    nameSize++;
  }
  buffer[nameSize] = '\0';
  bufferSize = nameSize+1;
  buffer = A_reloc(buffer, bufferSize);
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

bool Utils_Iter_readChar(Context* ctx, char c) {
  Iter* iter = &ctx->iter;
  char readChar = Iter_nextChar(iter);
  if (readChar == c) return true;
  Iter_unsafeBackChar(iter);
  return false;
}

void_stop Utils_Iter_skipChar(Context* ctx, char c) {
  Iter* iter = &ctx->iter;
  if (Iter_nextChar(iter) != c) {
    // Errors_metaparser_anotherTokenExpected(iter);
    // TODO: 
  }
}

String Utils_Iter_readString(Context* ctx) {
  Iter* iter = &ctx->iter;
  char* buffer = A_xloc(16);
  size_t bufferSize = 16;
  size_t nameSize = 0;

  char c; Iter_foreachChars(c, iter) {
    if (c == '"') {
      Iter_nextChar(iter);
      break;
    }
    else if (c == '\\') {
      char c1 = Iter_nextChar(iter);
      if (nameSize+1 >= bufferSize) {
        bufferSize *= 2;
        buffer = A_reloc(buffer, bufferSize);
      }
      buffer[nameSize] = '\\';
      nameSize++;
      buffer[nameSize] = c1;
      nameSize++;
    }
    else {
      if (nameSize == bufferSize) {
        bufferSize *= 2;
        buffer = A_reloc(buffer, bufferSize);
      }
      buffer[nameSize] = c;
      nameSize++;
    }
  }
  buffer[nameSize] = '\0';
  nameSize++;
  buffer = A_reloc(buffer, nameSize);
  return String_new(buffer, nameSize, true);
}

void Utils_Iter_readNumber_block(Context* ctx, StringBuilder* builder) {
  char c; Iter_foreachChars(c, &ctx->iter) {
    if (Chars_isDigit(c)) {
      StringBuilder_addChar(builder, c);
    }
    else break;
  }
}
double Utils_Iter_readNumber(Context* ctx) {
  char c = Iter_currChar(&ctx->iter);
  bool fraction;
  StringBuilder mainBuilder;
  StringBuilder_init(&mainBuilder);
  StringBuilder fracBuilder;
  StringBuilder_init(&fracBuilder);

  if (Chars_isDigit(c)) {
    Utils_Iter_readNumber_block(ctx, &mainBuilder);
  }
  else StringBuilder_addChar(&mainBuilder, '0');

  if (c == '.') {
    Iter_nextChar(&ctx->iter);
    Utils_Iter_readNumber_block(ctx, &fracBuilder);
  }
  else StringBuilder_addChar(&fracBuilder, '0');

  ViewString main = StringBuilder_get(&mainBuilder);
  ViewString frac = StringBuilder_get(&fracBuilder);
  double result = Strings_atoi(main.buffer);
  double fracResult = Strings_atoi(frac.buffer);
  for (size_t i = 0; i < frac.size; i++) {
    fracResult/=10;
  }
  StringBuilder_free(&mainBuilder);
  StringBuilder_free(&fracBuilder);
  return result + fracResult;
}

