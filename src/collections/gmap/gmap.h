#include "utils.h"
#include "strings.h"

// #define NAME ...
// #define TYPE ...
// #define NULLV ...
// #include "gmap.h"
// #undef NAME
// #undef TYPE
// #undef NULLV

// logic for generate names for structs
#define __NAME(name) _ ## name
#define _NAME(name) __NAME(name)
#define CONCAT(a, b) a ## _ ## b
#define _CONCAT(a, b) _ ## a ## _ ## b
#define ELEMENT(name) CONCAT(name, element)
#define _ELEMENT(name) _CONCAT(name, element)
#define FUNCTION(name, fun) CONCAT(name, fun)

typedef struct NAME NAME;
typedef struct ELEMENT(NAME) ELEMENT(NAME);

// gmap
struct NAME {
  size_t size;
  OWNER(ELEMENT(NAME)) first;
  OWNER(ELEMENT(NAME)) last;
};

// gmap_element
struct ELEMENT(NAME) {
  String key;
  int hash;
  TYPE value;
  MUT_WEAK(ELEMENT(NAME)) next;
};

int FUNCTION(NAME, getHash)(const char* key);

void FUNCTION(NAME, init)(NAME* map);
WAKE(ELEMENT(NAME)) FUNCTION(NAME, getElementByHash)(BORROW(NAME) map, int hash);
WAKE(ELEMENT(NAME)) FUNCTION(NAME, getElement)(BORROW(NAME) map, const String key);
type_errno(WAKE(TYPE)) FUNCTION(NAME, get)(BORROW(NAME) map, const String key);
bool FUNCTION(NAME, contains)(BORROW(NAME) map, const String key);
type_errno(TYPE) FUNCTION(NAME, set)(NAME* map, const String key, TYPE value);
type_errno(TYPE) FUNCTION(NAME, remove)(NAME* map, const String key);
void FUNCTION(NAME, free)(BORROW(NAME) map);

#undef __NAME
#undef _NAME
#undef CONCAT
#undef _CONCAT
#undef ELEMENT
#undef _ELEMENT
#undef FUNCTION
