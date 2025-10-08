#include "list.h"

// #define PNAME ...
// #define PTYPE ...

#define CONCAT(a, b) a ## _ ## b
#define FUNCTION(name, fun) CONCAT(name, fun)

typedef List PNAME;

inline void FUNCTION(PNAME, init)(PNAME* list, size_t capacity) {
  List_init(list, capacity);
}
inline void FUNCTION(PNAME, setCapacity)(PNAME* list, size_t capacity) {
  List_setCapacity(list, capacity);
}
inline void FUNCTION(PNAME, add)(PNAME* list, PTYPE value) {
  List_add(list, value);
}
inline void_errno FUNCTION(PNAME, insert)(PNAME* list, PTYPE value, size_t index) {
  List_insert(list, value, index);
}
inline type_errno(PTYPE) FUNCTION(PNAME, set)(PNAME* list, PTYPE value, size_t index) {
  return (PTYPE) List_set(list, value, index);
}
inline type_errno(PTYPE) FUNCTION(PNAME, remove)(PNAME* list, size_t index) {
  return (PTYPE) List_remove(list, index);
}
inline type_errno(PTYPE*) FUNCTION(PNAME, get)(PNAME* list, size_t index) {
  return (PTYPE*) List_get(list, index);
}
inline void FUNCTION(PNAME, free)(PNAME* list) {
  List_free(list);
}
