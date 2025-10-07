#include "gmap.h"

#include "allocator.h"

// #define TYPE ...
// #define NAME ...
// #define NULLV ...
// #define FREEFUN ...
// #define ISPOINTER ...
// #include "gmap.c.h"
// #undef TYPE
// #undef NAME
// #undef NULLV
// #undef FREEFUN
// #undef ISPOINTER

static inline int Map_hash(const char* key) {
  int hash = 0;
  while (*key) {
    hash = hash * 31 + *key;
    key++;
  }
  return hash;
}

// logic for generate names for structs
#define CONCAT(a, b) a ## _ ## b
#define ELEMENT(name) CONCAT(name, element)
#define FUNCTION(name, fun) CONCAT(name, fun)

void FUNCTION(NAME, init)(NAME* map) {
  map->size = 0;
  map->first = 0;
  map->last = 0;
}
ELEMENT(NAME)* FUNCTION(NAME, getElementByHash)(NAME* map, int hash) {
  if (map->size == 0) return 0;
  ELEMENT(NAME)* element = map->first;
  do {
    if (element->hash == hash) return element;
    element = element->next;
  } while (element);
  return 0;
}

ELEMENT(NAME)* FUNCTION(NAME, getElement)(NAME* map, const String key) {
  int hash = Map_hash(key.buffer);
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
    return 0;
  }
  else {
    if (Strings_equals(key, element->key)) {
      return element;
    }
    return 0;
  }
}

type_errno(TYPE) FUNCTION(NAME, get)(NAME* map, const String key) {
  ELEMENT(NAME)* element = FUNCTION(NAME, getElement)(map, key);
  if (element) {
    errno = 0; return element->value;
  }
  errno = 1; return NULLV;
}
bool FUNCTION(NAME, set)(NAME* map, const String key, TYPE value, 
  #ifdef FREEFUN
    bool deleteRequired
  #endif
) { // true if new element is gen
  int hash = Map_hash(key.buffer);
  ELEMENT(NAME)* hashElement = FUNCTION(NAME, getElementByHash)(map, hash);

  if (!hashElement) {
    ELEMENT(NAME)* newElement = A_loc(sizeof(ELEMENT(NAME)));
    newElement->key = String_copy(&key);
    newElement->hash = hash;
    newElement->value = value;
    #ifdef FREEFUN
      newElement->deleteRequired = deleteRequired;
    #endif
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
    
    return true;
  }

  ELEMENT(NAME)* element = hashElement;
  do {
    if (Strings_equals(key, element->key)) {
      #ifdef FREEFUN
        if (element->deleteRequired) {
          #ifdef ISPOINTER
            FREEFUN(element->value);
          #endif
          #ifndef ISPOINTER
            FREEFUN(& element->value);
          #endif
        }
        element->deleteRequired = deleteRequired;
      #endif
      element->value = value;
      return false;
    }
    element = element->next;
  } while (element && element->hash == hash);

  ELEMENT(NAME)* newElement = A_loc(sizeof(ELEMENT(NAME)));
  newElement->key = String_copy(&key);
  newElement->hash = hash;
  newElement->value = value;
  #ifdef FREEFUN
    newElement->deleteRequired = deleteRequired;
  #endif

  newElement->next = hashElement->next;
  hashElement->next = newElement;
  map->size++;
  return true;
}
void_errno FUNCTION(NAME, remove)(NAME* map, const String key) {
  int hash = Map_hash(key.buffer);
  ELEMENT(NAME)* element = map->first;
  ELEMENT(NAME)* prev = 0;
  while (element) {
    if (element->hash == hash) {
      do {
        if (Strings_equals(key, element->key)) {
          String_free(& element->key);
          #ifdef FREEFUN
            if (element->deleteRequired) {
              #ifdef ISPOINTER
                FREEFUN(element->value);
              #endif
              #ifndef ISPOINTER
                FREEFUN(& element->value);
              #endif
            }
          #endif

          if (prev) prev->next = element->next;
          else if (map->first == element) map->first = element->next;
          if (map->last == element) map->last = prev;
          A_free(element);

          map->size--;
          errno = 0; return;
        }
        element = element->next;
      } while (element);
      errno = 2; return;
    }
    prev = element;
    element = element->next;
  }
  errno = 1; return;
}
type_errno(TYPE) FUNCTION(NAME, getOwnership)(NAME* map, const String key) {
  int hash = Map_hash(key.buffer);
  ELEMENT(NAME)* element = map->first;
  while (element) {
    if (element->hash == hash) {
      do {
        if (Strings_equals(key, element->key)) {
          TYPE value = element->value;
          String_free(& element->key);
          A_free(element);
          errno = 0; return value;
        }
        element = element->next;
      } while (element);
      errno = 2; return NULLV;
    }
    element = element->next;
  }
  errno = 1; return NULLV;
}
void FUNCTION(NAME, free)(NAME* map) {
  ELEMENT(NAME)* element = map->first;
  while (element) {
    ELEMENT(NAME)* next = element->next;
    String_free(& element->key);
    #ifdef FREEFUN
      if (element->deleteRequired) {
        #ifdef ISPOINTER
          FREEFUN(element->value);
        #endif
        #ifndef ISPOINTER
          FREEFUN(& element->value);
        #endif
      }
    #endif
    A_free(element);
    element = next;
  }
  map->size = 0;
  map->first = 0;
  map->last = 0;
}
