#pragma once

#define NAME IntList
#define TYPE int
#define NULLV 0
#undef FREEFUN
#define TYPEDEFS 1
#include "glist.h"
#undef NAME
#undef TYPE
#undef NULLV
#undef TYPEDEFS

#include "prints.h"
dec_prints(IntList);
