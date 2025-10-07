#include "metaparsermodules/utils.h"
#include "errors.h"
#include "allocator.h"

String readName(struct StsFile* stsFile, char** iter) {
  char* ch = *iter;
  size_t bufMemSize = 128;
  size_t bufSize = 0;
  char* buf = A_loc(128);

  char c = *ch;
  buf[bufSize] = c;
  bufSize++;
  
  for (; ; ch++) {
    if (bufSize == bufMemSize) {
      bufMemSize+=128;
      buf = A_reloc(buf, bufMemSize);
    }
    c = *ch;

    if (!isNameChar(c)) {
      if (c == '\0') {
        size_t s;
        if (bufSize < 30) s = bufSize;
        else s = 10;
        Errors_metaparser_unexpectedEnd(s, ch, stsFile->currStart);
      }
      break;
    } 
    buf[bufSize] = c;
    
    bufSize++;
  }
  buf[bufSize] = '\0';
  buf = A_reloc(buf, bufSize+1);
  *iter = ch;
  
  return String_new(buf, bufSize, true);
}
String readRegex(struct StsFile* stsFile, char** iter) {
  char* ch = *iter;
  size_t bufMemSize = 128;
  size_t bufSize = 0;
  char* buf = A_loc(128);

  for (; ; ch++) {
    if (bufSize == bufMemSize) {
      bufMemSize+=128;
      buf = A_reloc(buf, bufMemSize);
    }
    char c = *ch;

    if (c == '\\') {
      ch++;
      c = *ch;
      if (c == '"') {
        buf[bufSize] = '"';
      }
      else if (c == '\0') {
        size_t s;
        if (bufSize < 30) s = bufSize;
        else s = 10;
        Errors_metaparser_unexpectedEnd(s, ch, stsFile->currStart);
      }
      else {
        buf[bufSize] = '\\';
        bufSize++;
        buf[bufSize] = c;
      }
    }
    else if (c == '"') break;
  
    bufSize++;
  }
  buf[bufSize] = '\0';
  buf = A_reloc(buf, bufSize+1);
  *iter = ch;

  return String_new(buf, bufSize, true);
}


void parseErrorsProcessing(struct StsFile* stsFile, char* ch, const char* unkownToken, size_t unexpectedEndEndCharNum) {
  if (*ch == '\0') {
    Errors_metaparser_unexpectedEnd(unexpectedEndEndCharNum, ch, stsFile->currStart);
  }
  else {
    Errors_metaparser_unkownToken(String_const(unkownToken), ch, stsFile->currStart);
  }
}

void skipVoid(char** iter) {
  char* ch = *iter;
  while (isVoid(*ch)) ch++;
  *iter = ch;
}

inline bool isLetter(char c) {
  return ('a' <= c && 'z' >= c) || ('A' <= c && 'Z' >= c);
}
inline bool isDigit(char c) {
  return '0' <= c && c <= '9';
}
inline bool isNameChar(char c) {
  return isLetter(c) || isDigit(c) || c == '_';
}
inline bool isVoid(char c) {
  return c == ' ' || c == '\n' || c == '\r' || c == '\t';
}
