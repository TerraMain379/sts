// #define NAME ...
// #define TYPE ...
// #define FREE_FUN ...

#include "utils.h"
#include "allocator.h"

#define CONCAT(a, b) a ## _ ## b
#define RC_FUN(name, fun) CONCAT(name, fun)

typedef struct {
  size_t refCount;
  TYPE value;
  bool freeRequired;
} NAME;

NAME RC_FUN(NAME, init)(TYPE value) {
  
}

TYPE* RC_FUN(NAME, get)(NAME rc) {
  rc.refCount++;
  return rc.value;
}
void RC_FUN(NAME, drop)(NAME rc) {
  rc.refCount--;
  if (rc.refCount == 0) {
    FREE_FUN(rc.value);
    if (rc.freeRequired) A_free(rc.value);
  }
}

#undef CONCAT
#undef RC_FUN
