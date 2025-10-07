#include "map.h"

#include "allocator.h"

// #####################################
// #            DEPRECATED             #
// #####################################

static int Map_hash(const char* key) {
  int hash = 0;
  while (*key) {
    hash = hash * 31 + *key;
    key++;
  }
  return hash;
}

void Map_init(struct Map* map) {
  map->size = 0;
  map->first = 0;
  map->last = 0;
}
struct MapElement* Map_getElementByHash(struct Map* map, int hash) {
  if (map->size == 0) return 0;
  struct MapElement* element = map->first;
  do {
    if (element->hash == hash) return element;
    element = element->next;
  } while (element);
  return 0;
}
struct MapElement* Map_getElement(struct Map* map, const String key) {
  int hash = Map_hash(key.buffer);
  struct MapElement* element = Map_getElementByHash(map, hash);
  if (!element) return 0;
  struct MapElement* next = element->next;
  if (next && next->hash == hash) {
    do {
      if (Strings_equals(key, element->key)) {
        return element;
      }
      element = element->next;
    } while (element && element->hash == hash);
    return 0;
  }
  else {
    if (Strings_equals(key, element->key)) {
      return element;
    }
    return 0;
  }
}
void* Map_get(struct Map* map, const String key) {
  struct MapElement* element = Map_getElement(map, key);
  if (element) return element->value;
  return 0;
}
bool Map_set(struct Map* map, const String key, void* value) {
  int hash = Map_hash(key.buffer);
  struct MapElement* hashElement = Map_getElementByHash(map, hash);

  if (!hashElement) {
    struct MapElement* newElement = A_loc(sizeof(struct MapElement));
    newElement->key = String_copy(key);
    newElement->hash = hash;
    newElement->value = value;
    newElement->next = 0;

    struct MapElement* last = map->last;
    if (last) {
      last->next = newElement;
      map->last = newElement;
    }
    else {
      map->first = newElement;
      map->last = newElement;
    }
    map->size++;
    return true;
  }

  struct MapElement* element = hashElement;
  do {
    if (Strings_equals(key, element->key)) {
      element->value = value;
      return false;
    }
    element = element->next;
  } while (element && element->hash == hash);

  struct MapElement* newElement = A_loc(sizeof(struct MapElement));
  newElement->key = String_copy(key);
  newElement->hash = hash;
  newElement->value = value;

  newElement->next = hashElement->next;
  hashElement->next = newElement;
  map->size++;
  return true;
}
bool Map_remove(struct Map* map, const String key) {
  int hash = Map_hash(key.buffer);
  struct MapElement* element = map->first;
  struct MapElement* prev = 0;
  while (element) {
    if (element->hash == hash) {
      do {
        if (Strings_equals(key, element->key)) {
          String_free(& element->key);
          A_free(element);
          return true;
        }
        prev = element;
        element = element->next;
      } while (element);
      return false;
    }
    prev = element;
    element = element->next;
  }
  return false;
}
bool Map_removeAndFree(struct Map* map, const String key) {

}
void Map_free(struct Map* map) {
  struct MapElement* element = map->first;
  while (element) {
    struct MapElement* next = element->next;
    String_free(& element->key);
    A_free(element);
    element = next;
  }
}
