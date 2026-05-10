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
void StringBuilder_addString(StringBuilder* builder, BORROW(ViewString) vs) {
  StringBuilder_applyCapacity(builder, builder->size + vs->size + 1);
  Strings_strlcpy(builder->buffer + builder->size, vs->buffer, vs->size + 1);
  builder->size += vs->size;
}

ViewString StringBuilder_get(StringBuilder* builder) {
  return ViewString_new(builder->buffer, builder->size);
}
String StringBuilder_take(StringBuilder* builder) {
  String string = String_new(builder->buffer, builder->size, true);
  builder->buffer = null;
  builder->size = 0;
  builder->capacity = 0;
  return string;
}
