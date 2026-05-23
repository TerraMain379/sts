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
  int shift;
} ErrorLogExcerpt;
dec_print_json(ErrorLogExcerpt);

ErrorLogExcerpt ErrorLogExcerpt_new(Source source);
void ErrorLogExcerpt_free(ErrorLogExcerpt* excerpt);

typedef struct ErrorLog {
  int v;
  ErrorSeverity severity;
  String code;
  String category;
  String method; bool existMethod;
  String message; bool existMessage;
  Source source; bool existSource;
  Source source1; bool existSource1;
  ErrorLogExcerpt excerpt; bool existExcerpt;
  ErrorLogExcerpt excerpt1; bool existExcerpt1;
  String hint; bool existHint;
  StringMap extra; bool existExtra;
  int seq;
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
