#include "utils.h"
#include "strings.h"

// #define TYPE ...
// #define NAME ...
// #define NULLV ...
// #define FREEFUN ...
// #define ISPOINTER ...
// #include "gmap.h"
// #undef TYPE
// #undef NAME
// #undef NULLV
// #undef FREEFUN
// #undef ISPOINTER

// logic for generate names for structs
#define CONCAT(a, b) a ## _ ## b
#define ELEMENT(name) CONCAT(name, element)
#define FUNCTION(name, fun) CONCAT(name, fun)

//gmap
typedef struct {
  size_t size;
  ELEMENT(NAME)* first;
  ELEMENT(NAME)* last;
} NAME;
//gmap_element
typedef struct {
  String key;
  int hash;
  TYPE value;
  #ifdef FREEFUN
    bool deleteRequired;
  #endif
  ELEMENT(NAME)* next;
} ELEMENT(NAME);

void FUNCTION(NAME, init)(NAME* map);
ELEMENT(NAME)* FUNCTION(NAME, getElementByHash)(NAME* map, int hash);
ELEMENT(NAME)* FUNCTION(NAME, getElement)(NAME* map, const String key);
type_errno(TYPE) FUNCTION(NAME, get)(NAME* map, const String key);
bool FUNCTION(NAME, set)(NAME* map, const String key, TYPE value, 
  #ifdef FREEFUN
    bool deleteRequired
  #endif
);
void_errno FUNCTION(NAME, remove)(NAME* map, const String key);
type_errno(TYPE) FUNCTION(NAME, getOwnership)(NAME* map, const String key);
void FUNCTION(NAME, free)(NAME* map);

#undef CONCAT
#undef ELEMENT
#undef FUNCTION
