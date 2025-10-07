#include "map.h"

#define TYPE void*
#define NAME Map
#define NULLV 0
#define FREEFUN A_free
#define ISPOINTER true
#include "gmap.c.h"
#undef TYPE
#undef NAME
#undef NULLV
#undef FREEFUN
#undef ISPOINTER
