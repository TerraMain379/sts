#include "unity.h"

#include "utils.h"

void setUp() { }
void tearDown() { }


#include "test_allocator.h"
#include "test_strings.h"

int main() {
  UNITY_BEGIN();
  printf("init tests\n");
  #ifndef BUILD_TESTS
    printf("please, enable BUILD_TESTS macros\n");
    return UNITY_END();
  #endif

  test_allocator();
  test_strings();

  return UNITY_END();
}
