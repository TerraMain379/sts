#include "allocator.h"

// #define NAME ...
// #define TYPE ...
// #define NULLV ...
// #define FREEFUN ...
// #include "glist.c.h"
// #undef NAME
// #undef TYPE
// #undef NULLV
// #undef FREEFUN

// logic for generate names for structs
#define CONCAT(a, b) a ## _ ## b
#define FUNCTION(name, fun) CONCAT(name, fun)

void FUNCTION(NAME, doubleCapacity)(NAME* list) {
  if (list->capacity == 0) FUNCTION(NAME, setCapacity)(list, 1);
  else FUNCTION(NAME, setCapacity)(list, 2 * list->capacity);
}

void FUNCTION(NAME, init)(NAME* list, size_t capacity) {
  list->size = 0;
  list->capacity = capacity;
  list->array = (OWNER(TYPE)) A_xloc(sizeof(TYPE)*capacity);
}
void FUNCTION(NAME, setCapacity)(NAME* list, size_t capacity) {
  if (capacity == 0) {
    A_free((void*) list->array);
    list->array = null;
  }
  else {
    list->array = (OWNER(TYPE)) A_xreloc((void*) list->array, sizeof(TYPE)*capacity);
  }
  list->capacity = capacity;
}
TYPE* FUNCTION(NAME, add)(NAME* list, TYPE value) {
  if (list->size == list->capacity) {
    FUNCTION(NAME, doubleCapacity)(list);
  }
  list->array[list->size] = value;
  TYPE* ptr = &list->array[list->size];
  list->size++;
  return ptr;
}
void_errno FUNCTION(NAME, insert)(NAME* list, TYPE value, size_t index) {
  if (index >= list->size) {
    errno = 1; return;
  }
  if (list->capacity == list->size) {
    FUNCTION(NAME, doubleCapacity)(list);
  }
  for (size_t i = list->size; i > index; i--) {
    list->array[i] = list->array[i - 1];
  }
  list->array[index] = value;
  list->size++;
  
  errno = 0; return;
}
type_errno(TYPE) FUNCTION(NAME, set)(NAME* list, TYPE value, size_t index) {
  if (index >= list->size) {
    errno = 1; return NULLV;
  }
  TYPE oldValue = list->array[index];
  list->array[index] = value;

  errno = 0; return oldValue;
}
type_errno(TYPE) FUNCTION(NAME, remove)(NAME* list, size_t index) {
  if (index >= list->size) {
    errno = 1; return NULLV;
  }

  TYPE value = list->array[index];
  for (size_t i = index; i < list->size - 1; i++) {
    list->array[i] = list->array[i + 1];
  }
  list->size--;
  errno = 0; return value;
}
type_errno(MUT_WEAK(TYPE)) FUNCTION(NAME, get)(BORROW(NAME) list, size_t index) {
  if (index >= list->size) {
    errno = 1; return null;
  }
  errno = 0; return & list->array[index];
}
void FUNCTION(NAME, free)(NAME* list) {
  A_free((void*) list->array);
}
void FUNCTION(NAME, freeElements)(NAME* list) {
  #ifdef FREEFUN
    for (size_t i = 0; i < list->size; i++) {
      FREEFUN(&list->array[i]);
    }
  #endif
}
