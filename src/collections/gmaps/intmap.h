#pragma once

#define NAME IntMap
#define TYPE int
#define NULLV 0
#undef FREEFUN
#include "gmap.h"
#undef NAME
#undef TYPE
#undef NULLV

#include "prints.h"
dec_prints(IntMap);
