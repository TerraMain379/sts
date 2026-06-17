#include "sources.h"

#include "errors.h"
#include "utils.h"
#include "allocator.h"
#include "print_utils.h"
#include "print_json_utils.h"


#define PNAME Sources
#define PTYPE OWNER(Source)
#define PFREEFUN Source_free
#define BASE_LIST List
#include "plist.c.h"
#undef PNAME
#undef PTYPE
#undef PFREEFUN
#undef BASE_LIST


dec_print(Source) {
  print_struct_init;
  print_field_value(String, filename);
  print_field_value(SourceSpan, span);
  print_struct_return;
}
dec_print_json(Source) {
  print_json_struct_init;
  print_json_field_value(String, filename);
  print_json_field_value(SourceSpan, span);
  print_json_struct_return;
}

dec_print(SourceSpan) {
  print_struct_init;
  print_field_value(SourceCoords, start);
  print_field_value(SourceCoords, end);
  print_struct_return;
}
dec_print_json(SourceSpan) {
  print_json_struct_init;
  print_json_field_value(SourceCoords, start);
  print_json_field_value(SourceCoords, end);
  print_json_struct_return;
}

dec_print(SourceCoords) {
  print_struct_init;
  print_field_value(size_t, lineNumber);
  print_field_value(size_t, charNumber);
  print_struct_return;
}
dec_print_json(SourceCoords) {
  print_json_struct_init;
  print_json_field_value(size_t, lineNumber);
  print_json_field_value(size_t, charNumber);
  print_json_struct_return;
}

dec_print(Sources) {
  print_glist(Sources, Source,*,);
}
dec_print_json(Sources) {
  print_json_glist(Sources, Source,*,);
}


SourcePointDescription SPD_new(SPDMode mode, int value, SPDFlags flags) {
  return (SourcePointDescription) {
    .mode = mode,
    .value = value,
    .flags = flags,
  };
}
SPDFlags SPDFlags_default() {
  return (SPDFlags) {
    .lineTransitionAfterCharShift = false
  };
}
SourcePointDescription SPD_new1(SPDMode mode, int value) {
  return (SourcePointDescription) {
    .mode = mode,
    .value = value,
    .flags = SPDFlags_default(),
  };
}
SourcePointDescription SPD_new2(SPDMode mode) {
  return (SourcePointDescription) {
    .mode = mode,
    .value = 1,
    .flags = SPDFlags_default(),
  };
}


void calculatePosition_backCharShift(Iter* iter, SourcePointDescription point) {
  if (point.flags.lineTransitionAfterCharShift) {
    iter->curr -= point.value;
  }
  else {
    int counter = point.value;
    if (counter > iter->curr - iter->start) {
      while (counter > 0) {
        Iter_unsafeBackChar(iter);
        if (Iter_currChar(iter) == '\n') {
          Iter_nextChar(iter);
          break;
        }
        if (iter->curr == iter->start) break;
        counter--;
      }
    }
    else {
      while (counter > 0) {
        Iter_unsafeBackChar(iter);
        if (Iter_currChar(iter) == '\n') {
          Iter_nextChar(iter);
          break;
        }
        counter--;
      }
    }
  }
}
void calculatePosition_forwardCharShift(Iter* iter, SourcePointDescription point) {
  if (point.flags.lineTransitionAfterCharShift) {
    if ((size_t) point.value > iter->size) {
      iter->curr += iter->size;
      iter->size = 0;
    }
    else {
      iter->curr += point.value;
      iter->size -= point.value;
    }
  }
  else {
    int counter = point.value;
    if (iter->size < (size_t) counter && counter >= 0) {
      while (counter > 0) {
        char c = Iter_nextChar(iter);
        if (c == '\0' || c == '\n') {
          Iter_unsafeBackChar(iter);
          break;
        }
        counter--;
      }
    }
    else {
      while (counter > 0) {
        char c = Iter_nextChar(iter);
        if (c == '\n') {
          Iter_unsafeBackChar(iter);
          break;
        }
        counter--;
      }
    }
  }
}

void calculateLeftPosition_currLine(Iter* iter, SourcePointDescription leftPoint) {
  do {
    Iter_unsafeBackChar(iter);
    if (iter->start == iter->curr) return;
  } while (Iter_currChar(iter) != '\n');
  Iter_nextChar(iter);
}
void calculateLeftPosition_backLineShift(Iter* iter, SourcePointDescription leftPoint) {
  int counter = leftPoint.value;
  while (counter >= 0) {
    Iter_unsafeBackChar(iter);
    if (iter->start == iter->curr) return;
    if (Iter_currChar(iter) == '\n') {
      counter--;
    }
  }
  Iter_nextChar(iter);
}
void calculateLeftPosition_forwardLineShift(Iter* iter, SourcePointDescription leftPoint) {
  int counter = leftPoint.value;
  if (counter == 0) {
    do {
      Iter_unsafeBackChar(iter);
      if (iter->start == iter->curr) return;
    } while (Iter_currChar(iter) != '\n');
    Iter_nextChar(iter);
  }
  else {
    while (counter > 0) {
      if (Iter_currChar(iter) == '\n') {
        counter--;
      }
      if (Iter_nextChar(iter) == '\0') break;
    }
  }
}
void calculateLeftPosition_currWord(Iter* iter, SourcePointDescription leftPoint) {
  char c = Iter_currChar(iter);
  bool type = Chars_isLetter(c) || Chars_isDigit(c) || c == '_';
  Iter_unsafeBackChar(iter);
  while (iter->curr > iter->start) {
    c = Iter_currChar(iter);
    bool currType = Chars_isLetter(c) || Chars_isDigit(c) || c == '_';
    if (type != currType) {
      Iter_nextChar(iter);
      break;
    }
    Iter_unsafeBackChar(iter);
  }
  Iter_nextChar(iter);
}
void calculateLeftPosition_backWordShift(Iter* iter, SourcePointDescription leftPoint) {
  char c = Iter_currChar(iter);
  bool type = Chars_isLetter(c) || Chars_isDigit(c) || c == '_';
  int counter = leftPoint.value * 2 + 1; // for swap context count
  while (counter > 0) {
    Iter_unsafeBackChar(iter);
    if (iter->curr == iter->start) break;

    c = Iter_currChar(iter);
    bool currType = Chars_isLetter(c) || Chars_isDigit(c) || c == '_';
    if (type != currType) {
      type = currType;
      counter--;
    }
  }
}
void calculateLeftPosition_forwardWordShift(Iter* iter, SourcePointDescription leftPoint) {
  char c = Iter_currChar(iter);
  bool type = Chars_isLetter(c) || Chars_isDigit(c) || c == '_';
  int counter = leftPoint.value * 2; // for swap context count
  while (counter > 0) {
    char c = Iter_nextChar(iter);
    if (iter->curr == iter->start) break;

    bool currType = Chars_isLetter(c) || Chars_isDigit(c) || c == '_';
    if (type != currType) {
      type = currType;
      counter--;
    }
  }
}

Iter calculateLeftPosition(BORROW(Iter*) origIter, SourcePointDescription leftPoint) {
  Iter tmpIter = Iter_copy(origIter);
  Iter* iter = &tmpIter;

  if (leftPoint.mode == SPDMode_CURR_CHAR) { }
  else if (leftPoint.mode == SPDMode_BACK_CHAR_SHIFT) {
    calculatePosition_backCharShift(iter, leftPoint);
  }
  else if (leftPoint.mode == SPDMode_FORWARD_CHAR_SHIFT) {
    calculatePosition_forwardCharShift(iter, leftPoint);
  }
  else if (leftPoint.mode == SPDMode_CURR_LINE) {
    calculateLeftPosition_currLine(iter, leftPoint);
  }
  else if (leftPoint.mode == SPDMode_BACK_LINE_SHIFT) {
    calculateLeftPosition_backLineShift(iter, leftPoint);
  }
  else if (leftPoint.mode == SPDMode_FORWARD_LINE_SHIFT) {
    calculateLeftPosition_forwardLineShift(iter, leftPoint);
  }
  else if (leftPoint.mode == SPDMode_CURR_WORD) {
    calculateLeftPosition_currWord(iter, leftPoint);
  }
  else if (leftPoint.mode == SPDMode_BACK_WORD_SHIFT) {
    calculateLeftPosition_backWordShift(iter, leftPoint);
  }
  else if (leftPoint.mode == SPDMode_FORWARD_WORD_SHIFT) {
    calculateLeftPosition_forwardWordShift(iter, leftPoint);
  }
  return *iter;
}

void calculateRightPosition_currLine(Iter* iter, SourcePointDescription rightPoint) {
  while (Iter_currChar(iter) != '\n') {
    if (Iter_nextChar(iter) == '\0') break;
  }
  Iter_unsafeBackChar(iter);
}
void calculateRightPosition_backLineShift(Iter* iter, SourcePointDescription rightPoint) {
  int counter = rightPoint.value;
  if (counter == 0) {
    while (Iter_currChar(iter) != '\n') {
      if (Iter_nextChar(iter) == '\0') break;
    }
    Iter_unsafeBackChar(iter);
  }
  else {
    while (counter > 0) {
      Iter_unsafeBackChar(iter);
      if (iter->start == iter->curr) return;
      if (Iter_currChar(iter) == '\n') counter--;
    }
    Iter_unsafeBackChar(iter);
  }
}
void calculateRightPosition_forwardLineShift(Iter* iter, SourcePointDescription rightPoint) {
  int counter = rightPoint.value;
  while (counter >= 0) {
    if (Iter_currChar(iter) == '\0') break;
    if (Iter_nextChar(iter) == '\n') {
      counter--;
    }
  }
  Iter_unsafeBackChar(iter);
}
void calculateRightPosition_currWord(Iter* iter, SourcePointDescription rightPoint) {
  char c = Iter_currChar(iter);
  bool type = Chars_isLetter(c) || Chars_isDigit(c) || c == '_';
  Iter_unsafeBackChar(iter);
  while (iter->curr > iter->start) {
    c = Iter_currChar(iter);
    bool currType = Chars_isLetter(c) || Chars_isDigit(c) || c == '_';
    if (type != currType) {
      Iter_unsafeBackChar(iter);
      break;
    }
    Iter_nextChar(iter);
  }
}
void calculateRightPosition_backWordShift(Iter* iter, SourcePointDescription rightPoint) {
  char c = Iter_currChar(iter);
  bool type = Chars_isLetter(c) || Chars_isDigit(c) || c == '_';
  int counter = rightPoint.value * 2; // for swap context count
  while (counter > 0) {
    Iter_unsafeBackChar(iter);
    if (iter->curr == iter->start) break;

    c = Iter_currChar(iter);
    bool currType = Chars_isLetter(c) || Chars_isDigit(c) || c == '_';
    if (type != currType) {
      type = currType;
      counter--;
    }
  }
}
void calculateRightPosition_forwardWordShift(Iter* iter, SourcePointDescription rightPoint) {
  char c = Iter_currChar(iter);
  bool type = Chars_isLetter(c) || Chars_isDigit(c) || c == '_';
  int counter = rightPoint.value * 2 + 1; // for swap context count
  while (counter > 0) {
    char c = Iter_nextChar(iter);
    if (iter->curr == iter->start) break;

    bool currType = Chars_isLetter(c) || Chars_isDigit(c) || c == '_';
    if (type != currType) {
      type = currType;
      counter--;
    }
  }
  Iter_unsafeBackChar(iter);
}

Iter calculateRightPosition(BORROW(Iter*) origIter, SourcePointDescription rightPoint) {
  Iter tmpIter = Iter_copy(origIter);
  Iter* iter = &tmpIter;

  if (rightPoint.mode == SPDMode_CURR_CHAR) {
  }
  else if (rightPoint.mode == SPDMode_BACK_CHAR_SHIFT) {
    calculatePosition_backCharShift(iter, rightPoint);
  }
  else if (rightPoint.mode == SPDMode_FORWARD_CHAR_SHIFT) {
    calculatePosition_forwardCharShift(iter, rightPoint);
  }
  else if (rightPoint.mode == SPDMode_CURR_LINE) {
    calculateRightPosition_currLine(iter, rightPoint);
  }
  else if (rightPoint.mode == SPDMode_BACK_LINE_SHIFT) {
    calculateRightPosition_backLineShift(iter, rightPoint);
  }
  else if (rightPoint.mode == SPDMode_FORWARD_LINE_SHIFT) {
    calculateRightPosition_forwardLineShift(iter, rightPoint);
  }
  else if (rightPoint.mode == SPDMode_CURR_WORD) {
    calculateRightPosition_currWord(iter, rightPoint);
  }
  else if (rightPoint.mode == SPDMode_BACK_WORD_SHIFT) {
    calculateRightPosition_backWordShift(iter, rightPoint);
  }
  else if (rightPoint.mode == SPDMode_FORWARD_WORD_SHIFT) {
    calculateRightPosition_forwardWordShift(iter, rightPoint);
  }

  return *iter;
}

SourceCoords calculateIterCoords(BORROW(Iter*) origIter) {
  Iter tmpIter = Iter_copy(origIter);
  Iter* iter = &tmpIter;

  SourceCoords coords = (SourceCoords) {
    .lineNumber = 1,
    .charNumber = 1
  };
  
  while (iter->curr != iter->start) {
    Iter_unsafeBackChar(iter);
    char c = Iter_currChar(iter);
    if (c == '\n') {
      break;
    }
    coords.charNumber++;
  }
  while (iter->curr != iter->start) {
    Iter_unsafeBackChar(iter);
    char c = Iter_currChar(iter);
    if (c == '\n') {
      coords.lineNumber++;
    }
  }
  return coords;
}

void loadCache(Iter leftIter, Iter rightIter, bool strict, String* cachedData, bool* cachedDataIsValid) {
  size_t len = rightIter.curr - leftIter.curr + 1;
  if (len < 200 || strict) {
    char* str = A_xloc((len + 1) * sizeof(char));
    Strings_strcpy(str, len + 1, leftIter.curr, len);
    str[len] = '\0';
    *cachedData = String_of(str);
    *cachedDataIsValid = true;
  }
}



Source Source_byIter(BORROW(ViewString) filename, BORROW(Iter*) iter, SourcePointDescription leftPoint, SourcePointDescription rightPoint) {
  return Source_byIters(filename, iter, leftPoint, iter, rightPoint);
}
Source Source_byIters(BORROW(ViewString) filename, BORROW(Iter*) leftIter, SourcePointDescription leftPoint, BORROW(Iter*) rightIter, SourcePointDescription rightPoint) {
  if (leftIter->start != rightIter->start) {
    Errors_internal_unexpectedBehavior(ViewString_of("Source_byIters"), ViewString_of("leftIter->start != rightIter->start"));
    non_call_return (Source) {0};
  }
  Iter l = calculateLeftPosition(leftIter, leftPoint);
  Iter r = calculateRightPosition(rightIter, rightPoint);

  if (l.curr > r.curr) {
    Errors_internal_unexpectedBehavior(ViewString_of("Source_byIters"), ViewString_of("l.curr > r.curr"));
    non_call_return (Source) {0};
  }
  SourceCoords lc = calculateIterCoords(&l);
  SourceCoords rc = calculateIterCoords(&r);

  String cachedData = {
    .buffer = null,
    .bufferOnHeap = false,
    .size = 0,
  };
  bool cachedDataIsValid = false;
  loadCache(l, r, false, &cachedData, &cachedDataIsValid);

  Source source = (Source) {
    .filename = String_copy(filename),
    .span = {
      .start = lc,
      .end = rc,
    },
    .startIter = l,
    .endIter = r,
    .cachedData = cachedData,
    .cachedDataIsValid = cachedDataIsValid
  };
  return source;
}
void_errno Source_updateCache(Source* source) {
  String_free(&source->cachedData);
  loadCache(
    source->startIter,
    source->endIter,
    true,
    &source->cachedData,
    &source->cachedDataIsValid
  );
}
void Source_free(Source* source) {
  String_free(&source->filename);
  String_free(&source->cachedData);
}
