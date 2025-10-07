#include "allocator.h"

#include <stdlib.h>
#include <stdio.h>

void A_err() {
  fprintf(stderr, "Error: %s\n", "allocate memory error");
  abort();
}

inline void* A_loc(size_t size) {
  return malloc(size);
}
inline void* A_xloc(size_t size) {
  void* ptr = malloc(size);
  if (ptr == 0 && size > 0) A_err();
  return ptr;
}
inline void* A_reloc(void* ptr, size_t size) {
  return realloc(ptr, size);
}
inline void* A_xreloc(void* ptr, size_t size) {
  ptr = realloc(ptr, size);
  if (ptr == 0 && size > 0) A_err();
  return ptr;
}
inline void A_free(void* ptr) {
  free(ptr);
}
