#pragma once

#include "sources.h"
#include "prints.h"
#include "stringmap.h"

#define ERRORLOG_OUTPUT_VERSION 1

typedef enum ErrorLogSeverity {
  ErrorLogSeverity_ERROR,
  ErrorLogSeverity_WARNING,
  ErrorLogSeverity_NOTE,
} ErrorSeverity;
dec_print_json(ErrorSeverity);

typedef struct ErrorLogExcerpt {
  String copy;
  String line;
  long shift;
} ErrorLogExcerpt;
dec_print_json(ErrorLogExcerpt);

ErrorLogExcerpt ErrorLogExcerpt_new(Source source);
void ErrorLogExcerpt_free(ErrorLogExcerpt* excerpt);

typedef struct ErrorLog {
  int v;
  ErrorSeverity severity;
  String code;
  String category;
  String method;
  String message;
  Source source;
  Source source1;
  ErrorLogExcerpt excerpt;
  ErrorLogExcerpt excerpt1;
  String hint;
  StringMap extra;
  int seq;
  struct {
    bool method : 1;
    bool message : 1;
    bool source : 1;
    bool source1 : 1;
    bool excerpt : 1;
    bool excerpt1 : 1;
    bool hint : 1;
    bool extra : 1;
  } exist;
} ErrorLog;
dec_print_json(ErrorLog);

void ErrorLog_init(ErrorLog* errorLog, Source source);
void ErrorLog_free(ErrorLog* errorLog);
void ErrorLog_send(ErrorLog* errorLog);

typedef enum LogType {
  LogType_MESSAGE,
  LogType_ERROR
} LogType;

typedef struct Log {
  LogType type;
  union {
    String message; // valid json value
    OWNER(ErrorLog) errorLog;
  } value;
} Log;

Log Log_byMessage(String message);
Log Log_byErrorLog(OWNER(ErrorLog) errorLog);
void Log_send(BORROW(Log) log);
void Log_free(Log* log);
void Log_sendMessage(String message);
