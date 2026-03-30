#include "constlist.h"

#define NAME ConstList
#define TYPE const void*
#define NULLV 0
#undef FREEFUN
#include "glist.c.h"
#undef NAME
#undef TYPE
#undef NULLV
