#define MAP_FUN(fun) _MAP_FUN(MAP_TYPE, fun)
#define _MAP_FUN(type, fun) __MAP_FUN(type, fun)
#define __MAP_FUN(type, fun) type ## _ ## fun

#define MAP_EQUAL_N(v1, v2) MAP_SWITCH(                   \
  TEST_ASSERT_EQUAL_PTR(v1, v2),                          \
  TEST_ASSERT_EQUAL_INT(v1, v2),                          \
  TEST_ASSERT_TRUE(Strings_equals(v1, v2))                \
)
#define MAP_EQUAL(v1, v2) MAP_SWITCH(                     \
  TEST_ASSERT_EQUAL_PTR(v1, v2),                          \
  TEST_ASSERT_EQUAL_INT(v1, v2),                          \
  TEST_ASSERT_TRUE(Strings_equals(v1, String_const(v2)))  \
)

#define MAP mm
#define MAP_TYPE Map
#define TYPE void*
#define MAP_SWITCH(v1, v2, v3) v1
{
  MAPS_CODE
}

#define MAP im
#define MAP_TYPE IntMap
#define TYPE int
#define MAP_SWITCH(v1, v2, v3) v2
{
  MAPS_CODE
}

#define MAP sm
#define MAP_TYPE StrMap
#define TYPE String
#define MAP_SWITCH(v1, v2, v3) v3
{
  MAPS_CODE
}
