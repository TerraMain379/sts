#include "constmap.h"

#define NAME ConstMap
#define TYPE const void*
#define NULLV 0
#undef FREEFUN
#include "gmap.c.h"
#undef NAME
#undef TYPE
#undef NULLV
