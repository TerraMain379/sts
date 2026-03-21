#include "viewstringlist.h"

#define NAME ViewStringList
#define TYPE ViewString
#define NULLV (ViewString){0}
#define FREEFUN ViewString_free
#include "glist.c.h"
#undef NAME
#undef TYPE
#undef NULLV
#undef FREEFUN
