#include "unity.h"

#include "map.h"
#include "strmap.h"
#include "allocator.h"
#include <errno.h>

struct Map* map;
void test_map_init() {
  Map_init(map);
  TEST_ASSERT_EQUAL_UINT64((uint64_t) map->size, (uint64_t)(size_t) 0);
  TEST_ASSERT_EQUAL_PTR(map->first, 0);
  TEST_ASSERT_EQUAL_PTR(map->last, 0);
}
void test_map_set1() {
  Map_set(map, String_const("key123"), (void*) 0x01567);
  TEST_ASSERT_EQUAL_UINT64((uint64_t) map->size, (uint64_t)(size_t) 1);
  TEST_ASSERT_NOT_NULL(map->first);
  TEST_ASSERT_NOT_NULL(map->last);
}
void test_map_get1() {
  void* value = Map_get(map, String_const("key123"));
  TEST_ASSERT_EQUAL_PTR(value, (void*) 0x01567);
}
void test_map_nullget1() {
  void* value = Map_get(map, String_const("h2so4"));
  TEST_ASSERT_EQUAL_PTR(value, 0);
}
void test_map_free() {
  Map_free(map);
  TEST_ASSERT_EQUAL_UINT64((uint64_t) map->size, (uint64_t)(size_t) 0);
  TEST_ASSERT_EQUAL_PTR(map->first, 0);
  TEST_ASSERT_EQUAL_PTR(map->last, 0);
}

void test_map_get_empty_returns_null() {
  void* value = Map_get(map, String_const("absent"));
  TEST_ASSERT_NOT_EQUAL(0, errno);
  TEST_ASSERT_EQUAL_PTR(value, 0);
}
void test_map_set_duplicate_updates_value_and_size_constant() {
  Map_set(map, String_const("dup"), (void*) 0x1);
  TEST_ASSERT_EQUAL_UINT64((uint64_t) map->size, (uint64_t)(size_t) 2);
  TEST_ASSERT_EQUAL_PTR(Map_get(map, String_const("dup")), (void*) 0x1);
  Map_set(map, String_const("dup"), (void*) 0x2);
  TEST_ASSERT_EQUAL_UINT64((uint64_t) map->size, (uint64_t)(size_t) 2);
  TEST_ASSERT_EQUAL_PTR(Map_get(map, String_const("dup")), (void*) 0x2);
}
void test_map_set_multiple_and_get_each() {
  Map_set(map, String_const("a"), (void*) 0xA);
  Map_set(map, String_const("b"), (void*) 0xB);
  Map_set(map, String_const("c"), (void*) 0xC);
  TEST_ASSERT_TRUE(Map_get(map, String_const("x")) == 0);
  TEST_ASSERT_EQUAL_PTR(Map_get(map, String_const("a")), (void*) 0xA);
  TEST_ASSERT_EQUAL_PTR(Map_get(map, String_const("b")), (void*) 0xB);
  TEST_ASSERT_EQUAL_PTR(Map_get(map, String_const("c")), (void*) 0xC);
}
void test_map_remove_nonexistent_returns_false_and_no_change() {
  size_t oldSize = map->size;
  errno = 0;
  Map_remove(map, String_const("zzz"));
  TEST_ASSERT_NOT_EQUAL(0, errno);
  TEST_ASSERT_EQUAL_UINT64((uint64_t) map->size, (uint64_t) oldSize);
}
void test_map_remove_existing_from_middle() {
  Map_set(map, String_const("k1"), (void*) 0x11);
  Map_set(map, String_const("k2"), (void*) 0x22);
  Map_set(map, String_const("k3"), (void*) 0x33);
  size_t sizeBefore = map->size;
  errno = 0;
  Map_remove(map, String_const("k2"));
  TEST_ASSERT_EQUAL_INT(0, errno);
  TEST_ASSERT_EQUAL_UINT64((uint64_t) map->size, (uint64_t)(sizeBefore - 1));
  TEST_ASSERT_EQUAL_PTR(Map_get(map, String_const("k2")), 0);
  TEST_ASSERT_EQUAL_PTR(Map_get(map, String_const("k1")), (void*) 0x11);
  TEST_ASSERT_EQUAL_PTR(Map_get(map, String_const("k3")), (void*) 0x33);
}
void test_map_set_empty_key_and_get() {
  Map_set(map, String_const(""), (void*) 0xEE, false);
  TEST_ASSERT_EQUAL_PTR(Map_get(map, String_const("")), (void*) 0xEE);
}
void test_map_set_null_value_increases_size_and_removable() {
  size_t sizeBefore = map->size;
  Map_set(map, String_const("nullv"), 0, false);
  TEST_ASSERT_EQUAL_UINT64((uint64_t) map->size, (uint64_t)(sizeBefore + 1));
  Map_remove(map, String_const("nullv"));
}

void testing_map() {
  map = A_loc(sizeof(struct Map));

  RUN_TEST(test_map_init);
  RUN_TEST(test_map_get_empty_returns_null);
  RUN_TEST(test_map_set1);
  RUN_TEST(test_map_get1);
  RUN_TEST(test_map_nullget1);
  RUN_TEST(test_map_set_duplicate_updates_value_and_size_constant);
  RUN_TEST(test_map_set_multiple_and_get_each);
  RUN_TEST(test_map_remove_nonexistent_returns_false_and_no_change);
  RUN_TEST(test_map_remove_existing_from_middle);
  RUN_TEST(test_map_set_empty_key_and_get);
  RUN_TEST(test_map_set_null_value_increases_size_and_removable);
  RUN_TEST(test_map_free);
  

  A_free(map);
}

void gmaps() {
  testing_map();
}
