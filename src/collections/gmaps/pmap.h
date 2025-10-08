// #define NAME ...
// #define TYPE ...

#define __NAME(name) _ ## name
#define _NAME(name) __NAME(name)
#define CONCAT(a, b) a ## _ ## b
#define _CONCAT(a, b) _ ## a ## _ ## b
#define ELEMENT(name) CONCAT(name, element)
#define _ELEMENT(name) _CONCAT(name, element)
#define FUNCTION(name, fun) CONCAT(name, fun)

typedef NAME Map;

inline void FUNCTION(NAME, init)(Map* map) {
  Map_init(map);
}
inline ELEMENT(NAME)* FUNCTION(NAME, getElementByHash)(NAME* map, int hash) {
  return Map_getElementByHash(map, hash);
}
inline ELEMENT(NAME)* FUNCTION(NAME, getElement)(NAME* map, const String key) {
  return Map_getElement(map, key);
}
inline type_errno(TYPE*) FUNCTION(NAME, get)(NAME* map, const String key) {
  return (TYPE*) Map_get(map, key);
}
inline bool FUNCTION(NAME, contains)(NAME* map, const String key) {
  return Map_contains(map, key);
}
inline type_errno(TYPE) FUNCTION(NAME, set)(NAME* map, const String key, TYPE value) {
  return (TYPE) Map_set(map, key, value);
}
inline type_errno(TYPE) FUNCTION(NAME, remove)(NAME* map, const String key) {
  return (TYPE) Map_remove(map, key);
}
inline void FUNCTION(NAME, free)(NAME* map) {
  Map_free(map);
}
