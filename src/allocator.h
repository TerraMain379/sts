#include <stddef.h>

void* A_loc(size_t size);
void* A_xloc(size_t size);
void* A_reloc(void* ptr, size_t size);
void* A_xreloc(void* ptr, size_t size);
void A_free(void* ptr);

#ifdef BUILD_TESTS
  size_t A_getCounter();
  size_t A_getLocCounter();
  size_t A_getRelocCounter();
  size_t A_getFreeCounter();
  bool A_checkLoc(void* ptr);
  size_t A_getSize(void* ptr);
#endif
