#include "metaparser_errors.h"

#include "logger.h"
#include "stringbuilder.h"

#define Context Sts_MetaParser_Context

#define end_err _end_err(ctx)
static void_stop _end_err(Context* ctx) {
  longjmp(ctx->errjmp, 1);
}

void_stop Errors_metaparser_unknownToken(Context* ctx, Source src) {
  ErrorLog elog = (ErrorLog) {
    .severity = ErrorLogSeverity_ERROR,
    .code = String_by("unknownToken"),
    .category = String_by("metaparser"),
    .method = (String) {0},
    .message = String_const("unknown token"),
    .source = src,
    .source1 = (Source) {0},
    .excerpt = ErrorLogExcerpt_new(src),
    .excerpt1 = (ErrorLogExcerpt) {0},
    .hint = (String) {0},
    .extra = (StringMap) {0},
    .existMethod = false,
    .existMessage = true,
    .existSource = true,
    .existSource1 = false,
    .existExcerpt = true,
    .existHint = false,
    .existExtra = false,
  };
  ErrorLog_send(&elog);
  ErrorLog_free(&elog);
  end_err;
}
void_stop Errors_metaparser_anotherTokenExpected(Context* ctx, Source src, ViewString expectedToken) {
  StringBuilder message;
  StringBuilder_init(&message);
  StringBuilder_addCharBuffer(&message, "expected token `");
  StringBuilder_addString(&message, expectedToken);
  StringBuilder_addChar(&message, '`');

  ErrorLog elog = (ErrorLog) {
    .severity = ErrorLogSeverity_ERROR,
    .code = String_by("anotherTokenExpected"),
    .category = String_by("metaparser"),
    .method = (String) {0},
    .message = StringBuilder_take(&message),
    .source = src,
    .source1 = (Source) {0},
    .excerpt = ErrorLogExcerpt_new(src),
    .excerpt1 = (ErrorLogExcerpt) {0},
    .hint = (String) {0},
    .extra = (StringMap) {0},
    .existMethod = false,
    .existMessage = true,
    .existSource = true,
    .existSource1 = false,
    .existExcerpt = true,
    .existHint = false,
    .existExtra = false,
  };
  ErrorLog_send(&elog);
  ErrorLog_free(&elog);
  end_err;
}
void_stop Errors_metaparser_invalidName(Context* ctx, Source src, ViewString invalidName, ViewString expectedName) {
  StringBuilder message;
  StringBuilder_init(&message);
  StringBuilder_addCharBuffer(&message, "invalid name `");
  StringBuilder_addString(&message, invalidName);
  StringBuilder_addChar(&message, '`');
  if (expectedName.buffer != null) {
    StringBuilder_addCharBuffer(&message, ", expected `");
    StringBuilder_addString(&message, expectedName);
    StringBuilder_addChar(&message, '`');
  }

  StringMap extra;
  StringMap_init(&extra);
  StringMap_set(&extra, ViewString_of("expectedName"), String_copy(expectedName));

  ErrorLog elog = (ErrorLog) {
    .severity = ErrorLogSeverity_ERROR,
    .code = String_by("invalidName"),
    .category = String_by("metaparser"),
    .method = (String) {0},
    .message = StringBuilder_take(&message),
    .source = src,
    .source1 = (Source) {0},
    .excerpt = ErrorLogExcerpt_new(src),
    .excerpt1 = (ErrorLogExcerpt) {0},
    .hint = (String) {0},
    .extra = extra,
    .existMethod = false,
    .existMessage = true,
    .existSource = true,
    .existSource1 = false,
    .existExcerpt = true,
    .existHint = false,
    .existExtra = true,
  };
  ErrorLog_send(&elog);
  ErrorLog_free(&elog);
  end_err;
}
void_stop Errors_metaparser_unexpectedEnd(Context* ctx, Source src) {
  ErrorLog elog = (ErrorLog) {
    .severity = ErrorLogSeverity_ERROR,
    .code = String_by("unexpectedEnd"),
    .category = String_by("metaparser"),
    .method = (String) {0},
    .message = (String) {0},
    .source = src,
    .source1 = (Source) {0},
    .excerpt = ErrorLogExcerpt_new(src),
    .excerpt1 = (ErrorLogExcerpt) {0},
    .hint = (String) {0},
    .extra = (StringMap) {0},
    .existMethod = false,
    .existMessage = false,
    .existSource = true,
    .existSource1 = false,
    .existExcerpt = true,
    .existHint = false,
    .existExtra = false,
  };
  ErrorLog_send(&elog);
  ErrorLog_free(&elog);
  end_err;
}
void_stop Errors_metaparser_cyclicExpanding(Context* ctx, Source src, ViewString zoneName, ViewString expandingZoneName) {
  StringBuilder message;
  StringBuilder_init(&message);
  StringBuilder_addCharBuffer(&message, "cyclic expanding: `");
  StringBuilder_addString(&message, zoneName);
  StringBuilder_addCharBuffer(&message, "` <- `");
  StringBuilder_addString(&message, expandingZoneName);
  StringBuilder_addChar(&message, '`');

  StringMap extra;
  StringMap_init(&extra);
  StringMap_set(&extra, ViewString_of("zoneName"), String_copy(zoneName));
  StringMap_set(&extra, ViewString_of("expandingZoneName"), String_copy(expandingZoneName));

  ErrorLog elog = (ErrorLog) {
    .severity = ErrorLogSeverity_ERROR,
    .code = String_by("cyclicExpanding"),
    .category = String_by("metaparser"),
    .method = (String) {0},
    .message = StringBuilder_take(&message),
    .source = src,
    .source1 = (Source) {0},
    .excerpt = ErrorLogExcerpt_new(src),
    .excerpt1 = (ErrorLogExcerpt) {0},
    .hint = (String) {0},
    .extra = extra,
    .existMethod = false,
    .existMessage = true,
    .existSource = true,
    .existSource1 = false,
    .existExcerpt = true,
    .existHint = false,
    .existExtra = true,
  };
  ErrorLog_send(&elog);
  ErrorLog_free(&elog);
  end_err;
}
void_stop Errors_metaparser_expressionWasAwaitingOperator(Context* ctx, Source srcExpression, Source srcLexem) {
  ErrorLog elog = (ErrorLog) {
    .severity = ErrorLogSeverity_ERROR,
    .code = String_by("expressionWasAwaitingOperator"),
    .category = String_by("metaparser"),
    .method = (String) {0},
    .message = (String) {0},
    .source = srcLexem,
    .source1 = srcExpression,
    .excerpt = ErrorLogExcerpt_new(srcLexem),
    .excerpt1 = ErrorLogExcerpt_new(srcExpression),
    .hint = (String) {0},
    .extra = (StringMap) {0},
    .existMethod = false,
    .existMessage = false,
    .existSource = true,
    .existSource1 = true,
    .existExcerpt = true,
    .existExcerpt1 = true,
    .existHint = false,
    .existExtra = false,
  };
  ErrorLog_send(&elog);
  ErrorLog_free(&elog);
  end_err;
}
void_stop Errors_metaparser_expressionWasAwaitingOperand(Context* ctx, Source srcExpression, Source srcLexem) {
  ErrorLog elog = (ErrorLog) {
    .severity = ErrorLogSeverity_ERROR,
    .code = String_by("expressionWasAwaitingOperand"),
    .category = String_by("metaparser"),
    .method = (String) {0},
    .message = (String) {0},
    .source = srcLexem,
    .source1 = srcExpression,
    .excerpt = ErrorLogExcerpt_new(srcLexem),
    .excerpt1 = ErrorLogExcerpt_new(srcExpression),
    .hint = (String) {0},
    .extra = (StringMap) {0},
    .existMethod = false,
    .existMessage = false,
    .existSource = true,
    .existSource1 = true,
    .existExcerpt = true,
    .existExcerpt1 = true,
    .existHint = false,
    .existExtra = false,
  };
  ErrorLog_send(&elog);
  ErrorLog_free(&elog);
  end_err;
}
void_stop Errors_metaparser_emptyExpression(CONTEXT* ctx, Source src) {
  ErrorLog elog = (ErrorLog) {
    .severity = ErrorLogSeverity_ERROR,
    .code = String_by("emptyExpression"),
    .category = String_by("metaparser"),
    .method = (String) {0},
    .message = (String) {0},
    .source = src,
    .source1 = (Source) {0},
    .excerpt = ErrorLogExcerpt_new(src),
    .excerpt1 = (ErrorLogExcerpt) {0},
    .hint = (String) {0},
    .extra = (StringMap) {0},
    .existMethod = false,
    .existMessage = false,
    .existSource = true,
    .existSource1 = false,
    .existExcerpt = true,
    .existExcerpt1 = false,
    .existHint = false,
    .existExtra = false,
  };
  ErrorLog_send(&elog);
  ErrorLog_free(&elog);
  end_err;
}

void Warnings_metaparser_unknownToken(CONTEXT* ctx, Source src) {
  ErrorLog elog = (ErrorLog) {
    .severity = ErrorLogSeverity_WARNING,
    .code = String_by("unknownToken"),
    .category = String_by("metaparser"),
    .method = (String) {0},
    .message = String_const("unknown token"),
    .source = src,
    .source1 = (Source) {0},
    .excerpt = ErrorLogExcerpt_new(src),
    .excerpt1 = (ErrorLogExcerpt) {0},
    .hint = (String) {0},
    .extra = (StringMap) {0},
    .existMethod = false,
    .existMessage = true,
    .existSource = true,
    .existSource1 = false,
    .existExcerpt = true,
    .existHint = false,
    .existExtra = false,
  };
  ErrorLog_send(&elog);
  ErrorLog_free(&elog);
  end_err;
}
void Warnings_metaparser_redefiningRegex(CONTEXT* ctx, Source src, ViewString regexName) {
  StringBuilder message;
  StringBuilder_init(&message);
  StringBuilder_addCharBuffer(&message, "redefiningRegex `");
  StringBuilder_addString(&message, regexName);
  StringBuilder_addChar(&message, '`');

  ErrorLog elog = (ErrorLog) {
    .severity = ErrorLogSeverity_WARNING,
    .code = String_by("redefiningRegex"),
    .category = String_by("metaparser"),
    .method = (String) {0},
    .message = StringBuilder_take(&message),
    .source = src,
    .source1 = (Source) {0},
    .excerpt = ErrorLogExcerpt_new(src),
    .excerpt1 = (ErrorLogExcerpt) {0},
    .hint = (String) {0},
    .extra = (StringMap) {0},
    .existMethod = false,
    .existMessage = true,
    .existSource = true,
    .existSource1 = false,
    .existExcerpt = true,
    .existExcerpt1 = false,
    .existHint = false,
    .existExtra = false,
  };
  ErrorLog_send(&elog);
  ErrorLog_free(&elog);
  end_err;
}
void Warnings_metaparser_redefiningMainZone(CONTEXT* ctx, Source src, ViewString zoneName) {
  ErrorLog elog = (ErrorLog) {
    .severity = ErrorLogSeverity_WARNING,
    .code = String_by("redefiningRegex"),
    .category = String_by("metaparser"),
    .method = (String) {0},
    .message = String_const("unknown token"),
    .source = src,
    .source1 = (Source) {0},
    .excerpt = ErrorLogExcerpt_new(src),
    .excerpt1 = (ErrorLogExcerpt) {0},
    .hint = (String) {0},
    .extra = (StringMap) {0},
    .existMethod = false,
    .existMessage = true,
    .existSource = true,
    .existSource1 = false,
    .existExcerpt = true,
    .existHint = false,
    .existExtra = false,
  };
  ErrorLog_send(&elog);
  ErrorLog_free(&elog);
  end_err;
}
