#include <stddef.h>

#include "utils.h"
#include "memtypes.h"

#define ALLOCATORH_STR_HELPER(x) #x
#define ALLOCATORH_STR(x) ALLOCATORH_STR_HELPER(x)
#define ALLOCATORH_LOCATION __FILE__ ":" ALLOCATORH_STR(__LINE__)

#define A_loc(size) _A_loc(size, ALLOCATORH_LOCATION)
#define A_xloc(size) _A_xloc(size, ALLOCATORH_LOCATION)
#define A_reloc(ptr, size) _A_reloc(ptr, size, ALLOCATORH_LOCATION)
#define A_xreloc(ptr, size) _A_xreloc(ptr, size, ALLOCATORH_LOCATION)
#define A_free(ptr) _A_free(ptr, ALLOCATORH_LOCATION)

OWNER(void*) _A_loc(size_t size, BORROW(char*) location);
OWNER(void*) _A_xloc(size_t size, BORROW(char*) location);
OWNER(void*) _A_reloc(OWNER(void*) ptr, size_t size, BORROW(char*) location);
OWNER(void*) _A_xreloc(OWNER(void*) ptr, size_t size, BORROW(char*) location);
void _A_free(OWNER(void*) ptr, BORROW(char*) location);

#ifdef BUILD_TESTS
  size_t A_getCounter();
  size_t A_getLocCounter();
  size_t A_getRelocCounter();
  size_t A_getFreeCounter();
  bool A_checkLoc(BORROW(void*) ptr);
  size_t A_getSize(BORROW(void*) ptr);
#endif
