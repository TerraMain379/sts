#include "list.h"

#define TYPE void*
#define NAME List
#define NULLV 0
#define FREEFUN A_free
#define ISPOINTER true
#include "glist.c.h"
#undef TYPE
#undef NAME
#undef NULLV
#undef FREEFUN
#undef ISPOINTER
