#include "utils.h"
#include "strings.h"

// #define NAME ...
// #define TYPE ...
// #define NULLV ...
// #define FREEFUN ...
// #include "gmap.h"
// #undef NAME
// #undef TYPE
// #undef NULLV
// #undef FREEFUN

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
MUT_WEAK(ELEMENT(NAME)) FUNCTION(NAME, getElementByHash)(BORROW(NAME) map, int hash);
MUT_WEAK(ELEMENT(NAME)) FUNCTION(NAME, getElement)(BORROW(NAME) map, BORROW(ViewString) key);
type_errno(TYPE*) FUNCTION(NAME, get)(BORROW(NAME) map, BORROW(ViewString) key);
bool FUNCTION(NAME, contains)(BORROW(NAME) map, BORROW(ViewString) key);
type_errno(TYPE) FUNCTION(NAME, set)(NAME* map, BORROW(ViewString) key, TYPE value);
type_errno(TYPE) FUNCTION(NAME, setByOwnKey)(NAME* map, OWNER(String) key, TYPE value);
type_errno(TYPE) FUNCTION(NAME, remove)(NAME* map, BORROW(ViewString) key);
void FUNCTION(NAME, free)(NAME* map);
void FUNCTION(NAME, freeElements)(NAME* map);

#undef __NAME
#undef _NAME
#undef CONCAT
#undef _CONCAT
#undef ELEMENT
#undef _ELEMENT
#undef FUNCTION
