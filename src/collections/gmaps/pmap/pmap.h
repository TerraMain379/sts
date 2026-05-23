#include "utils.h"

// #define PNAME ...
// #define PTYPE ... (only pointer)
// #define PFREEFUN ...
// #define BASE_MAP ... (Map / ConstMap)

#define CONCAT(a, b) a ## _ ## b
#define ELEMENT(name) CONCAT(name, element)
#define FUNCTION(name, fun) CONCAT(name, fun)

typedef BASE_MAP PNAME;
typedef ELEMENT(BASE_MAP) ELEMENT(PNAME);

static inline void FUNCTION(PNAME, init)(PNAME* map) {
  FUNCTION(BASE_MAP, init)(map);
}
static inline BORROW(ELEMENT(PNAME)*) FUNCTION(PNAME, getElementByHash)(BORROW(PNAME*) map, int hash) {
  return FUNCTION(BASE_MAP, getElementByHash)(map, hash);
}
static inline BORROW(ELEMENT(PNAME)*) FUNCTION(PNAME, getElement)(BORROW(PNAME*) map, BORROW(ViewString) key) {
  return FUNCTION(BASE_MAP, getElement)(map, key);
}
static inline type_errno(PTYPE*) FUNCTION(PNAME, get)(BORROW(PNAME*) map, BORROW(ViewString) key) {
  PTYPE** ptr = (PTYPE**) FUNCTION(BASE_MAP, get)(map, key);
  if (ptr == 0) {
    errno = 1;
    return 0;
  }
  errno = 0;
  return *ptr;
}
static inline bool FUNCTION(PNAME, contains)(BORROW(PNAME*) map, BORROW(ViewString) key) {
  return FUNCTION(BASE_MAP, contains)(map, key);
}
static inline type_errno(PTYPE*) FUNCTION(PNAME, set)(PNAME* map, BORROW(ViewString) key, OWNER(PTYPE*) value) {
  return (PTYPE*) FUNCTION(BASE_MAP, set)(map, key, value);
}
static inline type_errno(PTYPE*) FUNCTION(PNAME, remove)(PNAME* map, BORROW(ViewString) key) {
  return (PTYPE*) FUNCTION(BASE_MAP, remove)(map, key);
}
static inline void FUNCTION(PNAME, free)(PNAME* map) {
  FUNCTION(BASE_MAP, free)(map);
}
void FUNCTION(PNAME, freeElements)(PNAME* map);
