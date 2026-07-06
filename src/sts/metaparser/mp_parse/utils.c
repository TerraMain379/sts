#include "mp_parse/utils.h"

#include "allocator.h"
#include "stringbuilder.h"
#include "errors.h"
#include "metaparser_errors.h"

type_errno(String) Utils_Iter_readName(Context* ctx) {
  Iter* iter = &ctx->iter;
  char c = Iter_currChar(iter);
  if (!Chars_isNameStart(c)) {
    errno = 1; return (String) {0};
  }
  char* buffer = A_xloc(16);
  size_t bufferSize = 16;
  size_t nameSize = 0;

  Iter_foreachChars(c, iter) {
    if (!Chars_isNameStart(c) && !Chars_isDigit(c)) break;
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
  errno = 0; return String_new(buffer, nameSize, true);
}

void Utils_Iter_skipVoid(Context* ctx, bool strict) {
  Iter* iter = &ctx->iter;
  const char* start = iter->curr;
  char c;
  Iter_foreachChars(c, iter) {
    if (c == '#') {
      Iter_foreachChars(c, iter) {
        if (c == '\n') {
          break;
        }
      }
    }
    else if (!Chars_isVoid(c)) {
      break;
    }
  }
  if (strict && start == iter->curr) {
    if (c == '\0') {
      Errors_metaparser_unexpectedEnd(ctx, Source_byIter(
        ViewString_by(ctx->filename),
        &ctx->iter,
        SPD_new(
          SPDMode_BACK_CHAR_SHIFT,
          1,
          (SPDFlags) { .lineTransitionAfterCharShift = false }
        ),
        SPD_new2(SPDMode_CURR_LINE)
      ));
    }
    else {
      Iter prevCharIter = Iter_copy(iter);
      Iter_unsafeBackChar(&prevCharIter);

      Errors_metaparser_anotherTokenExpected(ctx, Source_byIters(
        ViewString_by(ctx->filename),
        &prevCharIter, SPD_new2(SPDMode_CURR_WORD),
        &ctx->iter, SPD_new2(SPDMode_CURR_CHAR)
      ), ViewString_of(" "));
    }
  }
}

void_errno Utils_Iter_skipChar(Context* ctx, char c) {
  Iter* iter = &ctx->iter;
  if (Iter_currChar(iter) != c) {
    Errors_metaparser_anotherTokenExpected(ctx, Source_byIter(
      ViewString_by(ctx->filename),
      iter,
      SPD_new2(SPDMode_CURR_CHAR),
      SPD_new2(SPDMode_CURR_CHAR)
    ), ViewString_of((char[2]){c, '\0'}));
  }
  Iter_nextChar(iter);
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
  bufferSize = nameSize+1;
  buffer = A_reloc(buffer, bufferSize);
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

  // TODO: redesign the interface to work more securely with large numbers, as they will now be truncated due to conversion to double
  char* endPtr;
  double result = (double) Strings_strtol(main.buffer, 10, &endPtr);
  if (*endPtr != '\0') goto endPtrError;
  double fracResult = (double) Strings_strtol(frac.buffer, 10, &endPtr);
  if (*endPtr != '\0') goto endPtrError;

  for (size_t i = 0; i < frac.size; i++) {
    fracResult/=10;
  }
  StringBuilder_free(&mainBuilder);
  StringBuilder_free(&fracBuilder);
  return result + fracResult;

  endPtrError: {
    Errors_internal_unexpectedBehavior(ViewString_of("Utils_Iter_readNumber"), ViewString_of(""));
    non_call_return 0;
  }
}

type_errno(Sts_MetaDeclarationValue) Utils_Iter_readPath(Context* ctx) {
  type_errno(String) firstString = Utils_Iter_readName(ctx);
  if (errno != 0) return (Sts_MetaDeclarationValue) {};
  Sts_MetaDeclarationValue leftValue = Sts_MetaDeclarationValue_byName1(firstString, ctx);
  Sts_MetaDeclarationValue_checkForLink(&leftValue, ctx);

  Utils_Iter_skipVoid(ctx, false);
  while (Iter_currChar(&ctx->iter) == '.') {
    Iter_nextChar(&ctx->iter);
    Utils_Iter_skipVoid(ctx, false);

    type_errno(String) nextString = Utils_Iter_readName(ctx);
    if (errno != 0) {
      Errors_metaparser_anotherTokenExpected(ctx, Source_byIter(
        ViewString_by(ctx->filename),
        &ctx->iter,
        SPD_new2_double(SPDMode_CURR_CHAR)
      ), ViewString_of("<name>"));
    }
    Sts_MetaDeclarationValue rightValue = Sts_MetaDeclarationValue_byName1(nextString, ctx);
    Sts_MetaDeclarationValue_checkForLink(&rightValue, ctx);

    Sts_MetaDeclarationExpression* expression = A_xloc(sizeof(Sts_MetaDeclarationExpression));
    *expression = (Sts_MetaDeclarationExpression) {
      .type = Sts_MetaDeclarationExpressionType_CHILD,
      .value1 = leftValue,
      .value2 = rightValue,
    };
    errno = 0; leftValue = Sts_MetaDeclarationValue_byExpression(expression);
  }
  return leftValue;
}
