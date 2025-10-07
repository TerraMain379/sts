#include "strmap.h"

#define TYPE String
#define NAME StrMap
#define NULLV (String){0}
#define FREEFUN String_free
#undef ISPOINTER
#include "gmap.c.h"
#undef TYPE
#undef NAME
#undef NULLV
#undef FREEFUN
#undef ISPOINTER
