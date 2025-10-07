#include "arraylist.h"

#include "allocator.h"

static inline bool validIndex(struct ArrayList* list, size_t index) {
  return index >= 0 && index < list->size;
}

void ArrayList_init(struct ArrayList* list, size_t capacity) {
  void** array = A_loc(sizeof(void*) * capacity);
  list->array = array;
  list->size = 0;
  list->capacity = capacity;
}
int ArrayList_setCapacity(struct ArrayList* list, size_t capacity) {
  if (capacity < list->capacity) return -1;
  else if (capacity == list->capacity) return 1;

  // void** array = A_loc(sizeof(void*) * capacity);
  // memcpy(array, list->array, list->capacity);
  // free(list->array);
  // list->array = array;
  list->array = A_reloc(list->array, sizeof(void*) * capacity);
  list->capacity = capacity;
  return 0;
}
void ArrayList_add(struct ArrayList* list, void* value) {
  if (list->capacity == list->size) {
    ArrayList_setCapacity(list, list->capacity*2);
  }
  list->array[list->size] = value;
  list->size++;
}
bool ArrayList_insert(struct ArrayList* list, size_t index, void* value) {
  if (list->size >= index) {
    ArrayList_add(list, value);
    return false;
  }
  if (list->capacity == list->size) {
    ArrayList_setCapacity(list, list->capacity*2);
  }
  for (size_t i = list->size; i > index; i--) {
    list->array[i] = list->array[i-1];
  }
  list->array[index] = value;
  list->size++;
  return true;
}
bool ArrayList_set(struct ArrayList* list, size_t index, void* value) {
  if (list->size <= index) {
    return false;
  }
  list->array[index] = value;
  return true;
}
bool ArrayList_freeItem(struct ArrayList* list, size_t index) {
  if (validIndex(list, index)) {
    A_free(list->array[index]);
    return true;
  }
  return false;
}
bool ArrayList_remove(struct ArrayList* list, size_t index) {
  if (validIndex(list, index)) {
    for (size_t i = index; i < list->size - 1; i++) {
      list->array[i] = list->array[i + 1];
    }
    list->size--;
    return true;
  }
  return false;
}
bool ArrayList_removeAndFree(struct ArrayList* list, size_t index) {
  ArrayList_freeItem(list, index);
  return ArrayList_remove(list, index);
}
void* ArrayList_pop(struct ArrayList* list) {
  // TODO
}
void* ArrayList_get(struct ArrayList* list, size_t index, int* code) {
  if (validIndex(list, index)) {
    *code = 0;
    return list->array[index];
  }
  *code = -1;
  return 0;
}
void ArrayList_free(struct ArrayList* list) {
  A_free(list->array);
}
