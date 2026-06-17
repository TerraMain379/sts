#include "errors.h"

#include <stdlib.h>
#include "logger.h"
#include "stringbuilder.h"

#define end_err _end_err()
static void_stop _end_err() {
  exit(EXIT_FAILURE);
}

void_stop Errors_internal_nullPointer(ViewString varName, ViewString location) {
  // TODO: 
  StringBuilder message;
  StringBuilder_init(&message);
  StringBuilder_addCharBuffer(&message, "variable `");
  StringBuilder_addString(&message, varName);
  StringBuilder_addCharBuffer(&message, "` is null");

  StringMap extra;
  StringMap_init(&extra);
  StringMap_set(&extra, ViewString_of("varName"), String_copy(varName));
  StringMap_set(&extra, ViewString_of("location"), String_copy(location));

  ErrorLog elog = (ErrorLog) {
    .severity = ErrorLogSeverity_ERROR,
    .code = String_by("nullPointer"),
    .category = String_by("internal"),
    .method = String_copy(location),
    .message = StringBuilder_take(&message),
    .source = (Source) {0},
    .excerpt = (ErrorLogExcerpt) {0},
    .hint = (String) {0},
    .extra = extra,
    .exist = {
      .method = true,
      .message = true,
      .source = false,
      .source1 = false,
      .excerpt = false,
      .excerpt1 = false,
      .hint = false,
      .extra = true,
    }
  };
  ErrorLog_send(&elog);
  ErrorLog_free(&elog);
  end_err;
}
void_stop Errors_internal_unexpectedBehavior(ViewString location, ViewString comment) {
  StringBuilder message;
  StringBuilder_init(&message);
  StringBuilder_addCharBuffer(&message, "unexpected behavior `");
  StringBuilder_addString(&message, comment);
  StringBuilder_addCharBuffer(&message, "` in `");
  StringBuilder_addString(&message, location);
  StringBuilder_addChar(&message, '`');

  StringMap extra;
  StringMap_init(&extra);
  StringMap_set(&extra, ViewString_of("location"), String_copy(location));
  StringMap_set(&extra, ViewString_of("comment"), String_copy(comment));

  ErrorLog elog = (ErrorLog) {
    .severity = ErrorLogSeverity_ERROR,
    .code = String_const("unexpectedBehavior"),
    .category = String_const("internal"),
    .method = String_copy(location),
    .message = StringBuilder_take(&message),
    .source = (Source) {0},
    .excerpt = (ErrorLogExcerpt) {0},
    .hint = (String) {0},
    .extra = extra,
    .exist = {
      .method = true,
      .message = true,
      .source = false,
      .source1 = false,
      .excerpt = false,
      .excerpt1 = false,
      .hint = false,
      .extra = true,
    }
  };
  ErrorLog_send(&elog);
  ErrorLog_free(&elog);
  end_err;
}

static bool inAllocateError = false;
void_stop Errors_internal_allocateMemoryError(ViewString varName, ViewString location) {
  if (!inAllocateError) {
    inAllocateError = true;

    StringBuilder message;
    StringBuilder_init(&message);
    if (location.buffer && varName.buffer) {
      StringBuilder_addCharBuffer(&message, "allocate memory error in `");
      StringBuilder_addString(&message, location);
      StringBuilder_addCharBuffer(&message, "` for `");
      StringBuilder_addString(&message, varName);
      StringBuilder_addChar(&message, '`');
    }
    else if (location.buffer && !varName.buffer) {
      StringBuilder_addCharBuffer(&message, "allocate memory error in `");
      StringBuilder_addString(&message, location);
      StringBuilder_addCharBuffer(&message, "`");
    }
    else if (!location.buffer && varName.buffer) {
      StringBuilder_addCharBuffer(&message, "allocate memory error for `");
      StringBuilder_addString(&message, varName);
      StringBuilder_addCharBuffer(&message, "`");
    }
    else {
      StringBuilder_addCharBuffer(&message, "allocate memory error");
    }


    StringMap extra;
    StringMap_init(&extra);
    if (varName.buffer) StringMap_set(&extra, ViewString_of("varName"), String_copy(varName));
    if (location.buffer) StringMap_set(&extra, ViewString_of("location"), String_copy(location));

    ErrorLog elog = (ErrorLog) {
      .severity = ErrorLogSeverity_ERROR,
      .code = String_const("allocatorError"),
      .category = String_by("internal"),
      .method = String_copy(location),
      .message = StringBuilder_take(&message),
      .source = (Source) {0},
      .excerpt = (ErrorLogExcerpt) {0},
      .hint = (String) {0},
      .extra = extra,
      .exist = {
        .method = true,
        .message = true,
        .source = false,
        .source1 = false,
        .excerpt = false,
        .excerpt1 = false,
        .hint = false,
        .extra = true,
      }
    };
    ErrorLog_send(&elog);
    ErrorLog_free(&elog);
  }
  else { // double critical allocate error
    printf( "\"{\"v\":%i,"
            "\"severity\":\"error\","
            "\"code\":\"allocatorError\","
            "\"method\":\"%s\","
            "\"seq\":-1}",
      ERRORLOG_OUTPUT_VERSION,
      location.buffer
    );
  }
  inAllocateError = false;
  end_err;
}
void_stop Errors_internal_unexpectedEnumType(ViewString location) {
  StringBuilder message;
  StringBuilder_init(&message);
  StringBuilder_addCharBuffer(&message, "unexpected enum type in `");
  StringBuilder_addString(&message, location);
  StringBuilder_addChar(&message, '`');

  StringMap extra;
  StringMap_init(&extra);
  StringMap_set(&extra, ViewString_of("location"), String_copy(location));

  ErrorLog elog = (ErrorLog) {
    .severity = ErrorLogSeverity_ERROR,
    .code = String_by("unexpectedEnumType"),
    .category = String_by("internal"),
    .method = String_copy(location),
    .message = StringBuilder_take(&message),
    .source = (Source) {0},
    .excerpt = (ErrorLogExcerpt) {0},
    .hint = (String) {0},
    .extra = extra,
    .exist = {
      .method = true,
      .message = true,
      .source = false,
      .source1 = false,
      .excerpt = false,
      .excerpt1 = false,
      .hint = false,
      .extra = true,
    }
  };
  ErrorLog_send(&elog);
  ErrorLog_free(&elog);
  end_err;
  end_err;
}
