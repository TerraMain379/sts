#include "list.h"

#define NAME List
#define TYPE void*
#define NULLV 0
#undef FREEFUN
#define TYPEDEFS 1
#include "glist.c.h"
#undef NAME
#undef TYPE
#undef NULLV
#undef TYPEDEFS
