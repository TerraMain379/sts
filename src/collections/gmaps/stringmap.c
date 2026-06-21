#include "stringmap.h"

#define NAME StringMap
#define TYPE String
#define NULLV (String){0}
#define FREEFUN String_free
#define TYPEDEFS 1
#include "gmap.c.h"
#undef NAME
#undef TYPE
#undef NULLV
#undef FREEFUN
#undef TYPEDEFS
