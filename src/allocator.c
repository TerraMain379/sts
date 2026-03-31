#include "allocator.h"

#include <stdlib.h>
#include <stdio.h>
#include "utils.h"

void A_err() {
  fprintf(stderr, "Error: %s\n", "allocate memory error");
  abort();
}

#ifdef BUILD_TESTS
  typedef struct A_Element {
    intptr_t ptr;
    size_t size;
  } A_Element;
  #define stackSize 2048
  typedef struct A_LocStack {
    size_t size;
    A_Element ptrs[stackSize];
  } A_LocStack;

  size_t counter = 0;
  size_t loc_counter = 0;
  size_t reloc_counter = 0;
  size_t free_counter = 0;

  A_LocStack locStack;
  
  type_errno(size_t) searchLoc(intptr_t ptr) {
    for (size_t i = 0; i < locStack.size; i++) {
      if (locStack.ptrs[i].ptr == ptr) {
        errno = 0; return i;
      }
    }
    errno = 1; return 0;
  }
#endif

inline void* A_loc(size_t size) {
  #ifdef BUILD_TESTS
    loc_counter++;
    counter++;
    void* ptr = malloc(size);
    locStack.ptrs[locStack.size] = (A_Element) { (intptr_t) ptr, size };
    locStack.size++;
    if (locStack.size >= stackSize) A_err();
    return ptr;
  #else
    return malloc(size);
  #endif
}
inline void* A_xloc(size_t size) {
  void* ptr = malloc(size);
  if (ptr == null && size > 0) A_err();
  #ifdef BUILD_TESTS
    loc_counter++;
    counter++;
    locStack.ptrs[locStack.size] = (A_Element) { (intptr_t) ptr, size };
    locStack.size++;
    if (locStack.size >= stackSize) A_err();
  #endif
  return ptr;
}
inline void* A_reloc(void* ptr, size_t size) {
  #ifdef BUILD_TESTS
    intptr_t optr = (intptr_t) ptr;
    void* nptr = realloc(ptr, size);
    size_t e = searchLoc(optr);
    if (errno != 0) A_err();
    reloc_counter++;
    locStack.ptrs[e].ptr = (intptr_t) nptr;
    locStack.ptrs[e].size = size;
    return nptr;
  #else
    return realloc(ptr, size);
  #endif
}
inline void* A_xreloc(void* ptr, size_t size) {
  #ifdef BUILD_TESTS
    intptr_t optr = (intptr_t) ptr;
  #endif
  void* nptr = realloc(ptr, size);
  if (nptr == null && size > 0) A_err();
  #ifdef BUILD_TESTS
    size_t e = searchLoc(optr);
    if (errno != 0) A_err();
    reloc_counter++;
    locStack.ptrs[e].ptr = (intptr_t) nptr;
    locStack.ptrs[e].size = size;
  #endif
  return nptr;
}
inline void A_free(void* ptr) {
  #ifdef BUILD_TESTS
    intptr_t optr = (intptr_t) ptr;
  #endif
  free(ptr);
  #ifdef BUILD_TESTS
    free_counter++;
    counter--;
    size_t e = searchLoc(optr);
    if (errno != 0) A_err();
    if (locStack.size == 0) A_err();
    for (size_t i = e; i < locStack.size-1; i++) {
      locStack.ptrs[i] = locStack.ptrs[i+1];
    }
    locStack.size--;
    locStack.ptrs[locStack.size].ptr = (intptr_t) null;
    locStack.ptrs[locStack.size].size = 0;
  #endif
}

#ifdef BUILD_TESTS
  size_t A_getCounter() {
    return counter;
  }
  size_t A_getLocCounter() {
    return loc_counter;
  }
  size_t A_getRelocCounter() {
    return reloc_counter;
  }
  size_t A_getFreeCounter() {
    return free_counter;
  }
  bool A_checkLoc(void* ptr) {
    searchLoc((intptr_t) ptr);  
    return errno == 0;
  }
  size_t A_getSize(void* ptr) {
    size_t e = searchLoc((intptr_t) ptr);  
    if (errno != 0) A_err();
    return locStack.ptrs[e].size;
  }
#endif
