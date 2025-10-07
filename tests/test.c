#include "unity.h"

#include "utils.h"

void setUp() {
  printf("RUN TESTS: ");
}
void tearDown() {
  printf("TESTS END!");
}


// #include "test_unicode.h"
// #include "test_gmaps.h"
// #include "test_strmap.h"
// #include "test_lists.h"

#include "test_glists.h"

int main() {
  UNITY_BEGIN();

  test_glists();

  return UNITY_END();
}
