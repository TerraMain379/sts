#include "metaparser_errors.h"

#include <stdio.h>
#include <stdlib.h>

void_stop Errors_metaparser_unkownToken(ViewString token, Iter* context) {}
void_stop Errors_metaparser_invalidName(ViewString name, char* context, String ownerOfName, char* start) {}
void_stop Errors_metaparser_unexpectedEnd(size_t endCharsNum, char* end, char* start) {}
void_stop Errors_metaparser_expandingByYourself(ViewString zone, ViewString expander, char* context) {}
void_stop Errors_internal_nullPointer(ViewString var, ViewString location) {}
void_stop Errors_internal_allocateMemoryError(ViewString location) {}

void Warnings_metaparser_unkownToken(ViewString token, Iter* context, Iter start) {}
void Warnings_metaparser_redefiningRegex(ViewString regexName, String token, char* start) {}
