#pragma once

#include "metaparser.h"
#include "utils.h"
#include "strings.h"
#include "sources.h"
#include "iter.h"

// define CONTEXT_NAME

#define Context Sts_MetaParser_Context

void_stop Errors_metaparser_unkownToken(Context* ctx, Source src);
void_stop Errors_metaparser_anotherTokenExpected(Context* ctx, Source src, ViewString expectedToken);
void_stop Errors_metaparser_invalidName(Context* ctx, Source src, ViewString invalidName, ViewString expectedName);
void_stop Errors_metaparser_unexpectedEnd(Context* ctx, Source src);
void_stop Errors_metaparser_cyclicExpanding(Context* ctx, Source src, ViewString zoneName, ViewString expandingZone);
void_stop Errors_metaparser_expressionWasAwaitingOperator(Context* ctx, Source srcExpression, Source srcLexem);
void_stop Errors_metaparser_expressionWasAwaitingOperand(Context* ctx, Source srcExpression, Source srcLexem);

void Warnings_metaparser_unkownToken(ViewString token, Iter* context, Iter start);
void Warnings_metaparser_redefiningRegex(ViewString regexName, String token, char* start);

#undef Context
