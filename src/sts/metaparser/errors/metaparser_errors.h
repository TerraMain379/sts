#pragma once

#include "metaparser.h"
#include "utils.h"
#include "strings.h"
#include "sources.h"

#define CONTEXT Sts_MetaParser_Context

void_stop Errors_metaparser_unknownToken(CONTEXT* ctx, Source src);
void_stop Errors_metaparser_tokenNotAvailableHere(CONTEXT* ctx, Source src, ViewString reason);
void_stop Errors_metaparser_anotherTokenExpected(CONTEXT* ctx, Source src, ViewString expectedToken);
void_stop Errors_metaparser_invalidName(CONTEXT* ctx, Source src, ViewString invalidName, ViewString expectedName);
void_stop Errors_metaparser_unexpectedEnd(CONTEXT* ctx, Source src);
void_stop Errors_metaparser_cyclicExpanding(CONTEXT* ctx, Source src, ViewString zoneName, ViewString expandingZoneName);
void_stop Errors_metaparser_expressionWasAwaitingOperator(CONTEXT* ctx, Source srcExpression, Source srcLexem);
void_stop Errors_metaparser_expressionWasAwaitingOperand(CONTEXT* ctx, Source srcExpression, Source srcLexem);
void_stop Errors_metaparser_emptyExpression(CONTEXT* ctx, Source src);

void Warnings_metaparser_unknownToken(CONTEXT* ctx, Source src);
void Warnings_metaparser_redefiningRegex(CONTEXT* ctx, Source src, ViewString regexName);
void Warnings_metaparser_redefiningMainZone(CONTEXT* ctx, Source src, ViewString zoneName);
