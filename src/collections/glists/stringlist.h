#pragma once

#define NAME StringList
#define TYPE String
#define NULLV (String){0}
#define FREEFUN String_free
#define TYPEDEFS 1
#include "glist.h"
#undef NAME
#undef TYPE
#undef NULLV
#undef FREEFUN
#undef TYPEDEFS

#include "prints.h"
dec_prints(StringList);

bool StringList_contains(StringList* list, BORROW(ViewString) vs);
