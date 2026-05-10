// #define PNAME ...
// #define PTYPE ...
// #define PFREEFUN ...
// #define BASE_LIST ...

#define CONCAT(a, b) a ## _ ## b
#define FUNCTION(name, fun) CONCAT(name, fun)

void FUNCTION(PNAME, freeElements)(PNAME* list) {
  #ifdef PFREEFUN
    for (size_t i = 0; i < list->size; i++) {
      PFREEFUN(list->array[i]);
      A_free(list->array[i]);
    }
  #endif
}
