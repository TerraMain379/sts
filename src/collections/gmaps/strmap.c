#include "strmap.h"

#define NAME StrMap
#define TYPE String
#define NULLV (String){0}
#include "gmap.c.h"
#undef NAME
#undef TYPE
#undef NULLV
