#include "stringlist.h"

#define NAME StringList
#define TYPE String
#define NULLV (String){0}
#define FREEFUN String_free
#include "glist.c.h"
#undef NAME
#undef TYPE
#undef NULLV
#undef FREEFUN

bool StringList_contains(StringList* list, BORROW(ViewString) vs) {
  for (size_t i = 0; i < list->size; i++) {
    String s = list->array[i];
    if (ViewStrings_equals(ViewString_by(s), vs)) return true;
  }
  return false;
}
