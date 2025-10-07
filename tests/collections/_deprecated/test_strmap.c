#include "unity.h"

#include "strmap.h"
#include "strings.h"
#include "allocator.h"
#include <errno.h>

static struct StrMap* smap;

static void test_strmap_init() {
  StrMap_init(smap);
  TEST_ASSERT_EQUAL_UINT64((uint64_t) smap->size, (uint64_t)(size_t) 0);
  TEST_ASSERT_EQUAL_PTR(smap->first, 0);
  TEST_ASSERT_EQUAL_PTR(smap->last, 0);
}

static void test_strmap_set1() {
  StrMap_set(smap, String_const("key123"), String_const("v1"), false);
  TEST_ASSERT_EQUAL_UINT64((uint64_t) smap->size, (uint64_t)(size_t) 1);
  TEST_ASSERT_NOT_NULL(smap->first);
  TEST_ASSERT_NOT_NULL(smap->last);
}

static void test_strmap_get1() {
  String value = StrMap_get(smap, String_const("key123"));
  TEST_ASSERT_TRUE(Strings_equals(value, String_const("v1")));
}

static void test_strmap_nullget1() {
  String value = StrMap_get(smap, String_const("h2so4"));
  TEST_ASSERT_EQUAL_UINT64((uint64_t) value.length, (uint64_t)(size_t) 0);
  TEST_ASSERT_EQUAL_PTR(value.buffer, 0);
}

static void test_strmap_free() {
  StrMap_free(smap);
  TEST_ASSERT_EQUAL_UINT64((uint64_t) smap->size, (uint64_t)(size_t) 0);
  TEST_ASSERT_EQUAL_PTR(smap->first, 0);
  TEST_ASSERT_EQUAL_PTR(smap->last, 0);
}

static void test_strmap_get_empty_returns_null() {
  String value = StrMap_get(smap, String_const("absent"));
  TEST_ASSERT_NOT_EQUAL(0, errno);
  TEST_ASSERT_EQUAL_PTR(value.buffer, 0);
}

static void test_strmap_set_duplicate_updates_value_and_size_constant() {
  StrMap_set(smap, String_const("dup"), String_const("1"), false);
  TEST_ASSERT_EQUAL_UINT64((uint64_t) smap->size, (uint64_t)(size_t) 2);
  TEST_ASSERT_TRUE(Strings_equals(StrMap_get(smap, String_const("dup")), String_const("1")));
  StrMap_set(smap, String_const("dup"), String_const("2"), false);
  TEST_ASSERT_EQUAL_UINT64((uint64_t) smap->size, (uint64_t)(size_t) 2);
  TEST_ASSERT_TRUE(Strings_equals(StrMap_get(smap, String_const("dup")), String_const("2")));
}

static void test_strmap_set_multiple_and_get_each() {
  StrMap_set(smap, String_const("a"), String_const("A"), false);
  StrMap_set(smap, String_const("b"), String_const("B"), false);
  StrMap_set(smap, String_const("c"), String_const("C"), false);
  TEST_ASSERT_TRUE(StrMap_get(smap, String_const("x")).buffer == 0);
  TEST_ASSERT_TRUE(Strings_equals(StrMap_get(smap, String_const("a")), String_const("A")));
  TEST_ASSERT_TRUE(Strings_equals(StrMap_get(smap, String_const("b")), String_const("B")));
  TEST_ASSERT_TRUE(Strings_equals(StrMap_get(smap, String_const("c")), String_const("C")));
}

static void test_strmap_remove_nonexistent_returns_false_and_no_change() {
  size_t oldSize = smap->size;
  errno = 0; StrMap_remove(smap, String_const("zzz")); TEST_ASSERT_NOT_EQUAL(0, errno);
  TEST_ASSERT_EQUAL_UINT64((uint64_t) smap->size, (uint64_t) oldSize);
}

static void test_strmap_remove_existing_from_middle() {
  StrMap_set(smap, String_const("k1"), String_const("11"), false);
  StrMap_set(smap, String_const("k2"), String_const("22"), false);
  StrMap_set(smap, String_const("k3"), String_const("33"), false);
  size_t sizeBefore = smap->size;
  errno = 0; StrMap_remove(smap, String_const("k2")); TEST_ASSERT_EQUAL_INT(0, errno);
  TEST_ASSERT_EQUAL_UINT64((uint64_t) smap->size, (uint64_t)(sizeBefore - 1));
  TEST_ASSERT_TRUE(StrMap_get(smap, String_const("k2")).buffer == 0);
  TEST_ASSERT_TRUE(Strings_equals(StrMap_get(smap, String_const("k1")), String_const("11")));
  TEST_ASSERT_TRUE(Strings_equals(StrMap_get(smap, String_const("k3")), String_const("33")));
}

static void test_strmap_set_empty_key_and_get() {
  StrMap_set(smap, String_const(""), String_const("EE"), false);
  TEST_ASSERT_TRUE(Strings_equals(StrMap_get(smap, String_const("")), String_const("EE")));
}

static void test_strmap_set_null_value_increases_size_and_removable() {
  size_t sizeBefore = smap->size;
  StrMap_set(smap, String_const("nullv"), (String){0}, false);
  TEST_ASSERT_EQUAL_UINT64((uint64_t) smap->size, (uint64_t)(sizeBefore + 1));
  errno = 0; StrMap_remove(smap, String_const("nullv")); TEST_ASSERT_EQUAL_INT(0, errno);
}

static void testing_strmap() {
  smap = A_loc(sizeof(struct StrMap));

  RUN_TEST(test_strmap_init);
  RUN_TEST(test_strmap_get_empty_returns_null);
  RUN_TEST(test_strmap_set1);
  RUN_TEST(test_strmap_get1);
  RUN_TEST(test_strmap_nullget1);
  RUN_TEST(test_strmap_set_duplicate_updates_value_and_size_constant);
  RUN_TEST(test_strmap_set_multiple_and_get_each);
  RUN_TEST(test_strmap_remove_nonexistent_returns_false_and_no_change);
  RUN_TEST(test_strmap_remove_existing_from_middle);
  RUN_TEST(test_strmap_set_empty_key_and_get);
  RUN_TEST(test_strmap_set_null_value_increases_size_and_removable);
  RUN_TEST(test_strmap_free);

  A_free(smap);
}

void strmap() {
  testing_strmap();
}


