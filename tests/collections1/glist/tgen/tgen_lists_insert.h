// #define index n
// #define/undef checkNext2
// #define v1 ...
// #define v2 ...
// #define v3 ...
// #include "tgen_lists_insert.h"
// #undef index
// #undef checkNext2
// #undef v1
// #undef v2
// #undef v3

#define LISTS_CODE                                      \
  size_t size = LIST->size;                             \
  TYPE* prevPtr = LIST_FUN(get)(LIST, index - 1);       \
  TEST_ASSERT_EQUAL_INT(errno, 0);                      \
  TYPE* currPtr = LIST_FUN(get)(LIST, index);           \
  TEST_ASSERT_EQUAL_INT(errno, 0);                      \
  TYPE prev = *prevPtr;                                 \
  TYPE curr = *currPtr;                                 \
                                                        \
  TYPE value = LIST_SWITCH(                             \
    (void*) v1,                                         \
    v2,                                                 \
    String_const(v3)                                    \
  );                                                    \
  LIST_FUN(insert)(LIST, value, index);                 \
  TEST_ASSERT_EQUAL_SIZE_T(LIST->size, (size+1));       \
                                                        \
  prevPtr = LIST_FUN(get)(LIST, index - 1);             \
  TEST_ASSERT_EQUAL_INT(errno, 0);                      \
  currPtr = LIST_FUN(get)(LIST, index);                 \
  TEST_ASSERT_EQUAL_INT(errno, 0);                      \
  TYPE* nextPtr = LIST_FUN(get)(LIST, index + 1);       \
  TEST_ASSERT_EQUAL_INT(errno, 0);                      \
                                                        \
  LIST_EQUAL_N(prev, *prevPtr);                         \
  LIST_EQUAL_N(curr, *nextPtr);                         \
  LIST_EQUAL_N(*currPtr, value);                        \

#include "tgen_lists.h"
#undef LISTS_CODE
