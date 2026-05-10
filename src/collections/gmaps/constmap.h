#pragma once

#define NAME ConstMap
#define TYPE const void*
#define NULLV 0
#undef FREEFUN
#include "gmap.h"
#undef NAME
#undef TYPE
#undef NULLV

dec_print(ConstMap);
