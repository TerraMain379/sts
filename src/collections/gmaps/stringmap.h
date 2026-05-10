#pragma once

#define NAME StringMap
#define TYPE String
#define NULLV (String){0}
#define FREEFUN String_free
#include "gmap.h"
#undef NAME
#undef TYPE
#undef NULLV
#undef FREEFUN

dec_print(StringMap);
