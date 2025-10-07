#include "unicode.h"
#include "utils.h"

#define UNKNOWN_CHAR 0xFFFD

int readULen(uint8_t c) {
  if (c == 0) return 0;
  if ((c & 0x80) == 0x00) return 1;
  else if ((c & 0xE0) == 0xC0) return 2;
  else if ((c & 0xF0) == 0xE0) return 3;
  else if ((c & 0xF8) == 0xF0) return 4;
  else return -1;
}

uchar UTF8_readUChar(char** iter){
  uchar result = 0;
  const uint8_t* ch = (const uint8_t*) *iter;
  int len = readULen(*ch);

  if (len == 0) {
    ++*iter;
    return 0;
  }
  if (len == -1) {
    ++*iter;
    return UNKNOWN_CHAR;
  }

  // extracting payload from first byte
  if (len == 1) {
    result = ch[0];
    *iter += 1;
    return result;
  } else if (len == 2) {
    result = (uchar)((ch[0] & 0x1F) << 6);
  } else if (len == 3) {
    result = (uchar)((ch[0] & 0x0F) << 12);
  } else { // len == 4
    result = (uchar)((ch[0] & 0x07) << 18);
  }

  // reading rest bytes
  for (int i = 1; i < len; i++) {
    // checking byte mask 10xxxxxx
    if ((ch[i] & 0xC0) != 0x80) {
      // invalid continuation: consume one byte to ensure progress
      ++(*iter);
      return UNKNOWN_CHAR;
    }
    // saving payload
    result |= (uchar)((ch[i] & 0x3F) << (6 * (len - i - 1)));
  }

  // overlong test (Error char, if char takes up more space than necessary)
  if ((len == 2 && result < 0x80) ||
      (len == 3 && result < 0x800) ||
      (len == 4 && result < 0x10000)) {
    *iter += len;
    return UNKNOWN_CHAR;
  }

  // reject UTF-16 surrogate range
  if (result >= 0xD800 && result <= 0xDFFF) {
    *iter += len;
    return UNKNOWN_CHAR;
  }

  // testing valid unicode scope
  if (result > 0x10FFFF) {
    *iter += len;
    return UNKNOWN_CHAR;
  }

  // move iter
  *iter += len;
  return result;
}
void UTF8_skipBOM(char** iter) {
  uint8_t* bytes = (uint8_t*)*iter;
  if (bytes[0] == 0xEF && bytes[1] == 0xBB && bytes[2] == 0xBF) {
    (*iter) += 3;
  }
}
