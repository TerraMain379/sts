#include "sources.h"

#include "utils.h"
#include "allocator.h"


#define PNAME Sources
#define PTYPE OWNER(Source)
#define PFREEFUN Source_free
#define BASE_LIST List
#include "plist.c.h"
#undef PNAME
#undef PTYPE
#undef PFREEFUN
#undef BASE_LIST


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


void calculatePositionBackCharShift(Iter* iter, SourcePointDescription point) {
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
void calculatePositionForwardCharShift(Iter* iter, SourcePointDescription point) {
  if (point.flags.lineTransitionAfterCharShift) {
    iter->curr += point.value;
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
Iter calculateLeftPosition(BORROW(Iter) origIter, SourcePointDescription leftPoint) {
  Iter tmpIter = Iter_copy(origIter);
  Iter* iter = &tmpIter;

  if (leftPoint.mode == SPDMode_CURR_CHAR) {
  }
  else if (leftPoint.mode == SPDMode_BACK_CHAR_SHIFT) {
    calculatePositionBackCharShift(iter, leftPoint);
  }
  else if (leftPoint.mode == SPDMode_FORWARD_CHAR_SHIFT) {
    calculatePositionForwardCharShift(iter, leftPoint);
  }
  else if (leftPoint.mode == SPDMode_CURR_LINE) {
    do {
      Iter_unsafeBackChar(iter);
      if (iter->start == iter->curr) return *iter;
    } while (Iter_currChar(iter) != '\n');
    Iter_nextChar(iter);
  }
  else if (leftPoint.mode == SPDMode_BACK_LINE_SHIFT) {
    int counter = leftPoint.value;
    while (counter >= 0) {
      Iter_unsafeBackChar(iter);
      if (iter->start == iter->curr) return *iter; // no activate Iter_nextChar
      if (Iter_currChar(iter) == '\n') {
        counter--;
      }
    }
    Iter_nextChar(iter);
  }
  else if (leftPoint.mode == SPDMode_FORWARD_LINE_SHIFT) {
    int counter = leftPoint.value;
    if (counter == 0) {
      do {
        Iter_unsafeBackChar(iter);
        if (iter->start == iter->curr) return *iter;
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
  return *iter;
}
Iter calculateRightPosition(BORROW(Iter) origIter, SourcePointDescription rightPoint) {
  Iter tmpIter = Iter_copy(origIter);
  Iter* iter = &tmpIter;

  if (rightPoint.mode == SPDMode_CURR_CHAR) {
  }
  else if (rightPoint.mode == SPDMode_BACK_CHAR_SHIFT) {
    calculatePositionBackCharShift(iter, rightPoint);
  }
  else if (rightPoint.mode == SPDMode_FORWARD_CHAR_SHIFT) {
    calculatePositionForwardCharShift(iter, rightPoint);
  }
  else if (rightPoint.mode == SPDMode_CURR_LINE) {
    while (Iter_currChar(iter) != '\n') {
      if (Iter_nextChar(iter) == '\0') break;
    }
    Iter_unsafeBackChar(iter);
  }
  else if (rightPoint.mode == SPDMode_BACK_LINE_SHIFT) {
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
        if (iter->start == iter->curr) return *iter;
        if (Iter_currChar(iter) == '\n') counter--;
      }
      Iter_unsafeBackChar(iter);
    }
  }
  else if (rightPoint.mode == SPDMode_FORWARD_LINE_SHIFT) {
    int counter = rightPoint.value;
    while (counter >= 0) {
      if (Iter_currChar(iter) == '\0') break;
      if (Iter_nextChar(iter) == '\n') {
        counter--;
      }
    }
    Iter_unsafeBackChar(iter);
  }
  return *iter;
}

Coords calculateIterCoords(BORROW(Iter) origIter) {
  Iter tmpIter = Iter_copy(origIter);
  Iter* iter = &tmpIter;

  Coords coords = (Coords) {
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
    char* str = A_xloc(sizeof(char)*(len+1));
    strncpy(str, leftIter.curr, len);
    str[len] = '\0';
    *cachedData = String_of(str);
    *cachedDataIsValid = true;
  }
}



Source Source_byIter(BORROW(ViewString) filename, BORROW(Iter) iter, SourcePointDescription leftPoint, SourcePointDescription rightPoint) {
  return Source_byIters(filename, iter, leftPoint, iter, rightPoint);
}
Source Source_byIters(BORROW(ViewString) filename, BORROW(Iter) leftIter, SourcePointDescription leftPoint, BORROW(Iter) rightIter, SourcePointDescription rightPoint) {
  if (leftIter->start != rightIter->start) {
    // TODO: ERROR
  }
  Iter l = calculateLeftPosition(leftIter, leftPoint);
  Iter r = calculateRightPosition(rightIter, rightPoint);

  if (l.curr > r.curr) {
    // TODO: ERROR
  }
  Coords lc = calculateIterCoords(&l);
  Coords rc = calculateIterCoords(&r);

  String cachedData = {0};
  bool cachedDataIsValid = false;
  loadCache(l, r, false, &cachedData, &cachedDataIsValid);

  Source source = (Source) {
    .filename = String_copy(filename),
    .startCoords = lc,
    .endCoords = rc,
    .startIter = l,
    .endIter = r,
    .cachedData = cachedData,
    .cachedDataIsValid = cachedDataIsValid
  };
  return source;
}
void_errno Source_updateCache(Source* source) {
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
