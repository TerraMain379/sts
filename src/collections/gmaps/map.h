#pragma once

#define NAME Map
#define TYPE void*
#define NULLV 0
#undef FREEFUN
#include "gmap.h"
#undef NAME
#undef TYPE
#undef NULLV

#include "prints.h"
dec_prints(Map);
