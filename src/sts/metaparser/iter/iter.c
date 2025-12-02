#include "iter.h"

Iter Iter_create(const char* const str, size_t size) {
  return (Iter) {
    .curr = str;
    .size = size;
  };
}
Iter Iter_new(const String string) {
  return (Iter) {
    .curr = string.buffer;
    .size = size.length;
  };
}
