// #define LISTS_CODE LIST = malloc(sizeof(LIST_TYPE)); \
//   LIST_FUN(init)(LIST, 2);
// #include "tgen_lists.h"
// #undef LISTS_CODE

#define LIST_FUN(fun) _LIST_FUN(LIST_TYPE, fun)
#define _LIST_FUN(type, fun) __LIST_FUN(type, fun)
#define __LIST_FUN(type, fun) type ## _ ## fun

#define LIST_EQUAL_N(v1, v2) LIST_SWITCH(                 \
  TEST_ASSERT_EQUAL_PTR(v1, v2),                          \
  TEST_ASSERT_EQUAL_INT(v1, v2),                          \
  TEST_ASSERT_TRUE(Strings_equals(v1, v2))                \
)
#define LIST_EQUAL(v1, v2) LIST_SWITCH(                   \
  TEST_ASSERT_EQUAL_PTR(v1, v2),                          \
  TEST_ASSERT_EQUAL_INT(v1, v2),                          \
  TEST_ASSERT_TRUE(Strings_equals(v1, String_const(v2)))  \
)

#define LIST ll
#define LIST_TYPE List
#define TYPE void*
#define LIST_SWITCH(v1, v2, v3) v1
{
  LISTS_CODE
}

#define LIST il
#define LIST_TYPE IntList
#define TYPE int
#define LIST_SWITCH(v1, v2, v3) v2
{
  LISTS_CODE
}

#define LIST sl
#define LIST_TYPE StrList
#define TYPE String
#define LIST_SWITCH(v1, v2, v3) v3
{
  LISTS_CODE
}

#undef LIST
#undef LIST_TYPE

