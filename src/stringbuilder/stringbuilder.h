#pragma once

#include "strings.h"
#include "utils.h"

typedef struct StringBuilder {
  OWNER(char*) buffer;
  size_t size;
  size_t capacity;
} StringBuilder;

void StringBuilder_init(StringBuilder* builder);
void StringBuilder_free(StringBuilder* builder);
void StringBuilder_setCapacity(StringBuilder* builder, size_t capacity);

void StringBuilder_addChar(StringBuilder* builder, char c);
void StringBuilder_addCharBuffer(StringBuilder* builder, BORROW(char*) str);
void StringBuilder_addString(StringBuilder* builder, BORROW(ViewString) vs);

ViewString StringBuilder_get(BORROW(StringBuilder*) builder);
String StringBuilder_take(OWNER(StringBuilder*) builder); // and free
