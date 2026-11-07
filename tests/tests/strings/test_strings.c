#include "test_strings.h"

#include "unity.h"

#include "strings.h"
#include "allocator.h"

void test_string_new1() {
  char text[6] = "hello";
  String string = String_new(text, 5, false);
  TEST_ASSERT_EQUAL_STRING(string.buffer, "hello");
  TEST_ASSERT_EQUAL_UINT(string.size, 5u);

  size_t c1 = A_getCounter();
  size_t fc1 = A_getFreeCounter();
  String_free(&string);
  size_t c2 = A_getCounter();
  size_t fc2 = A_getFreeCounter();
  
  TEST_ASSERT_EQUAL_UINT(c1, c2);
  TEST_ASSERT_EQUAL_UINT(fc1, fc2);
}

void test_string_new2() {
  char* text = A_xloc(sizeof(char)*6);
  Strings_strcpy(text, 6, "hello", 6);
  String string = String_new(text, 5, true);
  TEST_ASSERT_EQUAL_STRING(string.buffer, "hello");
  TEST_ASSERT_EQUAL_UINT(string.size, 5u);

  size_t c1 = A_getCounter();
  size_t fc1 = A_getFreeCounter();
  String_free(&string);
  size_t c2 = A_getCounter();
  size_t fc2 = A_getFreeCounter();
  
  TEST_ASSERT_EQUAL_UINT(c1-1, c2);
  TEST_ASSERT_EQUAL_UINT(fc1+1, fc2);
}

void test_string_of() {
  char* text = A_xloc(sizeof(char)*9);
  Strings_strcpy(text, 9, "text 123", 9);
  String string = String_of(text);
  TEST_ASSERT_EQUAL_PTR(string.buffer, text);
  TEST_ASSERT_EQUAL_STRING(string.buffer, "text 123");
  TEST_ASSERT_EQUAL_UINT(string.size, 8u);

  size_t c1 = A_getCounter();
  size_t fc1 = A_getFreeCounter();
  String_free(&string);
  size_t c2 = A_getCounter();
  size_t fc2 = A_getFreeCounter();
  
  TEST_ASSERT_TRUE(!A_checkLoc(text));
  TEST_ASSERT_EQUAL_UINT(c1-1, c2);
  TEST_ASSERT_EQUAL_UINT(fc1+1, fc2);
}

void test_string_by() {
  char* text = A_xloc(sizeof(char)*9);
  Strings_strcpy(text, 9, "text 123", 9);
  String string = String_by(text);
  TEST_ASSERT_NOT_EQUAL(string.buffer, text);
  TEST_ASSERT_EQUAL_STRING(string.buffer, "text 123");
  TEST_ASSERT_EQUAL_UINT(string.size, 8u);

  size_t c1 = A_getCounter();
  size_t fc1 = A_getFreeCounter();
  String_free(&string);
  size_t c2 = A_getCounter();
  size_t fc2 = A_getFreeCounter();
  
  TEST_ASSERT_TRUE(A_checkLoc(text));
  TEST_ASSERT_EQUAL_UINT(c1-1, c2);
  TEST_ASSERT_EQUAL_UINT(fc1+1, fc2);

  A_free(text);
}

void test_vstring_new() {
  char text[6] = "hello";
  ViewString vstring = ViewString_new(text, 5);
  TEST_ASSERT_EQUAL_STRING(vstring.buffer, "hello");
  TEST_ASSERT_EQUAL_UINT(vstring.size, 5u);

  size_t c1 = A_getCounter();
  size_t fc1 = A_getFreeCounter();
  ViewString_free(&vstring);
  size_t c2 = A_getCounter();
  size_t fc2 = A_getFreeCounter();
  
  TEST_ASSERT_EQUAL_UINT(c1, c2);
  TEST_ASSERT_EQUAL_UINT(fc1, fc2);
}

void test_vstring_of() {
  char text[6] = "hello";
  ViewString vstring = ViewString_of(text);
  TEST_ASSERT_EQUAL_STRING(vstring.buffer, "hello");
  TEST_ASSERT_EQUAL_UINT(vstring.size, 5u);

  size_t c1 = A_getCounter();
  size_t fc1 = A_getFreeCounter();
  ViewString_free(&vstring);
  size_t c2 = A_getCounter();
  size_t fc2 = A_getFreeCounter();
  
  TEST_ASSERT_EQUAL_UINT(c1, c2);
  TEST_ASSERT_EQUAL_UINT(fc1, fc2);
}

void test_vstring_by() {
  char text[6] = "hello";
  String string = String_by(text);
  ViewString vstring = ViewString_by(string);
  TEST_ASSERT_EQUAL_STRING(vstring.buffer, "hello");
  TEST_ASSERT_EQUAL_UINT(vstring.size, 5u);

  size_t c1 = A_getCounter();
  size_t fc1 = A_getFreeCounter();
  ViewString_free(&vstring);
  size_t c2 = A_getCounter();
  size_t fc2 = A_getFreeCounter();
  
  TEST_ASSERT_EQUAL_UINT(c1, c2);
  TEST_ASSERT_EQUAL_UINT(fc1, fc2);

  c1 = A_getCounter();
  fc1 = A_getFreeCounter();
  String_free(&string);
  c2 = A_getCounter();
  fc2 = A_getFreeCounter();
  
  TEST_ASSERT_EQUAL_UINT(c1-1, c2);
  TEST_ASSERT_EQUAL_UINT(fc1+1, fc2);
}

void test_string_copy1() {
  char* text = A_xloc(sizeof(char)*9);
  Strings_strcpy(text, 9, "text 123", 9);
  String string = String_of(text);
  TEST_ASSERT_EQUAL_STRING(string.buffer, "text 123");
  TEST_ASSERT_EQUAL_UINT(string.size, 8u);

  ViewString vstring = ViewString_by(string);
  TEST_ASSERT_EQUAL_STRING(vstring.buffer, "text 123");
  TEST_ASSERT_EQUAL_UINT(vstring.size, 8u);

  String string1 = String_copy(vstring);
  TEST_ASSERT_EQUAL_STRING(string1.buffer, "text 123");
  TEST_ASSERT_EQUAL_UINT(string1.size, 8u);
  char* buffer = string1.buffer;

  TEST_ASSERT_TRUE(A_checkLoc(text));
  TEST_ASSERT_TRUE(A_checkLoc(buffer));

  size_t c1 = A_getCounter();
  size_t fc1 = A_getFreeCounter();
  String_free(&string1);
  size_t c2 = A_getCounter();
  size_t fc2 = A_getFreeCounter();
  
  TEST_ASSERT_TRUE(A_checkLoc(text));
  TEST_ASSERT_TRUE(!A_checkLoc(buffer));
  TEST_ASSERT_EQUAL_UINT(c1-1, c2);
  TEST_ASSERT_EQUAL_UINT(fc1+1, fc2);

  c1 = A_getCounter();
  fc1 = A_getFreeCounter();
  ViewString_free(&vstring);
  c2 = A_getCounter();
  fc2 = A_getFreeCounter();
  
  TEST_ASSERT_TRUE(A_checkLoc(text));
  TEST_ASSERT_TRUE(!A_checkLoc(buffer));
  TEST_ASSERT_EQUAL_UINT(c1, c2);
  TEST_ASSERT_EQUAL_UINT(fc1, fc2);

  c1 = A_getCounter();
  fc1 = A_getFreeCounter();
  String_free(&string);
  c2 = A_getCounter();
  fc2 = A_getFreeCounter();
  
  TEST_ASSERT_TRUE(!A_checkLoc(text));
  TEST_ASSERT_TRUE(!A_checkLoc(buffer));
  TEST_ASSERT_EQUAL_UINT(c1-1, c2);
  TEST_ASSERT_EQUAL_UINT(fc1+1, fc2);
}

void test_string_copy2() {
  char* text = A_xloc(sizeof(char)*9);
  Strings_strcpy(text, 9, "text 123", 9);
  String string = String_of(text);
  TEST_ASSERT_EQUAL_STRING(string.buffer, "text 123");
  TEST_ASSERT_EQUAL_UINT(string.size, 8u);

  String string1 = String_copyString(string);
  TEST_ASSERT_EQUAL_STRING(string1.buffer, "text 123");
  TEST_ASSERT_EQUAL_UINT(string1.size, 8u);
  char* buffer = string1.buffer;

  TEST_ASSERT_TRUE(A_checkLoc(text));
  TEST_ASSERT_TRUE(A_checkLoc(buffer));

  size_t c1 = A_getCounter();
  size_t fc1 = A_getFreeCounter();
  String_free(&string1);
  size_t c2 = A_getCounter();
  size_t fc2 = A_getFreeCounter();
  
  TEST_ASSERT_TRUE(A_checkLoc(text));
  TEST_ASSERT_TRUE(!A_checkLoc(buffer));
  TEST_ASSERT_EQUAL_UINT(c1-1, c2);
  TEST_ASSERT_EQUAL_UINT(fc1+1, fc2);

  c1 = A_getCounter();
  fc1 = A_getFreeCounter();
  String_free(&string);
  c2 = A_getCounter();
  fc2 = A_getFreeCounter();
  
  TEST_ASSERT_TRUE(!A_checkLoc(text));
  TEST_ASSERT_TRUE(!A_checkLoc(buffer));
  TEST_ASSERT_EQUAL_UINT(c1-1, c2);
  TEST_ASSERT_EQUAL_UINT(fc1+1, fc2);
}

void test_vstring_equals1() {
  ViewString vstring1 = ViewString_of("hello world");
  ViewString vstring2 = ViewString_of("hello world");
  ViewString vstring3 = ViewString_of("world hello");
  ViewString vstring4 = ViewString_of("text 123");

  TEST_ASSERT_TRUE(ViewStrings_equals(vstring1, vstring2));
  TEST_ASSERT_TRUE(ViewStrings_equals(vstring2, vstring1));
  TEST_ASSERT_TRUE(!ViewStrings_equals(vstring1, vstring3));
  TEST_ASSERT_TRUE(!ViewStrings_equals(vstring1, vstring4));
  TEST_ASSERT_TRUE(!ViewStrings_equals(vstring2, vstring3));
  TEST_ASSERT_TRUE(!ViewStrings_equals(vstring2, vstring4));
  TEST_ASSERT_TRUE(!ViewStrings_equals(vstring3, vstring1));
  TEST_ASSERT_TRUE(!ViewStrings_equals(vstring3, vstring2));
  TEST_ASSERT_TRUE(!ViewStrings_equals(vstring3, vstring4));
  TEST_ASSERT_TRUE(!ViewStrings_equals(vstring4, vstring1));
  TEST_ASSERT_TRUE(!ViewStrings_equals(vstring4, vstring2));
  TEST_ASSERT_TRUE(!ViewStrings_equals(vstring4, vstring3));
}

void test_vstring_equals2() {
  String vstring1 = String_of("hello world");
  String vstring2 = String_of("hello world");
  String vstring3 = String_of("world hello");
  String vstring4 = String_of("text 123");

  TEST_ASSERT_TRUE(ViewStrings_equals(ViewString_by(vstring1), ViewString_by(vstring2)));
  TEST_ASSERT_TRUE(ViewStrings_equals(ViewString_by(vstring2), ViewString_by(vstring1)));
  TEST_ASSERT_TRUE(!ViewStrings_equals(ViewString_by(vstring1), ViewString_by(vstring3)));
  TEST_ASSERT_TRUE(!ViewStrings_equals(ViewString_by(vstring1), ViewString_by(vstring4)));
  TEST_ASSERT_TRUE(!ViewStrings_equals(ViewString_by(vstring2), ViewString_by(vstring3)));
  TEST_ASSERT_TRUE(!ViewStrings_equals(ViewString_by(vstring2), ViewString_by(vstring4)));
  TEST_ASSERT_TRUE(!ViewStrings_equals(ViewString_by(vstring3), ViewString_by(vstring1)));
  TEST_ASSERT_TRUE(!ViewStrings_equals(ViewString_by(vstring3), ViewString_by(vstring2)));
  TEST_ASSERT_TRUE(!ViewStrings_equals(ViewString_by(vstring3), ViewString_by(vstring4)));
  TEST_ASSERT_TRUE(!ViewStrings_equals(ViewString_by(vstring4), ViewString_by(vstring1)));
  TEST_ASSERT_TRUE(!ViewStrings_equals(ViewString_by(vstring4), ViewString_by(vstring2)));
  TEST_ASSERT_TRUE(!ViewStrings_equals(ViewString_by(vstring4), ViewString_by(vstring3)));
}

void test_string_equals() {
  String vstring1 = String_of("hello world");
  String vstring2 = String_of("hello world");
  String vstring3 = String_of("world hello");
  String vstring4 = String_of("text 123");

  TEST_ASSERT_TRUE(Strings_equals(vstring1, vstring2));
  TEST_ASSERT_TRUE(Strings_equals(vstring2, vstring1));
  TEST_ASSERT_TRUE(!Strings_equals(vstring1, vstring3));
  TEST_ASSERT_TRUE(!Strings_equals(vstring1, vstring4));
  TEST_ASSERT_TRUE(!Strings_equals(vstring2, vstring3));
  TEST_ASSERT_TRUE(!Strings_equals(vstring2, vstring4));
  TEST_ASSERT_TRUE(!Strings_equals(vstring3, vstring1));
  TEST_ASSERT_TRUE(!Strings_equals(vstring3, vstring2));
  TEST_ASSERT_TRUE(!Strings_equals(vstring3, vstring4));
  TEST_ASSERT_TRUE(!Strings_equals(vstring4, vstring1));
  TEST_ASSERT_TRUE(!Strings_equals(vstring4, vstring2));
  TEST_ASSERT_TRUE(!Strings_equals(vstring4, vstring3));
}

void test_vstring_tojson1() {
  String json;
  ViewString vstring = ViewString_of("string");
  // json = ViewStrings_toJson(&vstring, )
}

void test_strings() {
  RUN_TEST(test_string_new1);
  RUN_TEST(test_string_new2);
  RUN_TEST(test_string_of);
  RUN_TEST(test_string_by);
  RUN_TEST(test_vstring_new);
  RUN_TEST(test_vstring_of);
  RUN_TEST(test_vstring_by);
  RUN_TEST(test_string_copy1);
  RUN_TEST(test_string_copy2);
  RUN_TEST(test_vstring_equals1);
  RUN_TEST(test_vstring_equals2);
  RUN_TEST(test_string_equals);
  RUN_TEST(test_vstring_tojson1);
}
