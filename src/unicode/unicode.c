#include "unicode.h"

Unicode_UCharInfo Unicode_readUChar(WAKE(char) str, size_t byteLimit) {
  unsigned char* s = (unsigned char*) str;
  uchar uc = 0;
  int errorCode = 0;
  size_t len = Unicode_readUCharLength(*s);
  if (len > byteLimit) {
    errorCode = 2;
  }
  else {
    if (len == 1) {
      uc = s[0];
    }
    else if (len == 2) {
      uc = ((s[0] & 0x1F) << 6) |
        (s[1] & 0x3F);
    }
    else if (len == 3) {
      uc = ((s[0] & 0x0F) << 12) |
        ((s[1] & 0x3F) << 6) |
        (s[2] & 0x3F);
    }
    else if (len == 4) {
      uc = ((s[0] & 0x07) << 18) |
        ((s[1] & 0x3F) << 12) |
        ((s[2] & 0x3F) << 6) |
        (s[3] & 0x3F);
    }
    else {
      uc = Unicode_ERROR_CHAR;
      errorCode = 1;
    }
  }

  return (Unicode_UCharInfo) {
    .uc = uc;
    .byteSize = len;
    .errorCode = errorCode;
  };
}
size_t Unicode_readUCharLength(char startChar) {
  if (startChar < 0x80) return 1;
  if (startChar >= 0xC0 && startChar < 0xE0) return 2;
  if (startChar >= 0xE0 && startChar < 0xF0) return 3;
  if (startChar >= 0xF0 && startChar < 0xF8) return 4;
  return 0;
}
