#include "strings.h"
#include "utils.h"

typedef struct StringBuilder {
  char* buffer;
  size_t size;
  size_t capacity;
} StringBuilder;

void StringBuilder_init(StringBuilder* builder);
void StringBuilder_free(StringBuilder* builder);
void StringBuilder_setCapacity(StringBuilder* builder, size_t capacity);

void StringBuilder_addChar(StringBuilder* builder, char c);
void StringBuilder_addString(StringBuilder* builder, BORROW(ViewString) vs);

ViewString StringBuilder_get(StringBuilder* builder);
String StringBuilder_take(StringBuilder* builder); // and free
