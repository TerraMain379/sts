#include "map.h"

// #define PNAME ...
// #define PTYPE ...

#define CONCAT(a, b) a ## _ ## b
#define ELEMENT(name) CONCAT(name, element)
#define FUNCTION(name, fun) CONCAT(name, fun)

typedef Map PNAME;

inline void FUNCTION(PNAME, init)(Map* map) {
  Map_init(map);
}
inline ELEMENT(Map)* FUNCTION(PNAME, getElementByHash)(PNAME* map, int hash) {
  return Map_getElementByHash(map, hash);
}
inline ELEMENT(Map)* FUNCTION(PNAME, getElement)(PNAME* map, const String key) {
  return Map_getElement(map, key);
}
inline type_errno(PTYPE*) FUNCTION(PNAME, get)(PNAME* map, const String key) {
  return (PTYPE*) Map_get(map, key);
}
inline bool FUNCTION(PNAME, contains)(PNAME* map, const String key) {
  return Map_contains(map, key);
}
inline type_errno(PTYPE) FUNCTION(PNAME, set)(PNAME* map, const String key, PTYPE value) {
  return (PTYPE) Map_set(map, key, value);
}
inline type_errno(PTYPE) FUNCTION(PNAME, remove)(PNAME* map, const String key) {
  return (PTYPE) Map_remove(map, key);
}
inline void FUNCTION(PNAME, free)(PNAME* map) {
  Map_free(map);
}
