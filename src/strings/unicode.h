#include "utils.h"

typedef uint32_t uchar;

uchar UTF8_readUChar(char** iter);
void UTF8_skipBOM(char** iter);
