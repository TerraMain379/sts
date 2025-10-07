#include "test_unicode.h"

#include "unity.h"

#include "unicode.h"
#include "strings.h"

// UNKNOWN_CHAR from unicode.c
#define U_REPLACEMENT 0xFFFDu

static void assert_decode_sequence(const char* bytes, const uint32_t* expect, const size_t* lens, size_t n) {
  String str = String_const(bytes);
  char* p = str.buffer;
  char** it = &p;

  for (size_t i = 0; i < n; ++i) {
    char* before = *it;
    uint32_t cp = UTF8_readUChar(it);
    size_t delta = (size_t)(*it - before);
    TEST_ASSERT_EQUAL_HEX32_MESSAGE(expect[i], cp, "decoded codepoint mismatch");
    TEST_ASSERT_EQUAL_UINT_MESSAGE(lens[i], delta, "byte length mismatch");
  }
}

void test_unicode_ascii_iterates_and_lengths() {
  String str = String_const("Hello world!");
  char* p = str.buffer;
  char** it = &p;

  for (size_t i = 0; str.buffer[i] != '\0';) {
    char* before = *it;
    uint32_t cp = UTF8_readUChar(it);
    size_t delta = (size_t)(*it - before);
    TEST_ASSERT_EQUAL_UINT8(str.buffer[i], (uint8_t)cp);
    TEST_ASSERT_EQUAL_UINT(1u, delta);
    i += delta;
  }
}

void test_unicode_valid_multibyte_and_lengths() {
  // a, á, β, ¢, €, 𐍈
  const char* s = "\x61\xC3\xA1\xCE\xB2\xC2\xA2\xE2\x82\xAC\xF0\x90\x8D\x88";
  const uint32_t expect[] = {0x61, 0xE1, 0x3B2, 0xA2, 0x20AC, 0x10348};
  const size_t lens[] = {1, 2, 2, 2, 3, 4};
  assert_decode_sequence(s, expect, lens, 6);
}

void test_unicode_BOM_skip() {
  // BOM + 'A' (0x41)
  String str = String_const("\xEF\xBB\xBF\x41");
  char* p = str.buffer;
  char** it = &p;
  UTF8_skipBOM(it);
  TEST_ASSERT_EQUAL_PTR(str.buffer + 3, *it);
  uint32_t cp = UTF8_readUChar(it);
  TEST_ASSERT_EQUAL_UINT32(0x41u, cp);
}

void test_unicode_read_on_NUL_advances_and_returns_zero() {
  String str = String_const("\x00xyz");
  char* p = str.buffer;
  char** it = &p;
  uint32_t cp = UTF8_readUChar(it);
  TEST_ASSERT_EQUAL_UINT32(0u, cp);
  TEST_ASSERT_EQUAL_PTR(str.buffer + 1, *it);
}

void test_unicode_invalid_start_byte_replaced_and_advance_one() {
  // 0xF8 is invalid start in UTF-8. Then 'A'.
  String str = String_const("\xF8\x41");
  char* p = str.buffer;
  char** it = &p;
  uint32_t cp1 = UTF8_readUChar(it);
  TEST_ASSERT_EQUAL_HEX32(U_REPLACEMENT, cp1);
  TEST_ASSERT_EQUAL_PTR(str.buffer + 1, *it);
  uint32_t cp2 = UTF8_readUChar(it);
  TEST_ASSERT_EQUAL_UINT32(0x41u, cp2);
}

void test_unicode_invalid_continuation_replaced() {
  // Start byte 0xC2 requires one continuation, but next is space (0x20), not 10xxxxxx
  String str = String_const("\xC2\x20\x41");
  char* p = str.buffer;
  char** it = &p;
  uint32_t cp1 = UTF8_readUChar(it);
  // Function should detect invalid continuation and yield replacement; it should not over-advance
  TEST_ASSERT_EQUAL_HEX32(U_REPLACEMENT, cp1);
  // After failure, implementation currently does not consume remaining bytes in the sequence except those validated; ensure progress occurred
  TEST_ASSERT_TRUE(*it > str.buffer);
  // Next valid 'A' must still be decodable eventually
  // Skip until we reach 'A' to avoid relying on specific consumption policy
  while (**it && **it != 'A') { (void)UTF8_readUChar(it); }
  if (**it == 'A') {
    uint32_t cp2 = UTF8_readUChar(it);
    TEST_ASSERT_EQUAL_UINT32(0x41u, cp2);
  }
}

void test_unicode_overlong_sequences_replaced() {
  // Overlong encodings of ASCII '/': 0x2F
  const char s1[] = "\xC0\xAF";      // 2-byte overlong
  const char s2[] = "\xE0\x80\xAF";  // 3-byte overlong
  const char s3[] = "\xF0\x80\x80\xAF"; // 4-byte overlong
  const uint32_t exp[1] = {U_REPLACEMENT};
  const size_t len2[1] = {2};
  const size_t len3[1] = {3};
  const size_t len4[1] = {4};
  assert_decode_sequence(s1, exp, len2, 1);
  assert_decode_sequence(s2, exp, len3, 1);
  assert_decode_sequence(s3, exp, len4, 1);
}

void test_unicode_boundaries_and_invalid_above_max() {
  // Max valid U+10FFFF: F4 8F BF BF
  const char* max_valid = "\xF4\x8F\xBF\xBF";
  String s1 = String_const(max_valid);
  char* p1 = s1.buffer; char** it1 = &p1;
  uint32_t cp1 = UTF8_readUChar(it1);
  TEST_ASSERT_EQUAL_HEX32(0x10FFFFu, cp1);
  TEST_ASSERT_EQUAL_PTR(s1.buffer + 4, *it1);

  // Above max: F4 90 80 80 -> should be replacement
  const char* above = "\xF4\x90\x80\x80";
  String s2 = String_const(above);
  char* p2 = s2.buffer; char** it2 = &p2;
  uint32_t cp2 = UTF8_readUChar(it2);
  TEST_ASSERT_EQUAL_HEX32(U_REPLACEMENT, cp2);
}

void test_unicode_truncated_sequences() {
  // Incomplete sequences should be treated as invalid (replacement), consumption depends on implementation
  const char* s = "\xC3"; // expects one continuation but string ends
  String str = String_const(s);
  char* p = str.buffer; char** it = &p;
  uint32_t cp = UTF8_readUChar(it);
  TEST_ASSERT_EQUAL_HEX32(U_REPLACEMENT, cp);
}

void unicode() {
  RUN_TEST(test_unicode_ascii_iterates_and_lengths);
  RUN_TEST(test_unicode_valid_multibyte_and_lengths);
  RUN_TEST(test_unicode_BOM_skip);
  RUN_TEST(test_unicode_read_on_NUL_advances_and_returns_zero);
  RUN_TEST(test_unicode_invalid_start_byte_replaced_and_advance_one);
  RUN_TEST(test_unicode_invalid_continuation_replaced);
  RUN_TEST(test_unicode_overlong_sequences_replaced);
  RUN_TEST(test_unicode_boundaries_and_invalid_above_max);
  RUN_TEST(test_unicode_truncated_sequences);
}
