#include "strlist.h"

#define TYPE String
#define NAME StrList
#define NULLV (String){0}
#define FREEFUN String_free
#undef ISPOINTER
#include "glist.c.h"
#undef TYPE
#undef NAME
#undef NULLV
#undef FREEFUN
#undef ISPOINTER
