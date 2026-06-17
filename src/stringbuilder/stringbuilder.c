#include "stringbuilder.h"

#include "allocator.h"

void StringBuilder_init(StringBuilder* builder) {
  builder->buffer = A_xloc(16*sizeof(char));
  builder->size = 0;
  builder->capacity = 16;
  builder->buffer[0] = '\0';
}
void StringBuilder_free(StringBuilder* builder) {
  A_free(builder->buffer);
  builder->buffer = null;
  builder->size = 0;
  builder->capacity = 0;
}
void StringBuilder_setCapacity(StringBuilder* builder, size_t capacity) {
  if (capacity == builder->capacity) return;
  builder->capacity = capacity;
  builder->buffer = A_xreloc(builder->buffer, capacity);
  if (capacity > builder->size) builder->capacity = capacity;
}

void StringBuilder_applyCapacity(StringBuilder* builder, size_t minCapacity) {
  size_t capacity = builder->capacity;
  if (capacity >= minCapacity) return;
  if (minCapacity > capacity*2) {
    StringBuilder_setCapacity(builder, minCapacity);
  }
  else if (minCapacity > 1000) {
    StringBuilder_setCapacity(builder, minCapacity+50);
  }
  else {
    StringBuilder_setCapacity(builder, capacity*2);
  }
}

void StringBuilder_addChar(StringBuilder* builder, char c) {
  StringBuilder_applyCapacity(builder, builder->size + 2);
  builder->buffer[builder->size++] = c;
  builder->buffer[builder->size] = '\0';
}
void StringBuilder_addCharBuffer(StringBuilder* builder, BORROW(char*) str) {
  size_t len = Strings_getLen(str);
  StringBuilder_applyCapacity(builder, builder->size + len + 1);
  Strings_strcpy(builder->buffer + builder->size, len + 1, str, len + 1);
  builder->size += len;
}
void StringBuilder_addString(StringBuilder* builder, ViewString vs) {
  StringBuilder_applyCapacity(builder, builder->size + vs.size + 1);
  Strings_strcpy(builder->buffer + builder->size, vs.size + 1, vs.buffer, vs.size + 1);
  builder->size += vs.size;
}

ViewString StringBuilder_get(BORROW(StringBuilder*) builder) {
  return ViewString_new(builder->buffer, builder->size);
}
String StringBuilder_take(OWNER(StringBuilder*) builder) {
  String string = String_new(builder->buffer, builder->size, true);
  builder->buffer = null;
  builder->size = 0;
  builder->capacity = 0;
  return string;
}

String ViewStrings_toJson(BORROW(ViewString) vs, bool forging) {
  StringBuilder builder;
  StringBuilder_init(&builder);
  if (forging) StringBuilder_addChar(&builder, '"');
  for (size_t i = 0; i < vs.size; i++) {
    char c = vs.buffer[i];
    if (c == '\n') {
      StringBuilder_addChar(&builder, '\\');
      StringBuilder_addChar(&builder, 'n');
    }
    else if (c == '"') {
      StringBuilder_addChar(&builder, '\\');
      StringBuilder_addChar(&builder, '"');
    }
    else if (c == '\\') {
      StringBuilder_addChar(&builder, '\\');
      StringBuilder_addChar(&builder, '\\');
    }
    else {
      StringBuilder_addChar(&builder, c);
    }
  }
  if (forging) StringBuilder_addChar(&builder, '"');
  return StringBuilder_take(&builder);
}
