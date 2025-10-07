#include "glist.h"

#include "allocator.h"

// #define TYPE ...
// #define NAME ...
// #define NULLV ...
// #define FREEFUN ...
// #define ISPOINTER ...
// #include "glist.c.h"
// #undef TYPE
// #undef NAME
// #undef NULLV
// #undef FREEFUN
// #undef ISPOINTER

// logic for generate names for structs
#define CONCAT(a, b) a ## _ ## b
// #define ELEMENT(name) CONCAT(name, element)
#define FUNCTION(name, fun) CONCAT(name, fun)

static inline bool validIndex(NAME* list, size_t index) {
  return index < list->size;
}
static inline void doubleCapacity(NAME* list) {
  if (list->capacity == 0) FUNCTION(NAME, setCapacity)(list, 1);
  else FUNCTION(NAME, setCapacity)(list, 2 * list->capacity);
}

void FUNCTION(NAME, init)(NAME* list, size_t capacity) {
  list->size = 0;
  list->capacity = capacity;
  list->array = A_loc(sizeof(TYPE)*capacity);
  list->deleteRequairesArray = A_loc(sizeof(bool)*capacity);
}
void FUNCTION(NAME, setCapacity)(NAME* list, size_t capacity) {
  if (capacity == 0) {
    A_free(list->array);
    A_free(list->deleteRequairesArray);
    list->array = 0;
    list->deleteRequairesArray = 0;
  }
  else {
    list->array = A_reloc(list->array, sizeof(TYPE)*capacity);
    list->deleteRequairesArray = A_reloc(list->deleteRequairesArray, sizeof(bool)*capacity);
  }
  list->capacity = capacity;
}
void FUNCTION(NAME, add)(NAME* list, TYPE value, bool deleteRequaired) {
  if (list->size == list->capacity) {
    doubleCapacity(list);
  }
  list->array[list->size] = value;
  list->deleteRequairesArray[list->size] = deleteRequaired;
  list->size++;
}
void_errno FUNCTION(NAME, insert)(NAME* list, TYPE value, bool deleteRequaired, size_t index) {
  if (index >= list->size) {
    errno = 1; return;
  }
  if (list->capacity == list->size) {
    doubleCapacity(list);
  }
  for (size_t i = list->size; i > index; i--) {
    list->array[i] = list->array[i - 1];
    list->deleteRequairesArray[i] = list->deleteRequairesArray[i - 1];
  }
  list->array[index] = value;
  list->deleteRequairesArray[index] = deleteRequaired;
  list->size++;
  
  errno = 0; return;
}
void_errno FUNCTION(NAME, set)(NAME* list, TYPE value, bool deleteRequaired, size_t index) {
  if (index >= list->size) {
    errno = 1; return;
  }
  #ifdef FREEFUN
    if (list->deleteRequairesArray[index]) {
      #ifdef ISPOINTER
        FREEFUN(list->array[index]);
      #endif
      #ifndef ISPOINTER
        FREEFUN(& list->array[index]);
      #endif
    }
  #endif
  list->array[index] = value;
  list->deleteRequairesArray[index] = deleteRequaired;

  errno = 0; return;
}
void_errno FUNCTION(NAME, remove)(NAME* list, size_t index) {
  if (index >= list->size) {
    errno = 1; return;
  }

  #ifdef FREEFUN
    if (list->deleteRequairesArray[index]) {
      #ifdef ISPOINTER
        FREEFUN(list->array[index]);
      #endif
      #ifndef ISPOINTER
        FREEFUN(& list->array[index]);
      #endif
    }
  #endif
  for (size_t i = index; i < list->size - 1; i++) {
    list->array[i] = list->array[i + 1];
    list->deleteRequairesArray[i] = list->deleteRequairesArray[i + 1];
  }
  list->size--;
  errno = 0; return;
}
type_errno(TYPE*) FUNCTION(NAME, get)(NAME* list, size_t index) {
  if (index >= list->size) {
    errno = 1; return 0;
  }
  errno = 0; return & list->array[index];
}
type_errno(TYPE) FUNCTION(NAME, getOwnership)(NAME* list, size_t index) {
  if (index >= list->size) {
    errno = 1; return NULLV;
  } 
  TYPE value = list->array[index];
  list->deleteRequairesArray[index] = false;
  FUNCTION(NAME, remove)(list, index);
  errno = 0; return value;
}
void FUNCTION(NAME, free)(NAME* list) {
  #ifdef FREEFUN
    for (size_t i = 0; i < list->size; i++) {
      if (list->deleteRequairesArray[i]) {
        #ifdef ISPOINTER
          FREEFUN(list->array[i]);
        #endif
        #ifndef ISPOINTER
          FREEFUN(& list->array[i]);
        #endif
      }
    }
  #endif
  A_free(list->array);
  A_free(list->deleteRequairesArray);
}
