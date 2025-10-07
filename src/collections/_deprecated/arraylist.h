#pragma once

#include "utils.h"

struct ArrayList {
  void** array;
  size_t size;
  size_t capacity;
};

void ArrayList_init(struct ArrayList* list, size_t capacity);
int ArrayList_setCapacity(struct ArrayList* list, size_t capacity);
void ArrayList_add(struct ArrayList* list, void* value);
bool ArrayList_insert(struct ArrayList* list, size_t index, void* value);
bool ArrayList_set(struct ArrayList* list, size_t index, void* value);
bool ArrayList_freeItem(struct ArrayList* list, size_t index);
bool ArrayList_remove(struct ArrayList* list, size_t index);
bool ArrayList_removeAndFree(struct ArrayList* list, size_t index);
void* ArrayList_pop(struct ArrayList* list);
void* ArrayList_get(struct ArrayList* list, size_t index, int* code);
void ArrayList_free(struct ArrayList* list);
