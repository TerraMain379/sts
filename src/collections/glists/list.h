#pragma once

#define NAME List
#define TYPE void*
#define NULLV 0
#undef FREEFUN
#include "glist.h"
#undef NAME
#undef TYPE
#undef NULLV

dec_print(List);
