// #define KEY ...
// #define VALUE ...

#define MAPS_CODE 
  size_t size = MAP->size;
  bool contains = MAP_FUN(contains)(MAP, KEY);
  
  if (contains) {
    TYPE value = *MAP_FUN(get)(MAP, KEY);
    TEST_ASSERT_EQUAL_INT(errno, 0);
    TYPE delValue = MAP_FUN(set)(MAP, KEY, VALUE);
    TEST_ASSERT_EQUAL_INT(errno, 1);
    MAP_EQUAL_N(value, delValue);
    TEST_ASSERT_EQUAL_SIZE_T(MAP->size, size);
  }
  else {
    TYPE* ptr = MAP_FUN(get)(MAP, KEY);
    TEST_ASSERT_EQUAL_INT(errno, 1);
    TEST_ASSERT_EQUAL_PTR(ptr, 0);
    MAP_FUN(set)(MAP, KEY, VALUE);
    TEST_ASSERT_EQUAL_SIZE_T(MAP->size, size+1);
  }

#include "tgen_maps.h"
#undef MAPS_CODE

