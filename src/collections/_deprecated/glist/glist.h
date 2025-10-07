#include "utils.h"
#include "strings.h"

// #define TYPE ...
// #define NAME ...
// #define NULLV ...
// #define FREEFUN ...
// #define ISPOINTER ...
// #include "glist.h"
// #undef TYPE
// #undef NAME
// #undef NULLV
// #undef FREEFUN
// #undef ISPOINTER

// logic for generate names for structs
#define CONCAT(a, b) a ## _ ## b
#define FUNCTION(name, fun) CONCAT(name, fun)

// glist
typedef struct {
  size_t size;
  size_t capacity;
  TYPE* array;
  bool* deleteRequairesArray;
} NAME;

void FUNCTION(NAME, init)(NAME* list, size_t capacity);
void FUNCTION(NAME, setCapacity)(NAME* list, size_t capacity);
void FUNCTION(NAME, add)(NAME* list, TYPE value, bool deleteRequaired);
void_errno FUNCTION(NAME, insert)(NAME* list, TYPE value, bool deleteRequaired, size_t index);
void_errno FUNCTION(NAME, set)(NAME* list, TYPE value, bool deleteRequaired, size_t index);
void_errno FUNCTION(NAME, remove)(NAME* list, size_t index);
type_errno(TYPE*) FUNCTION(NAME, get)(NAME* list, size_t index);
type_errno(TYPE) FUNCTION(NAME, getOwnership)(NAME* list, size_t index);
void FUNCTION(NAME, free)(NAME* list);

#undef CONCAT
#undef FUNCTION
