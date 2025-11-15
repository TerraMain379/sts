#pragma once

#include "utils.h"
#include "strings.h"

void_stop Errors_metaparser_unkownToken(String token, Iter* context);
void_stop Errors_metaparser_invalidName(String name, char* context, String ownerOfName, char* start);
void_stop Errors_metaparser_unexpectedEnd(size_t endCharsNum, char* end, char* start);
void_stop Errors_metaparser_expandingByYourself(String zone, String expander, char* context);
void_stop Errors_internal_nullPointer(String var, String location);
void_stop Errors_internal_allocateMemoryError(String location);

void Warnings_metaparser_unkownToken(String token, Iter* context, Iter start);
void Warnings_metaparser_redefiningRegex(String regexName, String token, char* start);
