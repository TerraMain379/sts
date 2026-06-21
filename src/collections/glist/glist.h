#include "utils.h"
#include "strings.h"

// #define NAME ...
// #define TYPE ...
// #define NULLV ...
// #define FREEFUN ...
// #define TYPEDEFS ...
// #include "glist.h"
// #undef NAME
// #undef TYPE
// #undef NULLV
// #undef FREEFUN
// #undef TYPEDEFS

// logic for generate names for structs
#define CONCAT(a, b) a ## _ ## b
#define FUNCTION(name, fun) CONCAT(name, fun)

#ifdef TYPEDEFS
  typedef struct NAME NAME;
#endif

// glist
struct NAME {
  size_t size;
  size_t capacity;
  OWNER(TYPE*) array;
};

void FUNCTION(NAME, doubleCapacity)(NAME* list);

void FUNCTION(NAME, init)(NAME* list, size_t capacity);
void FUNCTION(NAME, setCapacity)(NAME* list, size_t capacity);
MUT_BORROW(TYPE*) FUNCTION(NAME, add)(NAME* list, OWNER(TYPE) value);
void_errno FUNCTION(NAME, insert)(NAME* list, OWNER(TYPE) value, size_t index);
type_errno(OWNER(TYPE)) FUNCTION(NAME, set)(NAME* list, OWNER(TYPE) value, size_t index);
type_errno(OWNER(TYPE)) FUNCTION(NAME, remove)(NAME* list, size_t index);
type_errno(MUT_BORROW(TYPE*)) FUNCTION(NAME, get)(BORROW(NAME*) list, size_t index);
void FUNCTION(NAME, free)(NAME* list);
void FUNCTION(NAME, freeElements)(NAME* list);

#undef CONCAT
#undef FUNCTION
