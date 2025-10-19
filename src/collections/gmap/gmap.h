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
  ELEMENT(NAME)* first;
  ELEMENT(NAME)* last;
};

// gmap_element
struct ELEMENT(NAME) {
  String key;
  int hash;
  TYPE value;
  ELEMENT(NAME)* next;
};

int FUNCTION(NAME, getHash)(const char* key);

void FUNCTION(NAME, init)(NAME* map);
ELEMENT(NAME)* FUNCTION(NAME, getElementByHash)(NAME* map, int hash);
ELEMENT(NAME)* FUNCTION(NAME, getElement)(NAME* map, const String key);
type_errno(TYPE*) FUNCTION(NAME, get)(NAME* map, const String key);
bool FUNCTION(NAME, contains)(NAME* map, const String key);
type_errno(TYPE) FUNCTION(NAME, set)(NAME* map, const String key, TYPE value);
type_errno(TYPE) FUNCTION(NAME, remove)(NAME* map, const String key);
void FUNCTION(NAME, free)(NAME* map);

#undef __NAME
#undef _NAME
#undef CONCAT
#undef _CONCAT
#undef ELEMENT
#undef _ELEMENT
#undef FUNCTION
