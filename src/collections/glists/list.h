#pragma once

#define NAME List
#define TYPE void*
#define NULLV 0
#undef FREEFUN
#define TYPEDEFS 1
#include "glist.h"
#undef NAME
#undef TYPE
#undef NULLV
#undef TYPEDEFS

#include "prints.h"
dec_prints(List);
