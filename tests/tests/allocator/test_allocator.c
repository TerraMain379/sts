#include "test_allocator.h"

#include "unity.h"

#include "allocator.h"
#include "utils.h"


void test_start() {
  TEST_ASSERT_EQUAL_UINT(A_getCounter(), 0);
  TEST_ASSERT_EQUAL_UINT(A_getLocCounter(), 0);
  TEST_ASSERT_EQUAL_UINT(A_getRelocCounter(), 0);
  TEST_ASSERT_EQUAL_UINT(A_getFreeCounter(), 0);
}

void test_loc1() {
  size_t lc1 = A_getLocCounter();
  size_t c1 = A_getCounter();
  void* p1 = A_loc(1);
  size_t lc2 = A_getLocCounter();
  size_t c2 = A_getCounter();

  TEST_ASSERT_EQUAL_UINT(lc1 + 1, lc2);
  TEST_ASSERT_EQUAL_UINT(c1 + 1, c2);
  TEST_ASSERT_TRUE(A_checkLoc(p1));
  TEST_ASSERT_EQUAL_UINT(A_getSize(p1), 1);

  A_free(p1);
  lc1 = A_getLocCounter();
  c1 = A_getCounter();

  TEST_ASSERT_EQUAL_UINT(lc2, lc1);
  TEST_ASSERT_EQUAL_UINT(c2 - 1, c1);
  TEST_ASSERT_TRUE(!A_checkLoc(p1));
}
void test_xloc1() {
  size_t lc1 = A_getLocCounter();
  size_t c1 = A_getCounter();
  void* p1 = A_xloc(1);
  size_t lc2 = A_getLocCounter();
  size_t c2 = A_getCounter();

  TEST_ASSERT_EQUAL_UINT(lc1 + 1, lc2);
  TEST_ASSERT_EQUAL_UINT(c1 + 1, c2);
  TEST_ASSERT_TRUE(A_checkLoc(p1));
  TEST_ASSERT_EQUAL_UINT(A_getSize(p1), 1);

  A_free(p1);
  lc1 = A_getLocCounter();
  c1 = A_getCounter();

  TEST_ASSERT_EQUAL_UINT(lc2, lc1);
  TEST_ASSERT_EQUAL_UINT(c2 - 1, c1);
  TEST_ASSERT_TRUE(!A_checkLoc(p1));
}

size_t startLc;
size_t startC;
void* ptrs[100];
void test_locs1_1() {
  startLc = A_getLocCounter();
  startC = A_getCounter();

  // void* ptrs[100];
  size_t a = 1 - 10;
  printf("%zu\n", a);
  for (size_t i = 1; i <= 100; i++) {
    void* p = A_xloc(i);
    ptrs[i-1] = p;
    size_t lc = A_getLocCounter();
    size_t c = A_getCounter();
    TEST_ASSERT_EQUAL_UINT(startLc + i, lc);
    TEST_ASSERT_EQUAL_UINT(startC + i, c);
  }

  for (size_t i = 1; i <= 100; i++) {
    void* p = ptrs[i-1];
    TEST_ASSERT_TRUE(A_checkLoc(p));
    TEST_ASSERT_EQUAL_UINT(A_getSize(p), i);
  }
}
void test_locs1_2() {
  for (size_t i = 1; i <= 100; i++) {
    void* p = ptrs[i-1];

    size_t lc1 = A_getLocCounter();
    size_t c1 = A_getCounter();
    A_free(p);
    size_t lc2 = A_getLocCounter();
    size_t c2 = A_getCounter();

    TEST_ASSERT_TRUE(!A_checkLoc(p));
    TEST_ASSERT_EQUAL_UINT(lc2, lc1);
    TEST_ASSERT_EQUAL_UINT(c2, c1 - 1);
  }

  size_t endLc = A_getLocCounter();
  size_t endC = A_getCounter();
  TEST_ASSERT_EQUAL_UINT(startLc+100, endLc);
  TEST_ASSERT_EQUAL_UINT(startC, endC);
}
void test_reloc_start() {
  TEST_ASSERT_EQUAL_UINT(A_getCounter(), 0);
}
void test_reloc() {
  void* p1 = A_xloc(10);

  TEST_ASSERT_TRUE(A_checkLoc(p1));
  TEST_ASSERT_EQUAL_UINT(A_getSize(p1), 10);


  size_t lc1 = A_getLocCounter();
  size_t rc1 = A_getRelocCounter();
  size_t c1 = A_getCounter();
  void* p2 = A_reloc(p1, 20);
  size_t lc2 = A_getLocCounter();
  size_t rc2 = A_getRelocCounter();
  size_t c2 = A_getCounter();

  // TEST_ASSERT_EQUAL_PTR(p1, p2);
  // A_checkLoc(p1); TEST_ASSERT_TRUE(errno == 0);
  A_checkLoc(p2); TEST_ASSERT_TRUE(errno == 0);
  TEST_ASSERT_EQUAL_UINT(A_getSize(p2), 20);
  TEST_ASSERT_EQUAL_UINT(lc1, lc2);
  TEST_ASSERT_EQUAL_UINT(rc1+1, rc2);
  TEST_ASSERT_EQUAL_UINT(c1, c2);

  c1 = A_getCounter();
  size_t fc1 = A_getFreeCounter();
  A_free(p2);
  c2 = A_getCounter();
  size_t fc2 = A_getFreeCounter();

  TEST_ASSERT_EQUAL_UINT(c1-1, c2);
  TEST_ASSERT_EQUAL_UINT(fc1+1, fc2);
}
void test_xreloc() {
  void* p1 = A_xloc(10);

  TEST_ASSERT_TRUE(A_checkLoc(p1));
  TEST_ASSERT_EQUAL_UINT(A_getSize(p1), 10);

  size_t lc1 = A_getLocCounter();
  size_t rc1 = A_getRelocCounter();
  size_t c1 = A_getCounter();
  void* p2 = A_xreloc(p1, 20);
  size_t lc2 = A_getLocCounter();
  size_t rc2 = A_getRelocCounter();
  size_t c2 = A_getCounter();

  // TEST_ASSERT_EQUAL_PTR(p1, p2);
  // A_checkLoc(p1); TEST_ASSERT_TRUE(errno == 0);
  A_checkLoc(p2); TEST_ASSERT_TRUE(errno == 0);
  TEST_ASSERT_EQUAL_UINT(A_getSize(p2), 20);
  TEST_ASSERT_EQUAL_UINT(lc1, lc2);
  TEST_ASSERT_EQUAL_UINT(rc1+1, rc2);
  TEST_ASSERT_EQUAL_UINT(c1, c2);

  c1 = A_getCounter();
  size_t fc1 = A_getFreeCounter();
  A_free(p2);
  c2 = A_getCounter();
  size_t fc2 = A_getFreeCounter();

  TEST_ASSERT_EQUAL_UINT(c1-1, c2);
  TEST_ASSERT_EQUAL_UINT(fc1+1, fc2);
}
void test_reloc_sp1() { // it is specific to the most common allocator
  void* m1 = A_xloc(10);

  size_t lc1 = A_getLocCounter();
  size_t c1 = A_getCounter();
  void* p1 = A_loc(10);
  size_t lc2 = A_getLocCounter();
  size_t c2 = A_getCounter();

  TEST_ASSERT_EQUAL_UINT(A_getSize(p1), 10);
  TEST_ASSERT_EQUAL_UINT(c1+1, c2);
  TEST_ASSERT_EQUAL_UINT(lc1+1, lc2);

  void* m2 = A_xloc(10);
  void* m3 = A_xloc(10);
  A_free(m2);

  lc1 = A_getLocCounter();
  size_t rc1 = A_getRelocCounter();
  c1 = A_getCounter();
  void* p2 = A_xreloc(p1, 30);
  lc2 = A_getLocCounter();
  size_t rc2 = A_getRelocCounter();
  c2 = A_getCounter();

  TEST_ASSERT_TRUE(p1 != p2);
  A_checkLoc(p1); TEST_ASSERT_TRUE(errno != 0);
  A_checkLoc(p2); TEST_ASSERT_TRUE(errno == 0);
  TEST_ASSERT_EQUAL_UINT(A_getSize(p2), 30);
  TEST_ASSERT_EQUAL_UINT(lc1, lc2);
  TEST_ASSERT_EQUAL_UINT(rc1+1, rc2);
  TEST_ASSERT_EQUAL_UINT(c1, c2);

  A_free(m1);
  A_free(m3);
}


void test_allocator() {
  RUN_TEST(test_start);
  RUN_TEST(test_loc1);
  RUN_TEST(test_xloc1);
  RUN_TEST(test_locs1_1);
  RUN_TEST(test_locs1_2);
  RUN_TEST(test_reloc_start);
  RUN_TEST(test_reloc); // it is specific to the most common allocator
  RUN_TEST(test_xreloc); // it is specific to the most common allocator
  RUN_TEST(test_reloc_start); 
  RUN_TEST(test_reloc_sp1); // it is specific to the most common allocator
}
