#pragma once

#include "utils.h"

typedef uint32_t uchar;

typedef struct Unicode_UCharInfo {
  uchar uc;
  size_t byteSize;
  int errorCode;
} Unicode_UCharInfo;

#define Unicode_ERROR_CHAR 0xFFFD

Unicode_UCharInfo Unicode_readUChar(WAKE(char) str, size_t byteLimit);
size_t Unicode_readUCharLength(char startChar);
