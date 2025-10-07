// #define index n
// #include "tgen_lists_remove.h"
// #undef index

#define LISTS_CODE                                      \
  size_t size = LIST->size;                             \
  TYPE* prevPtr = LIST_FUN(get)(LIST, index - 1);       \
  TEST_ASSERT_EQUAL_INT(errno, 0);                      \
  TYPE* currPtr = LIST_FUN(get)(LIST, index);           \
  TEST_ASSERT_EQUAL_INT(errno, 0);                      \
  TYPE* nextPtr = LIST_FUN(get)(LIST, index + 1);       \
  TEST_ASSERT_EQUAL_INT(errno, 0);                      \
  TYPE prev = *prevPtr;                                 \
  TYPE curr = *currPtr;                                 \
  TYPE next = *nextPtr;                                 \
                                                        \
  TYPE delValue = LIST_FUN(remove)(LIST, index);        \
  TEST_ASSERT_EQUAL_SIZE_T(LIST->size, size - 1);       \
                                                        \
  prevPtr = LIST_FUN(get)(LIST, index - 1);             \
  TEST_ASSERT_EQUAL_INT(errno, 0);                      \
  currPtr = LIST_FUN(get)(LIST, index);                 \
  TEST_ASSERT_EQUAL_INT(errno, 0);                      \
  TYPE newPrev = *prevPtr;                              \
  TYPE newCurr = *currPtr;                              \
                                                        \
  LIST_EQUAL_N(prev, newPrev);                          \
  LIST_EQUAL_N(curr, delValue);                         \
  LIST_EQUAL_N(next, newCurr);                          \

#include "tgen_lists.h"
#undef LISTS_CODE
