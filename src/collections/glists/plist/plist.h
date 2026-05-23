#include "utils.h"

// #define PNAME ...
// #define PTYPE ...
// #define PFREEFUN ...
// #define BASE_LIST ...

#define CONCAT(a, b) a ## _ ## b
#define FUNCTION(name, fun) CONCAT(name, fun)

typedef BASE_LIST PNAME;

static inline void FUNCTION(PNAME, init)(PNAME* list, size_t capacity) {
  FUNCTION(BASE_LIST, init)(list, capacity);
}
static inline void FUNCTION(PNAME, setCapacity)(PNAME* list, size_t capacity) {
  FUNCTION(BASE_LIST, setCapacity)(list, capacity);
}
static inline PTYPE* FUNCTION(PNAME, add)(PNAME* list, OWNER(PTYPE*) value) {
  return (PTYPE*) *FUNCTION(BASE_LIST, add)(list, value);
}
static inline void_errno FUNCTION(PNAME, insert)(PNAME* list, OWNER(PTYPE*) value, size_t index) {
  FUNCTION(BASE_LIST, insert)(list, value, index);
}
static inline type_errno(PTYPE*) FUNCTION(PNAME, set)(PNAME* list, OWNER(PTYPE*) value, size_t index) {
  return (PTYPE*) FUNCTION(BASE_LIST, set)(list, value, index);
}
static inline type_errno(PTYPE*) FUNCTION(PNAME, remove)(PNAME* list, size_t index) {
  return (PTYPE*) FUNCTION(BASE_LIST, remove)(list, index);
}
static inline type_errno(PTYPE*) FUNCTION(PNAME, get)(BORROW(PNAME*) list, size_t index) {
  return (PTYPE*) *FUNCTION(BASE_LIST, get)(list, index);
}
static inline void FUNCTION(PNAME, free)(PNAME* list) {
  FUNCTION(BASE_LIST, free)(list);
}
void FUNCTION(PNAME, freeElements)(PNAME* list);
