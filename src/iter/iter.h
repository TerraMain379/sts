#pragma once

#include "utils.h"
#include "strings.h"
#include "unicode.h"

typedef struct Iter {
  WEAK(char*) start;
  WEAK(char*) curr;
  size_t size;
  Unicode_UCharInfo currUInfo;
  bool currUInfoIsValid;
} Iter;

Iter Iter_create(WEAK(char*) str, size_t size);
Iter Iter_new(WEAK(ViewString) vstring);
Iter Iter_copy(BORROW(Iter*) iter);

char Iter_currChar(Iter* iter);
char Iter_nextChar(Iter* iter);

uchar Iter_currUChar(Iter* iter);
uchar Iter_nextUChar(Iter* iter);

void Iter_unsafeBackChar(Iter* iter);
void Iter_unsafeBackUChar(Iter* iter);


// iter: Iter*
#define Iter_foreachChars(c, iter) \
  for ( \
    (c) = Iter_currChar(iter); \
    (c) != '\0'; \
    (c) = Iter_nextChar(iter) \
  )
#define Iter_foreachUChars(uc, iter) \
  for ( \
    (uc) = Iter_currUChar(iter); \
    (uc) != 0; \
    (uc) = Iter_nextUChar(iter) \
  )
