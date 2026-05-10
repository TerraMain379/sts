#include "errors.h"

#include <stdlib.h>

#define end_err _end_err()
static void_stop _end_err() {
  exit(EXIT_FAILURE);
}

void_stop Errors_internal_nullPointer(ViewString varName, ViewString location) {
  // TODO: 
  end_err;
}
void_stop Errors_internal_unexpectedBehavior(ViewString location, ViewString comment) {
  // TODO: 
  end_err;
}
void_stop Errors_internal_allocateMemoryError(ViewString varName, ViewString location) {
  // TODO: 
  end_err;
}
void_stop Errors_internal_unexpectedEnumType(ViewString location) {
  // TODO: 
  end_err;
}
