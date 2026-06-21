#include "intmap.h"

#define NAME IntMap
#define TYPE int
#define NULLV 0
#undef FREEFUN
#define TYPEDEFS 1
#include "gmap.c.h"
#undef NAME
#undef TYPE
#undef NULLV
#undef TYPEDEFS
