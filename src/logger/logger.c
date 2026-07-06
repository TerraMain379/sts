#include "logger.h"

#include "print_json_utils.h"

dec_print_json(ErrorSeverity) {
  print_json_enum_init;
  print_json_enum_r(ErrorLogSeverity_ERROR, ERROR);
  print_json_enum_r(ErrorLogSeverity_WARNING, WARNING);
  print_json_enum_r(ErrorLogSeverity_NOTE, NOTE);
  print_json_enum_end;
}
dec_print_json(ErrorLogExcerpt) {
  print_json_struct_init;
  print_json_field_value(String, copy);
  print_json_field_value(String, line);
  print_json_struct_return;
}
dec_print_json(ErrorLog) {
  print_json_struct_init;
  print_json_field_value(int, v);
  print_json_field_value(ErrorSeverity, severity);
  print_json_field_value(String, code);
  print_json_field_value(String, category);
  if (input->exist.method) { print_json_field_value(String, method); }
  if (input->exist.message) { print_json_field_value(String, message); }
  if (input->exist.source) { print_json_field_value(Source, source); }
  if (input->exist.excerpt) { print_json_field_value(ErrorLogExcerpt, excerpt); }
  if (input->exist.source1) { print_json_field_value(Source, source1); }
  if (input->exist.excerpt1) { print_json_field_value(ErrorLogExcerpt, excerpt1); }
  if (input->exist.hint) { print_json_field_value(String, hint); }
  if (input->exist.extra) { print_json_field_value(StringMap, extra); }
  print_json_field_value(int, seq);
  print_json_struct_return;
}

ErrorLogExcerpt ErrorLogExcerpt_new(Source source) {
  ErrorLogExcerpt excerpt;
  if (!source.cachedDataIsValid) Source_updateCache(&source);
  excerpt.copy = String_copyString(source.cachedData);
  Source lineSource = Source_byIters(
    ViewString_by(source.filename),
    &source.startIter, SPD_new2(SPDMode_CURR_LINE),
    &source.endIter, SPD_new2(SPDMode_CURR_LINE)
  ); Source_updateCache(&lineSource);
  excerpt.line = lineSource.cachedData;
  lineSource.cachedData = (String) {0};
  excerpt.shift = source.startIter.curr - lineSource.startIter.curr;
  Source_free(&lineSource);
  return excerpt;
}
void ErrorLogExcerpt_free(ErrorLogExcerpt* excerpt) {
  String_free(&excerpt->copy);
  String_free(&excerpt->line);
}

void ErrorLog_init(ErrorLog* errorLog, Source source) {
  *errorLog = (ErrorLog) {
    .v = ERRORLOG_OUTPUT_VERSION,
    .severity = ErrorLogSeverity_ERROR,
    .code = {0},
    .category = {0},
    .method = {0},
    .message = {0},
    .source = source,
    .excerpt = ErrorLogExcerpt_new(source),
    .hint = {0},
    .seq = 0,
  };
  StringMap_init(&errorLog->extra);
}
void ErrorLog_free(ErrorLog* errorLog) {
  String_free(&errorLog->code);
  String_free(&errorLog->category);
  String_free(&errorLog->method);
  String_free(&errorLog->message);
  Source_free(&errorLog->source);
  ErrorLogExcerpt_free(&errorLog->excerpt);
  String_free(&errorLog->hint);
  StringMap_freeElements(&errorLog->extra);
  StringMap_free(&errorLog->extra);
}
static int seq = 0;
void ErrorLog_send(ErrorLog* errorLog) {
  errorLog->seq = seq++;
  String str = ErrorLog_print_json(errorLog, 0);
  printf("%s\n", str.buffer);
  String_free(&str);
}

Log Log_byMessage(String message) {
  return (Log) {
    .type = LogType_MESSAGE,
    .value = { .message = message },
  };
}
Log Log_byErrorLog(OWNER(ErrorLog) errorLog);
void Log_send(BORROW(Log) log);
void Log_free(Log* log);
void Log_sendMessage(String message);
