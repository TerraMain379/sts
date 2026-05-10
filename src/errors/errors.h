#pragma once

#include "utils.h"
#include "strings.h"

void_stop Errors_internal_nullPointer(ViewString varName, ViewString location);
void_stop Errors_internal_unexpectedBehavior(ViewString location, ViewString comment);
void_stop Errors_internal_unexpectedEnumType(ViewString location);
void_stop Errors_internal_allocateMemoryError(ViewString varName, ViewString location);
