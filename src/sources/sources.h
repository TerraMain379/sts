#pragma once

#include "utils.h"
#include "string.h"
#include "iter.h"
#include "list.h"
#include "prints.h"

typedef enum SPDMode {
  SPDMode_NULL = 0,
  SPDMode_CURR_CHAR,
  SPDMode_BACK_CHAR_SHIFT,
  SPDMode_FORWARD_CHAR_SHIFT,
  
  SPDMode_CURR_LINE,
  SPDMode_BACK_LINE_SHIFT,
  SPDMode_FORWARD_LINE_SHIFT,

  SPDMode_CURR_WORD,
  SPDMode_BACK_WORD_SHIFT,
  SPDMode_FORWARD_WORD_SHIFT,
} SPDMode;

typedef struct SPDFlags {
  bool lineTransitionAfterCharShift;
} SPDFlags;

SPDFlags SPDFlags_default();

typedef struct SourcePointDescription {
  SPDMode mode;
  int value;
  SPDFlags flags;
} SourcePointDescription;

SourcePointDescription SPD_new(SPDMode mode, int value, SPDFlags flags);
SourcePointDescription SPD_new1(SPDMode mode, int value);
SourcePointDescription SPD_new2(SPDMode mode);
#define SPD_new1_double(mode, value) SPD_new1(mode, value),SPD_new1(mode, value)
#define SPD_new2_double(mode) SPD_new2(mode),SPD_new2(mode)



typedef struct SourceCoords {
  size_t lineNumber;
  size_t charNumber;
} SourceCoords;
dec_prints(SourceCoords);
typedef struct SourceSpan {
  SourceCoords start;
  SourceCoords end;
} SourceSpan;
dec_prints(SourceSpan);

typedef struct Source {
  OWNER(String) filename;
  SourceSpan span;
  Iter startIter;
  Iter endIter;

  OWNER(String) cachedData;
  bool cachedDataIsValid;
} Source;
dec_prints(Source);

Source Source_byIter(BORROW(ViewString) filename, BORROW(Iter*) iter, SourcePointDescription leftPoint, SourcePointDescription rightPoint);
Source Source_byIters(BORROW(ViewString) filename, BORROW(Iter*) leftIter, SourcePointDescription leftPoint, BORROW(Iter*) rightIter, SourcePointDescription rightPoint);

void_errno Source_updateCache(Source* source);
void Source_free(Source* source);


#define PNAME Sources
#define PTYPE OWNER(Source)
#define PFREEFUN Source_free
#define BASE_LIST List
#include "plist.h"
#undef PNAME
#undef PTYPE
#undef PFREEFUN
#undef BASE_LIST
dec_prints(Sources);
