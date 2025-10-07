#pragma once

#define TYPE void*
#define NAME List
#define NULLV 0
#define FREEFUN A_free
#define ISPOINTER true
#include "glist.h"
#undef TYPE
#undef NAME
#undef NULLV
#undef FREEFUN
#undef ISPOINTER
