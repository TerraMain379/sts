#pragma once

#define NAME IntMap
#define TYPE int
#define NULLV 0
#undef FREEFUN
#define TYPEDEFS 1
#include "gmap.h"
#undef NAME
#undef TYPE
#undef NULLV
#undef TYPEDEFS

#include "prints.h"
dec_prints(IntMap);
