// #define NAME ...
// #define TYPE ...

#define CONCAT(a, b) a ## _ ## b
#define FUNCTION(name, fun) CONCAT(name, fun)

typedef List NAME;

inline void FUNCTION(NAME, init)(NAME* list, size_t capacity) {
  List_init(list, capacity);
}
inline void FUNCTION(NAME, setCapacity)(NAME* list, size_t capacity) {
  List_setCapacity(list, capacity);
}
inline void FUNCTION(NAME, add)(NAME* list, TYPE value) {
  List_add(list, value);
}
inline void_errno FUNCTION(NAME, insert)(NAME* list, TYPE value, size_t index) {
  List_insert(list, value, index);
}
inline type_errno(TYPE) FUNCTION(NAME, set)(NAME* list, TYPE value, size_t index) {
  return (TYPE) List_set(list, value, index);
}
inline type_errno(TYPE) FUNCTION(NAME, remove)(NAME* list, size_t index) {
  return (TYPE) List_remove(list, index);
}
inline type_errno(TYPE*) FUNCTION(NAME, get)(NAME* list, size_t index) {
  return (TYPE*) List_get(list, index);
}
inline void FUNCTION(NAME, free)(NAME* list) {
  List_free(list);
}
