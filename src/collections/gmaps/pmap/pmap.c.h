// #define PNAME ...
// #define PTYPE ... (only pointer)
// #define PFREEFUN ...
// #define BASE_MAP ... (Map / ConstMap)

#define CONCAT(a, b) a ## _ ## b
#define ELEMENT(name) CONCAT(name, element)
#define FUNCTION(name, fun) CONCAT(name, fun)

void FUNCTION(PNAME, freeElements)(PNAME* map) {
  #ifdef PFREEFUN
    ELEMENT(PNAME)* element = map->first;
    while (element) {
      PFREEFUN(element->value);
      element = element->next;
    }
  #endif
}
