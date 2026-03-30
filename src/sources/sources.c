#include "sources.h"

#include "utils.h"
#include "allocator.h"


#define NAME Sources
#define TYPE Source
#define NULLV (Source) {0}
#define FREEFUN Source_free
#include "glist.c.h"
#undef NAME
#undef TYPE
#undef NULLV
#undef FREEFUN


Source Source_new(String filename, size_t startLineNumber, size_t endLineNumber, size_t startCharNumber, size_t endCharNumber) {
  return (Source) {
    .filename = filename,
    .startLineNumber = startLineNumber,
    .endLineNumber = endLineNumber,
    .startCharNumber = startCharNumber,
    .endCharNumber = endCharNumber,
    .cacheIsValid = false
  };
}
type_errno(Source) Source_byIter(String filename, Iter iter, size_t forwardShift, size_t backwardShift) {
  if (iter.curr - backwardShift < iter.start) {
    errno = 1; return (Source) {0};
  }
  if (iter.size < forwardShift) {
    errno = 2; return (Source) {0};
  }

  size_t size = forwardShift + backwardShift + 1;
  const char* start = iter.curr - backwardShift;
  char* data = A_loc(sizeof(char)*(size+1));
  strncpy(data, start, size);
  String cachedData = String_new(data, size, true);

  size_t startLineNumber = 0;
  size_t startCharNumber = 0;
  for (const char* p = iter.start; p < iter.curr - backwardShift; p++) {
    if (*p == '\n') {
      startLineNumber++;
      startCharNumber = 0;
    } else {
      startCharNumber++;
    }
  }

  size_t endLineNumber = 0;
  size_t endCharNumber = 0;
  for (size_t i = 0; i < size; i++) {
    if (data[i] == '\n') {
      endLineNumber++;
      endCharNumber = 0;
    } else {
      endCharNumber++;
    }
  }

  errno = 0; return (Source) {
    .filename = filename,
    .startLineNumber = startLineNumber,
    .endLineNumber = startLineNumber + endLineNumber,
    .startCharNumber = startCharNumber,
    .endCharNumber = endCharNumber,
    .cachedData = cachedData,
    .cacheIsValid = true
  };

}
type_errno(Source) Source_byIters(String filename, const Iter startIter, const Iter endIter) {
  return (Source) {0}; // TODO:
}
void_errno Source_updateCache(Source* source) {
  // TODO:
}
void Source_free(Source* source) {
  // TODO: 
}
