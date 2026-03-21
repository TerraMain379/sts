#pragma once

#define NAME StringList
#define TYPE String
#define NULLV (String){0}
#define FREEFUN String_free
#include "glist.h"
#undef NAME
#undef TYPE
#undef NULLV
#undef FREEFUN
