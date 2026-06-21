#include "map.h"

#define NAME Map
#define TYPE void*
#define NULLV 0
#undef FREEFUN
#define TYPEDEFS 1
#include "gmap.c.h"
#undef NAME
#undef TYPE
#undef NULLV
#undef TYPEDEFS
