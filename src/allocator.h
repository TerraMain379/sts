#include <stddef.h>

void* A_loc(size_t size);
void* A_xloc(size_t size);
void* A_reloc(void* ptr, size_t size);
void* A_xreloc(void* ptr, size_t size);
void A_free(void* ptr);
