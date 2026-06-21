#include "viewstringlist.h"

#define NAME ViewStringList
#define TYPE ViewString
#define NULLV (ViewString){0}
#define FREEFUN ViewString_free
#define TYPEDEFS 1
#include "glist.c.h"
#undef NAME
#undef TYPE
#undef NULLV
#undef FREEFUN
#undef TYPEDEFS

bool ViewStringList_contains(ViewStringList* list, BORROW(ViewString) vs) {
  for (size_t i = 0; i < list->size; i++) {
    ViewString s = list->array[i];
    if (ViewStrings_equals(s, vs)) return true;
  }
  return false;
}
