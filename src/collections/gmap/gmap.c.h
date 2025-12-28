#include "allocator.h"

// #define NAME ...
// #define TYPE ...
// #define NULLV ...
// #include "gmap.c.h"
// #undef NAME
// #undef TYPE
// #undef NULLV


// logic for generate names for structs
#define CONCAT(a, b) a ## _ ## b
#define ELEMENT(name) CONCAT(name, element)
#define FUNCTION(name, fun) CONCAT(name, fun)

// void FUNCTION(NAME, init)(NAME* map);
// ELEMENT(NAME)* FUNCTION(NAME, getElementByHash)(NAME* map, int hash);
// ELEMENT(NAME)* FUNCTION(NAME, getElement)(NAME* map, const String key);
// type_errno(TYPE) FUNCTION(NAME, get)(NAME* map, const String key);
// bool FUNCTION(NAME, contains)(NAME* map, const String key);const String key
// type_errno(TYPE) FUNCTION(NAME, set)(NAME* map, const String key, TYPE value);
// type_errno(TYPE) FUNCTION(NAME, remove)(NAME* map, const String key);
// void FUNCTION(NAME, free)(NAME* map);

int FUNCTION(NAME, getHash)(const char* key) {
  int hash = 0;
  while (*key) {
    hash = hash * 31 + *key;
    key++;
  }
  return hash;
}

void FUNCTION(NAME, init)(NAME* map) {
  map->size = 0;
  map->first = 0;
  map->last = 0;
}
WAKE(ELEMENT(NAME)) FUNCTION(NAME, getElementByHash)(BORROW(NAME) map, int hash) {
  if (map->size == 0) return 0;
  ELEMENT(NAME)* element = map->first;
  do {
    if (element->hash == hash) return element;
    element = element->next;
  } while (element);
  return 0;
}

WAKE(ELEMENT(NAME)) FUNCTION(NAME, getElement)(BORROW(NAME) map, const String key) {
  int hash = FUNCTION(NAME, getHash)(key.buffer);
  ELEMENT(NAME)* element = FUNCTION(NAME, getElementByHash)(map, hash);
  if (!element) return 0;
  ELEMENT(NAME)* next = element->next;
  if (next && next->hash == hash) {
    do {
      if (Strings_equals(key, element->key)) {
        return element;
      }
      element = element->next;
    } while (element && element->hash == hash);
  }
  else {
    if (Strings_equals(key, element->key)) {
      return element;
    }
  }
  return 0;
}

type_errno(TYPE*) FUNCTION(NAME, get)(BORROW(NAME) map, const String key) {
  ELEMENT(NAME)* element = FUNCTION(NAME, getElement)(map, key);
  if (element) {
    errno = 0; return & element->value;
  }
  errno = 1; return 0;
}
bool FUNCTION(NAME, contains)(BORROW(NAME) map, const String key) {
  ELEMENT(NAME)* element = FUNCTION(NAME, getElement)(map, key);
  return (bool) element;
}
type_errno(TYPE) FUNCTION(NAME, set)(NAME* map, const String key, TYPE value) {
  int hash = FUNCTION(NAME, getHash)(key.buffer);
  ELEMENT(NAME)* hashElement = FUNCTION(NAME, getElementByHash)(map, hash);

  if (!hashElement) {
    ELEMENT(NAME)* newElement = A_loc(sizeof(ELEMENT(NAME)));
    newElement->key = String_copy(&key);
    newElement->hash = hash;
    newElement->value = value;
    newElement->next = 0;
    ELEMENT(NAME)* last = map->last;
    if (last) {
      last->next = newElement;
      map->last = newElement;
    }
    else {
      map->first = newElement;
      map->last = newElement;
    }
    map->size++;
    
    errno = 0; return NULLV;
  }

  ELEMENT(NAME)* element = hashElement;
  do {
    if (Strings_equals(key, element->key)) {
      TYPE oldValue = element->value;
      element->value = value;
      errno = 1; return oldValue;
    }
    element = element->next;
  } while (element && element->hash == hash);

  ELEMENT(NAME)* newElement = A_loc(sizeof(ELEMENT(NAME)));
  newElement->key = String_copy(&key);
  newElement->hash = hash;
  newElement->value = value;

  newElement->next = hashElement->next;
  hashElement->next = newElement;
  map->size++;
  errno = 0; return NULLV;
}
type_errno(TYPE) FUNCTION(NAME, remove)(NAME* map, const String key) {
  int hash = FUNCTION(NAME, getHash)(key.buffer);
  ELEMENT(NAME)* element = map->first;
  ELEMENT(NAME)* prev = 0;
  while (element) {
    if (element->hash == hash) {
      do {
        if (Strings_equals(key, element->key)) {
          TYPE value = element->value;

          if (prev) prev->next = element->next;
          else if (map->first == element) map->first = element->next;
          if (map->last == element) map->last = prev;

          String_free(& element->key);
          A_free(element);

          map->size--;
          errno = 0; return value;
        }
        element = element->next;
      } while (element);
      errno = 2; return NULLV;
    }
    prev = element;
    element = element->next;
  }
  errno = 1; return NULLV;
}
void FUNCTION(NAME, free)(BORROW(NAME) map) {
  ELEMENT(NAME)* element = map->first;
  while (element) {
    ELEMENT(NAME)* next = element->next;
    String_free(& element->key);
    A_free(element);
    element = next;
  }
  map->size = 0;
  map->first = 0;
  map->last = 0;
}
