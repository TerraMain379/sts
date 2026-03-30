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
static inline ELEMENT(PNAME)* FUNCTION(PNAME, getElementByHash)(PNAME* map, int hash) {
  return FUNCTION(BASE_MAP, getElementByHash)(map, hash);
}
static inline ELEMENT(PNAME)* FUNCTION(PNAME, getElement)(PNAME* map, const ViewString* key) {
  return FUNCTION(BASE_MAP, getElement)(map, key);
}
static inline type_errno(MUT_WEAK(PTYPE)) FUNCTION(PNAME, get)(PNAME* map, const ViewString* key) {
  return (MUT_WEAK(PTYPE)) FUNCTION(BASE_MAP, get)(map, key);
}
static inline bool FUNCTION(PNAME, contains)(PNAME* map, const ViewString* key) {
  return FUNCTION(BASE_MAP, contains)(map, key);
}
static inline type_errno(PTYPE) FUNCTION(PNAME, set)(PNAME* map, const ViewString* key, PTYPE value) {
  return (PTYPE) FUNCTION(BASE_MAP, set)(map, key, value);
}
static inline type_errno(PTYPE) FUNCTION(PNAME, remove)(PNAME* map, const ViewString* key) {
  return (PTYPE) FUNCTION(BASE_MAP, remove)(map, key);
}
static inline void FUNCTION(PNAME, free)(PNAME* map) {
  FUNCTION(BASE_MAP, free)(map);
}
void FUNCTION(PNAME, freeElements)(PNAME* map);
