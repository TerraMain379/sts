#include "utils.h"
#include "string.h"
#include "iter.h"

typedef struct Source {
  String filename;
  size_t startLineNumber;
  size_t endLineNumber;
  size_t startCharNumber;
  size_t endCharNumber;
  String cachedData;
  bool cacheIsValid;
} Source;

Source Source_new(String filename, size_t startLineNumber, size_t endLineNumber, size_t startCharNumber, size_t endCharNumber);
type_errno(Source) Source_byIter(String filename, const Iter iter, size_t forwardShift, size_t backwardShift);
type_errno(Source) Source_byIters(String filename, const Iter startIter, const Iter endIter);
void_errno Source_updateCache(Source* source);
void Source_free(Source* source);

#define NAME Sources
#define TYPE Source
#define NULLV (Source) {0}
#define FREEFUN Source_free
#include "glist.h"
#undef NAME
#undef TYPE
#undef NULLV
#undef FREEFUN
