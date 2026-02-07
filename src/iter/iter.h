#include "utils.h"
#include "unicode.h"

struct Iter;
typedef struct Iter Iter;

Iter Iter_create(WAKE(char) const str, size_t size);
Iter Iter_new(const String string);

char Iter_currChar(Iter* iter);
char Iter_nextChar(Iter* iter);

uchar Iter_currUChar(Iter* iter);
uchar Iter_nextUChar(Iter* iter);

void Iter_unsafeBackChar(Iter* iter);
void Iter_unsafeBackUChar(Iter* iter);


// iter: Iter*
#define Iter_foreachChars(c, iter) \
  for( \
    char c = Iter_currChar(iter); \
    c != '\0'; \
    c = Iter_nextChar(iter) \
  )
#define Iter_foreachUChars(uc, iter) \
  for( \
    uchar uc = Iter_currUChar(iter); \
    uc != 0; \
    uc = Iter_nextUChar(iter) \
  )
