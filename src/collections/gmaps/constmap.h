#pragma once

#define NAME ConstMap
#define TYPE const void*
#define NULLV 0
#undef FREEFUN
#include "gmap.h"
#undef NAME
#undef TYPE
#undef NULLV

#include "prints.h"
dec_prints(ConstMap);
