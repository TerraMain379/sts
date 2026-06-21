#include "constlist.h"

#define NAME ConstList
#define TYPE const void*
#define NULLV 0
#undef FREEFUN
#define TYPEDEFS 1
#include "glist.c.h"
#undef NAME
#undef TYPE
#undef NULLV
#undef TYPEDEFS
