#pragma once

#define NAME ViewStringMap
#define TYPE ViewString
#define NULLV (ViewString){0}
#define FREEFUN ViewString_free
#define TYPEDEFS 1
#include "gmap.h"
#undef NAME
#undef TYPE
#undef NULLV
#undef FREEFUN
#undef TYPEDEFS

#include "prints.h"
dec_prints(ViewStringMap);
