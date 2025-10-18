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
#include "test_gmaps.h"

#define NAME RegexRC
#define TYPE Regex
#define FREE_FUN Regex_free
#include "refcount.h"
#undef NAME
#undef TYPE
#undef FREE_FUN

int main() {
  UNITY_BEGIN();

  test_glists();
  test_gmaps();

  return UNITY_END();
}
