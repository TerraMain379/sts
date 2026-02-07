#include "iter.h"

struct Iter {
  WAKE(char) const start;
  WAKE(char) curr;
  size_t size;
  Unicode_UCharInfo currUInfo;
  bool currUInfoIsValid;
};

Iter Iter_create(const char* const str, size_t size) {
  return (Iter) {
    .start = str,
    .curr = str,
    .size = size,
    .currUInfoIsValid = false
  };
}
Iter Iter_new(const String string) {
  return (Iter) {
    .start = string.buffer,
    .curr = string.buffer,
    .size = string.length,
    .currUInfoIsValid = false
  };
}

char Iter_currChar(Iter* iter) {
  return *iter->curr;
}
char Iter_nextChar(Iter* iter) {
  if (iter->size == 0) return 0;
  iter->size--;
  iter->curr++;
  iter->currUInfoIsValid = false;
  return *iter->curr;
}

uchar Iter_currUChar(Iter* iter) {
  if (iter->currUInfoIsValid) {
    return iter->currUInfo.uc;
  }
  else {
    Unicode_UCharInfo uinfo = Unicode_readUChar(iter->curr, iter->size);
    iter->currUInfo = uinfo;
    iter->currUInfoIsValid = true;
    return uinfo.uc;
  }
}
uchar Iter_nextUChar(Iter* iter) {
  if (iter->size == 0) return 0;
  size_t byteSize;
  if (iter->currUInfoIsValid) {
    byteSize = iter->currUInfo.byteSize;
  }
  else {
    byteSize = Unicode_readUCharLength(*iter->curr);
  }

  iter->size -= byteSize;
  if (iter->size < 0) {
    iter->size = 0;
    return 0;
  }
  iter->curr += byteSize;
  
  Unicode_UCharInfo uinfo = Unicode_readUChar(iter->curr, iter->size);

  iter->currUInfo = uinfo;
  iter->currUInfoIsValid = true;
  return uinfo.uc;
}

bool Iter_backChar(Iter* iter) {
  if (iter->curr > iter->start) {
    iter->curr--;
    iter->size++;
    return true;
  }
  return false;
}
bool Iter_backUChar(Iter* iter) {
  if (iter->curr > iter->start) {
    do {
      iter->curr--;
      iter->size++;
    } while ( 
      iter->curr > iter->start &&
      (unsigned char) *iter->curr >= 0x80
    );
    return true;
  }
  return false;
}

void Iter_unsafeBackChar(Iter* iter) {
  iter->curr--;
  iter->size++;
}
void Iter_unsafeBackUChar(Iter* iter) {
  do {
    iter->curr--;
    iter->size++;
  } while ( 
    iter->curr > iter->start &&
    (unsigned char) *iter->curr >= 0x80
  );
}
