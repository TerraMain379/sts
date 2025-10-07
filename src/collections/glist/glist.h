#include "utils.h"
#include "strings.h"

// #define NAME ...
// #define TYPE ...
// #define NULLV ...
// #include "glist.h"
// #undef NAME
// #undef TYPE
// #undef NULLV

// logic for generate names for structs
#define CONCAT(a, b) a ## _ ## b
#define FUNCTION(name, fun) CONCAT(name, fun)

// glist
typedef struct {
  size_t size;
  size_t capacity;
  TYPE* array;
} NAME;

void FUNCTION(NAME, init)(NAME* list, size_t capacity);
void FUNCTION(NAME, setCapacity)(NAME* list, size_t capacity);
void FUNCTION(NAME, add)(NAME* list, TYPE value);
void_errno FUNCTION(NAME, insert)(NAME* list, TYPE value, size_t index);
type_errno(TYPE) FUNCTION(NAME, set)(NAME* list, TYPE value, size_t index);
type_errno(TYPE) FUNCTION(NAME, remove)(NAME* list, size_t index);
type_errno(TYPE*) FUNCTION(NAME, get)(NAME* list, size_t index);
void FUNCTION(NAME, free)(NAME* list);

#undef CONCAT
#undef FUNCTION
