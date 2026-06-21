#pragma once

#define NAME StringMap
#define TYPE String
#define NULLV (String){0}
#define FREEFUN String_free
#define TYPEDEFS 1
#include "gmap.h"
#undef NAME
#undef TYPE
#undef NULLV
#undef FREEFUN
#undef TYPEDEFS

#include "prints.h"
dec_prints(StringMap);
