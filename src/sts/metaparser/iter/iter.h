typedef struct Iter {
  char* const curr;
  size_t size;
} Iter;

Iter Iter_new(const char* const str);
