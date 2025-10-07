#include "test_glists.h"

#include "unity.h"

#include "utils.h"
#include "allocator.h"
#include "string.h"

#include "list.h"
#include "intlist.h"
#include "strlist.h"


List* ll;
IntList* il;
StrList* sl;


void test_glists_init() {
  #define LISTS_CODE                                      \
    LIST = A_loc(sizeof(LIST_TYPE));                      \
    LIST_FUN(init)(LIST, 2);                              \
    TEST_ASSERT_EQUAL_SIZE_T(LIST->size, 0);              \
    TEST_ASSERT_EQUAL_SIZE_T(LIST->capacity, 2);          \

  #include "tgen_lists.h"
  #undef LISTS_CODE
}

void test_glists_add1() {
  #define v1 0x123B
  #define v2 0x123B
  #define v3 "123B"
  #include "tgen_lists_add.h"
}
void test_glists_get1() {
  #define index 0
  #include "tgen_lists_get.h"
  #undef v1
  #undef v2
  #undef v3
}

void test_glists_add2() {
  #define v1 0x321C
  #define v2 0x321C
  #define v3 "321C"
  #include "tgen_lists_add.h"
}
void test_glists_get2() {
  #define index 1
  #include "tgen_lists_get.h"
  #undef v1
  #undef v2
  #undef v3
}

void test_glists_add3_for_capacity() {
  #define v1 0x59110
  #define v2 0x59110
  #define v3 "Hello"
  #include "tgen_lists_add.h"
}
void test_glists_get3_for_capacity() {
  #define index 2
  #include "tgen_lists_get.h"
  #undef v1
  #undef v2
  #undef v3
}

void test_glists_insert_at_begin() {
  #define LISTS_CODE                                                \
    size_t prevSize = LIST->size;                                   \
    TYPE* ptr1;                                                     \
    TYPE* ptr2;                                                     \
    TYPE* ptr3;                                                     \
                                                                    \
    ptr1 = LIST_FUN(get)(LIST, 0);                                  \
    TEST_ASSERT_NOT_NULL(ptr1);                                     \
    TEST_ASSERT_EQUAL_INT(errno, 0);                                \
    TYPE e1 = *ptr1;                                                \
                                                                    \
    ptr2 = LIST_FUN(get)(LIST, 1);                                  \
    TEST_ASSERT_NOT_NULL(ptr2);                                     \
    TEST_ASSERT_EQUAL_INT(errno, 0);                                \
    TYPE e2 = *ptr2;                                                \
                                                                    \
    LIST_FUN(insert)(                                               \
      LIST, LIST_SWITCH(                                            \
        (void*) 0x25,                                               \
        0x25,                                                       \
        String_const("0x25")                                        \
      ), 0                                                          \
    );                                                              \
    TEST_ASSERT_EQUAL_SIZE_T(LIST->size, prevSize + 1);             \
    ptr1 = LIST_FUN(get)(LIST, 0);                                  \
    ptr2 = LIST_FUN(get)(LIST, 1);                                  \
    ptr3 = LIST_FUN(get)(LIST, 2);                                  \
    TEST_ASSERT_EQUAL_INT(errno, 0);                                \
    TEST_ASSERT_EQUAL_INT(errno, 0);                                \
    TEST_ASSERT_EQUAL_INT(errno, 0);                                \
    TYPE v1 = *ptr1;                                                \
    TYPE v2 = *ptr2;                                                \
    TYPE v3 = *ptr3;                                                \
    LIST_SWITCH(                                                    \
      TEST_ASSERT_EQUAL_PTR(e1, v2),                                \
      TEST_ASSERT_EQUAL_INT(e1, v2),                                \
      TEST_ASSERT_TRUE(Strings_equals(e1, v2))                      \
    );                                                              \
    LIST_SWITCH(                                                    \
      TEST_ASSERT_EQUAL_PTR(e2, v3),                                \
      TEST_ASSERT_EQUAL_INT(e2, v3),                                \
      TEST_ASSERT_TRUE(Strings_equals(e2, v3))                      \
    );                                                              \
    LIST_SWITCH(                                                    \
      TEST_ASSERT_EQUAL_PTR(v1, (void*) 0x25),                      \
      TEST_ASSERT_EQUAL_INT(v1, 0x25),                              \
      TEST_ASSERT_TRUE(Strings_equals(v1, String_const("0x25")))    \
    );                                                              \

  #include "tgen_lists.h"
  #undef LISTS_CODE
}

void test_glists_insert_after_end() {
  #define LISTS_CODE                                  \
    TYPE value = LIST_SWITCH(                         \
      (void*) 999,                                    \
      999,                                            \
      String_const("nine nine nine")                  \
    );                                                \
    size_t size = LIST->size;                         \
    LIST_FUN(insert)(LIST, value, size);              \
    TEST_ASSERT_NOT_NULL(errno);                      \
    TEST_ASSERT_EQUAL_INT(LIST->size, size);          \
    LIST_FUN(insert)(LIST, value, size + 2);          \
    TEST_ASSERT_NOT_NULL(errno);                      \
    TEST_ASSERT_EQUAL_INT(LIST->size, size);          \
  
  #include "tgen_lists.h"
  #undef LISTS_CODE
}
void test_glists_add_10els() {
  size_t size = ll->size;
  TEST_ASSERT_EQUAL_SIZE_T(size, il->size);
  TEST_ASSERT_EQUAL_SIZE_T(size, sl->size);

  #define v1 10
  #define v2 10
  #define v3 "A"

  for (size_t i = 0; i < 10; i++) {
    #include "tgen_lists_add.h"
  }

  #define LISTS_CODE TEST_ASSERT_EQUAL_SIZE_T(size+10, LIST->size);
  #include "tgen_lists.h"
  #undef LISTS_CODE

  for (size_t i = size; i < size + 10; i++) {
    #define index i
    #include "tgen_lists_get.h"
  }

  #undef v1
  #undef v2
  #undef v3
}

void test_glists_insert_in_middle1() {
  #define index 2
  #define checkNext2
  #define v1 600
  #define v2 600
  #define v3 "6-0-0"
  #include "tgen_lists_insert.h"
  #undef index
  #undef checkNext2
}
void test_glists_insert_in_middle2() {
  #define index 5
  #define checkNext2
  #define v1 700
  #define v2 700
  #define v3 "7-0-0"
  #include "tgen_lists_insert.h"
  #undef index
  #undef checkNext2
}

void test_glists_remove_at_end() {
  #define LISTS_CODE                                    \
    size_t size = LIST->size;                           \
    TYPE* ptr = LIST_FUN(get)(LIST, size-1);            \
    TEST_ASSERT_EQUAL_INT(errno, 0);                    \
    TYPE value = *ptr;                                  \
                                                        \
    TYPE delValue = LIST_FUN(remove)(LIST, size-1);     \
    TEST_ASSERT_EQUAL_INT(errno, 0);                    \
    LIST_EQUAL_N(value, delValue);                      \
    TEST_ASSERT_EQUAL_SIZE_T(LIST->size, size-1);       \

  #include "tgen_lists.h"
  #undef LISTS_CODE
}

void test_glists_remove_at_begin() {
  #define LISTS_CODE                                    \
    size_t size = LIST->size;                           \
    TYPE* ptr = LIST_FUN(get)(LIST, 0);                 \
    TEST_ASSERT_EQUAL_INT(errno, 0);                    \
    TYPE value = *ptr;                                  \
                                                        \
    TYPE delValue = LIST_FUN(remove)(LIST, 0);          \
    TEST_ASSERT_EQUAL_INT(errno, 0);                    \
    LIST_EQUAL_N(value, delValue);                      \
    TEST_ASSERT_EQUAL_SIZE_T(LIST->size, size-1);       \

  #include "tgen_lists.h"
  #undef LISTS_CODE
}

void test_glists_remove_in_middle1() {
  #define index 2
  #include "tgen_lists_remove.h"
  #undef index
}
void test_glists_remove_in_middle2() {
  #define index 4
  #include "tgen_lists_remove.h"
  #undef index
}
void test_glists_remove_in_middle3() {
  #define index 3
  #include "tgen_lists_remove.h"
  #undef index

  #define index 3
  #include "tgen_lists_remove.h"
  #undef index

  #define index 7
  #include "tgen_lists_remove.h"
  #undef index
}

void test_glists_remove_after_end() {
  #define LISTS_CODE                          \
    size_t size = LIST->size;                 \
    LIST_FUN(remove)(LIST, size);             \
    TEST_ASSERT_NOT_NULL(errno);              \
    TEST_ASSERT_EQUAL_INT(LIST->size, size);  \
                                              \
    LIST_FUN(remove)(LIST, size + 2);         \
    TEST_ASSERT_NOT_NULL(errno);              \
    TEST_ASSERT_EQUAL_INT(LIST->size, size);  \

  #include "tgen_lists.h"
  #undef LISTS_CODE
}

void test_glists() {
  RUN_TEST(test_glists_init);
  RUN_TEST(test_glists_add1);
  RUN_TEST(test_glists_get1);
  RUN_TEST(test_glists_add2);
  RUN_TEST(test_glists_get2);
  RUN_TEST(test_glists_add3_for_capacity);
  RUN_TEST(test_glists_get3_for_capacity);
  RUN_TEST(test_glists_insert_at_begin);
  RUN_TEST(test_glists_add_10els);
  RUN_TEST(test_glists_insert_after_end);
  RUN_TEST(test_glists_insert_in_middle1);
  RUN_TEST(test_glists_insert_in_middle2);
  RUN_TEST(test_glists_remove_at_end);
  RUN_TEST(test_glists_remove_at_begin);
  RUN_TEST(test_glists_remove_in_middle1);
  RUN_TEST(test_glists_remove_in_middle2);
  RUN_TEST(test_glists_remove_in_middle3);
  RUN_TEST(test_glists_remove_after_end);
}
