#include <stdint.h>
#include <stddef.h>

#include "utils.h"
#include "strings.h"

// #####################################
// #            DEPRECATED             #
// #####################################

struct Map {
  size_t size;
  struct MapElement* first;
  struct MapElement* last;
};
struct MapElement {
  String key;
  int hash;
  void* value;
  struct MapElement* next;
};

void Map_init(struct Map* map);
struct MapElement* Map_getElementByHash(struct Map* map, int hash);
struct MapElement* Map_getElement(struct Map* map, const String key);
void* Map_get(struct Map* map, const String key);
bool Map_set(struct Map* map, const String key, void* value); // true if new element is gen
bool Map_remove(struct Map* map, const String key);
bool Map_removeAndFree(struct Map* map, const String key);
void Map_free(struct Map* map);
