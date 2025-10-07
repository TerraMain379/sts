#include "errors.h"

#include <stdio.h>
#include <stdlib.h>

static const char* findLineStart(const char* context, const char* start, size_t* lineNumber) {
  size_t line = 1;
  const char* p = start;
  const char* lastLineStart = start;
  while (p < context) {
    if (*p == '\n') {
      line++;
      lastLineStart = p + 1;
    }
    p++;
  }
  if (lineNumber) *lineNumber = line;
  return lastLineStart;
}
static const char* findLineEnd(const char* context) {
  while (1) {
    if (*context == '\0' || *context == '\n') {
      return context-1;
    }
  }
  return 0;
}


void Errors_metaparser_unkownToken(String token, char* context, char* start) {
  size_t lineNumber = 0;
  const char* lineStart = findLineStart(context, start, &lineNumber);
  const char* lineEnd = findLineEnd(context);
  size_t lineLen = lineEnd - lineStart + 1;

  // Вычислить позицию символа
  size_t pos = context - lineStart;

  char prefix[64];
  snprintf(prefix, sizeof(prefix), "in context (line %zu): ", lineNumber);

  size_t prefixLen = Strings_getLen(prefix);
  printf("[ERROR]: MetaParser: Unkown token: \"%s\"\n", token.buffer);
  printf("%s", prefix);
  fwrite(lineStart, 1, lineLen, stdout);
  printf("\n");
  for (size_t i = 0; i < pos + prefixLen; ++i) putchar('-');
  printf("^\n");
  exit(1);
}
void Errors_metaparser_invalidName(String name, char* context, String ownerOfName, char* start) {}
void Errors_metaparser_unexpectedEnd(size_t endCharsNum, char* end, char* start) {}
void Errors_metaparser_expandingByYourself(String zone, String expander, char* context) {}
void Errors_internal_nullPointer(String var, String location) {}
void Errors_internal_allocateMemoryError(String location) {}

void Warnings_metaparser_redefiningRegex(String regexName, String token, char* start) {}
