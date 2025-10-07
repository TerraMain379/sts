#include "test_gmaps.h"

#include "unity.h"

#include "utils.h"
#include "allocator.h"
#include "string.h"

#include "map.h"
#include "intmap.h"
#include "strmap.h"

Map* mm;
IntMap* im;
StrMap* sm;

void test_gmaps_init() {
  #define MAPS_CODE                         \
    MAP = A_loc(sizeof(MAP_TYPE));          \
    MAP_FUN(init)(MAP);                     \
    TEST_ASSERT_EQUAL_SIZE_T(MAP->size, 0); \

  #include "tgen_maps.h"
  #undef MAPS_CODE
}
void test_gmaps_set_get1() {
  #define MAPS_CODE
    String key = String_const("key1");
    TEST_ASSERT_EQUAL_SIZE_T(MAP->size, 0);
    MAP_FUN(set)(MAP, key, MAP_SWITCH(
      0x123,
      0x123,
      String_const("0x123")
    ));
    TEST_ASSERT_EQUAL_SIZE_T(MAP->size, 1);

    TYPE* ptr = MAP_FUN(get)(MAP, key);
    TEST_ASSERT_EQUAL_INT(errno, 0);
    TYPE value = *ptr;


  #include "tgen_maps.h"
}

void test_gmaps() {
  
}
