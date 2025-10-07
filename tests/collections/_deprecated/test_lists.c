#include "unity.h"

#include "list.h"
#include "strlist.h"
#include "strings.h"
#include "allocator.h"
#include <errno.h>

static struct List* list;
static struct StrList* slist;

static void test_list_init() {
  List_init(list, 0);
  TEST_ASSERT_EQUAL_UINT64((uint64_t) list->size, (uint64_t)(size_t) 0);
  TEST_ASSERT_EQUAL_UINT64((uint64_t) list->capacity, (uint64_t)(size_t) 0);
}

static void test_list_add_and_get() {
  int* v1 = A_loc(sizeof(int)); *v1 = 11;
  int* v2 = A_loc(sizeof(int)); *v2 = 22;
  List_add(list, v1, true);
  List_add(list, v2, true);
  TEST_ASSERT_EQUAL_UINT64((uint64_t) list->size, (uint64_t)(size_t) 2);
  TEST_ASSERT_NOT_NULL(List_get(list, 0));
  TEST_ASSERT_NOT_NULL(List_get(list, 1));
}

static void test_list_add_and_get_many() {
  List_init(list, 0);
  for (int i = 0; i < 10; i++) {
    int* v = A_loc(sizeof(int)); *v = i;
    List_add(list, v, true);
    TEST_ASSERT_EQUAL_UINT64((uint64_t) list->size, (uint64_t)(size_t) (i+1));
    TEST_ASSERT_EQUAL_INT(i, **(int**)List_get(list, i));
  }
}

static void test_list_set_and_getownership() {
  int* v3 = A_loc(sizeof(int)); *v3 = 33;
  List_set(list, v3, true, 1);
  int* owned = (int*) List_getOwnership(list, 1);
  TEST_ASSERT_NOT_NULL(owned);
  TEST_ASSERT_EQUAL_INT(33, *owned);
  A_free(owned);
}

static void test_list_insert_and_remove() {
  int* v4 = A_loc(sizeof(int)); *v4 = 44;
  List_insert(list, v4, true, 1);
  List_remove(list, 0);
}

static void test_list_insert_positions() {
  List_init(list, 0);
  int* v10 = A_loc(sizeof(int)); *v10 = 10; List_add(list, v10, true);
  errno = 0; List_insert(list, (void*)0xDEADBEEF, true, list->size); TEST_ASSERT_NOT_EQUAL(0, errno);
  int* v5 = A_loc(sizeof(int)); *v5 = 5; errno = 0; List_insert(list, v5, true, 0); TEST_ASSERT_EQUAL_INT(0, errno);
  TEST_ASSERT_EQUAL_INT(5, **(int**)List_get(list, 0));
  TEST_ASSERT_EQUAL_INT(10, **(int**)List_get(list, 1));
  int* v20 = A_loc(sizeof(int)); *v20 = 20; List_add(list, v20, true);
  int* v15 = A_loc(sizeof(int)); *v15 = 15; errno = 0; List_insert(list, v15, true, 2); TEST_ASSERT_EQUAL_INT(0, errno);
  TEST_ASSERT_EQUAL_INT(5, **(int**)List_get(list, 0));
  TEST_ASSERT_EQUAL_INT(10, **(int**)List_get(list, 1));
  TEST_ASSERT_EQUAL_INT(15, **(int**)List_get(list, 2));
  TEST_ASSERT_EQUAL_INT(20, **(int**)List_get(list, 3));
}

static void test_list_set_positions() {
  List_init(list, 0);
  int* v0 = A_loc(sizeof(int)); *v0 = 0; List_add(list, v0, true);
  int* v1 = A_loc(sizeof(int)); *v1 = 1; List_add(list, v1, true);
  int* v2 = A_loc(sizeof(int)); *v2 = 2; List_add(list, v2, true);
  int* v99 = A_loc(sizeof(int)); *v99 = 99; errno = 0; List_set(list, v99, true, 1); TEST_ASSERT_EQUAL_INT(0, errno);
  TEST_ASSERT_EQUAL_INT(99, **(int**)List_get(list, 1));
  errno = 0; List_set(list, (void*)0x1, true, 100); TEST_ASSERT_NOT_EQUAL(0, errno);
}

static void test_list_remove_positions() {
  List_init(list, 0);
  for (int i = 0; i < 5; i++) { int* p = A_loc(sizeof(int)); *p = i; List_add(list, p, true); }
  errno = 0; List_remove(list, 2); TEST_ASSERT_EQUAL_INT(0, errno);
  TEST_ASSERT_EQUAL_UINT64((uint64_t) list->size, (uint64_t)(size_t) 4);
  errno = 0; List_remove(list, 0); TEST_ASSERT_EQUAL_INT(0, errno);
  TEST_ASSERT_EQUAL_UINT64((uint64_t) list->size, (uint64_t)(size_t) 3);
  errno = 0; List_remove(list, list->size - 1); TEST_ASSERT_EQUAL_INT(0, errno);
  TEST_ASSERT_EQUAL_UINT64((uint64_t) list->size, (uint64_t)(size_t) 2);
}

static void test_list_bounds_and_free() {
  (void) List_remove(list, 100);
  (void) List_set(list, A_loc(sizeof(int)), true, 100);
  (void) List_get(list, 100);
  List_free(list);
  TEST_ASSERT_TRUE(1);
}

static void test_list_errno_cases() {
  // fresh list
  List_init(list, 0);
  errno = 0; List_insert(list, (void*)0x1, true, 5); TEST_ASSERT_NOT_EQUAL(0, errno);
  errno = 0; List_set(list, (void*)0x2, true, 7);   TEST_ASSERT_NOT_EQUAL(0, errno);
  errno = 0; void** got = List_get(list, 3);        TEST_ASSERT_NOT_EQUAL(0, errno); TEST_ASSERT_EQUAL_PTR(0, got);
  errno = 0; void* owned = List_getOwnership(list, 9); TEST_ASSERT_NOT_EQUAL(0, errno); TEST_ASSERT_EQUAL_PTR(0, owned);
  errno = 0; List_remove(list, 4);                  TEST_ASSERT_NOT_EQUAL(0, errno);
  List_free(list);
}

static void test_strlist_init() {
  StrList_init(slist, 0);
  TEST_ASSERT_EQUAL_UINT64((uint64_t) slist->size, (uint64_t)(size_t) 0);
  TEST_ASSERT_EQUAL_UINT64((uint64_t) slist->capacity, (uint64_t)(size_t) 0);
  // malloc(0) may return non-null; don't assert on array pointer
}

static void test_strlist_add_get_equals() {
  StrList_add(slist, String_const("a"), false);
  StrList_add(slist, String_const("b"), false);
  TEST_ASSERT_TRUE(Strings_equals(*StrList_get(slist, 0), String_const("a")));
  TEST_ASSERT_TRUE(Strings_equals(*StrList_get(slist, 1), String_const("b")));
}

static void test_strlist_add_many_and_get() {
  StrList_init(slist, 0);
  for (int i = 0; i < 8; i++) {
    char buf[4]; buf[0] = 'a' + i; buf[1] = '\0';
    StrList_add(slist, String_const(buf), false);
    TEST_ASSERT_TRUE(Strings_equals(*StrList_get(slist, i), String_const(buf)));
  }
}

static void test_strlist_set_insert_remove() {
  StrList_set(slist, String_const("B"), false, 1);
  StrList_insert(slist, String_const("A"), false, 1);
  TEST_ASSERT_TRUE(Strings_equals(*StrList_get(slist, 1), String_const("A")));
  StrList_remove(slist, 0);
}

static void test_strlist_getownership_and_free() {
  String owned = StrList_getOwnership(slist, 0);
  if (owned.buffer) String_free(&owned);
  StrList_free(slist);
  TEST_ASSERT_TRUE(1);
}

static void test_strlist_errno_cases() {
  // fresh strlist
  StrList_init(slist, 0);
  errno = 0; StrList_insert(slist, String_const("x"), false, 2); TEST_ASSERT_NOT_EQUAL(0, errno);
  errno = 0; StrList_set(slist, String_const("y"), false, 3);    TEST_ASSERT_NOT_EQUAL(0, errno);
  errno = 0; String* g = StrList_get(slist, 1);                   TEST_ASSERT_NOT_EQUAL(0, errno); TEST_ASSERT_EQUAL_PTR(0, g);
  errno = 0; String ow = StrList_getOwnership(slist, 5);          TEST_ASSERT_NOT_EQUAL(0, errno); TEST_ASSERT_EQUAL_PTR(0, ow.buffer); TEST_ASSERT_EQUAL_UINT64((uint64_t)0, (uint64_t)ow.length);
  errno = 0; StrList_remove(slist, 4);                            TEST_ASSERT_NOT_EQUAL(0, errno);
  StrList_free(slist);
}

static void testing_lists() {
  list = A_loc(sizeof(struct List));
  slist = A_loc(sizeof(struct StrList));

  RUN_TEST(test_list_init);
  RUN_TEST(test_list_add_and_get);
  RUN_TEST(test_list_add_and_get_many);
  RUN_TEST(test_list_set_and_getownership);
  RUN_TEST(test_list_insert_and_remove);
  RUN_TEST(test_list_insert_positions);
  RUN_TEST(test_list_set_positions);
  RUN_TEST(test_list_remove_positions);
  RUN_TEST(test_list_bounds_and_free);
  RUN_TEST(test_list_errno_cases);

  RUN_TEST(test_strlist_init);
  RUN_TEST(test_strlist_add_get_equals);
  RUN_TEST(test_strlist_add_many_and_get);
  RUN_TEST(test_strlist_set_insert_remove);
  RUN_TEST(test_strlist_getownership_and_free);
  RUN_TEST(test_strlist_errno_cases);

  A_free(list);
  A_free(slist);
}

void lists() {
  testing_lists();
}


