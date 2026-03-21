#pragma once

#define NAME ViewStringMap
#define TYPE ViewString
#define NULLV (ViewString){0}
#define FREEFUN ViewString_free
#include "gmap.h"
#undef NAME
#undef TYPE
#undef NULLV
#undef FREEFUN
