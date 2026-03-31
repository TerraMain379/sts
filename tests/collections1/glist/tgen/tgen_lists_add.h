// this .h file is needed for generate tests for add elements v1, v2, v3 to all lists

// #define v1 ...
// #define v2 ...
// #define v3 "..."

#define LISTS_CODE                                    \
  size_t size = LIST->size;                           \
  LIST_FUN(add)(                                      \
    LIST, LIST_SWITCH(                                \
      (void*) v1,                                     \
      v2,                                             \
      String_const(v3)                                \
    )                                                 \
  );                                                  \
  TEST_ASSERT_EQUAL_SIZE_T(LIST->size, (size+1));     \

#include "tgen_lists.h"
#undef LISTS_CODE
