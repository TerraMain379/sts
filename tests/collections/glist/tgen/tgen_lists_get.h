// this .h file is needed for generate tests for get elements v1, v2, v3 to all lists

// #define v1 ...
// #define v2 ...
// #define v3 "..."
// #define index n

#define LISTS_CODE                                                    \
  TYPE* ptr = LIST_FUN(get)(LIST, index);                             \
  TEST_ASSERT_NOT_NULL(ptr);                                          \
  TEST_ASSERT_EQUAL_INT(errno, 0);                                    \
  TYPE value = *ptr;                                                  \
  LIST_EQUAL(value, LIST_SWITCH(v1,v2,v3));                           \

#include "tgen_lists.h"
#undef LISTS_CODE
