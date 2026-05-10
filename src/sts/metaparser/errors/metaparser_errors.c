#include "metaparser_errors.h"

#include <stdio.h>
#include <stdlib.h>

#define Context Sts_MetaParser_Context

#define end_err _end_err(ctx)
static void_stop _end_err(Context* ctx) {
  longjmp(ctx->errjmp, 1);
}

void_stop Errors_metaparser_unkownToken(Context* ctx, Source src) {
  // TODO: 
  end_err;
}
void_stop Errors_metaparser_anotherTokenExpected(Context* ctx, Source src, ViewString expectedToken) {
  // TODO: 
  end_err;
}
void_stop Errors_metaparser_invalidName(Context* ctx, Source src, ViewString invalidName, ViewString expectedName) {
  // TODO: 
  end_err;
}
void_stop Errors_metaparser_unexpectedEnd(Context* ctx, Source src) {
  // TODO: 
  end_err;
}
void_stop Errors_metaparser_cyclicExpanding(Context* ctx, Source src, ViewString zoneName, ViewString expandingZone) {
  // TODO: 
  end_err;
}
void_stop Errors_metaparser_expressionWasAwaitingOperator(Context* ctx, Source srcExpression, Source srcLexem) {
  // TODO: 
  end_err;
}
void_stop Errors_metaparser_expressionWasAwaitingOperand(Context* ctx, Source srcExpression, Source srcLexem) {
  // TODO: 
  end_err;
}

void Warnings_metaparser_unkownToken(ViewString token, Iter* context, Iter start);
void Warnings_metaparser_redefiningRegex(ViewString regexName, String token, char* start);
