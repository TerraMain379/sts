#include "allocator.h"
#include "sources.h"
#include "utils.h"
#include "strings.h"
#include "metablocks.h"
#include "metaparser.h"
#include "stringbuilder.h"
#include "files.h"
#include "mpmodules/declarations.h"
// #include "metaparser.h"
#include "mpmodules/utils.h"
#include "print_json_utils.h"
#include "print_utils.h"
#include "prints.h"
#include "logger.h"

void test_parse();
void test_lexem_parser();
void test_print_json();

int main() {
  // input.sts
  test_parse();
  // test_lexem_parser();
  // test_print_json();
}
void test_parse() {
  type_errno(String) data = Files_readFile(ViewString_of("input.sts"));
  if (errno != 0) {
    return;
  }
  // printf("%s", data.buffer);
  Iter iter = Iter_new(ViewString_by(data));

  Sts_MetaFile metaFile;
  Sts_MetaFile_init(&metaFile);

  Sts_MetaParser_Arguments args;
  Sts_MetaParser_Arguments_init(&args);
  args.metadata.filename = String_by("input.sts");

  Sts_MetaParser_parse(&metaFile, iter, args);
  if (errno != 0) {
    return;
  }

  String log = Sts_MetaFile_print_json(&metaFile, 1);
  printf("%s\n", log.buffer);
  String_free(&log);

  Sts_MetaParser_Arguments_free(&args);
  Sts_MetaFile_free(&metaFile);
  String_free(&data);
}

void test_lexem_parser() {
  String string = Files_readFile(ViewString_of("input.expression"));
  Iter iter = Iter_new(ViewString_by(string));

  // Sts_MetaParser_Context ctx = (Sts_MetaParser_Context){
  //   .metaFile = null,
  //   .iter = Iter_new((ViewString*)&string),
  //   .args = (Sts_MetaParser_Arguments) {
  //     .metadata = {
  //       .filename = String_by("input.sts")
  //     }
  //   },
  // };
  // if (setjmp(ctx.errjmp) != 0) { // ERROR EXIT
  //   printf("%s", "setjmp exit\n");
  //   return;
  // }
  //
  // parseDeclarations(&block, &ctx);


  // printf("%s", "block: \n");
  // String output = Sts_MetaDeclarationsBlock_print(&block, 1);
  // printf("%s", output.buffer);
  // String_free(&output);
  // printf("%s", "\nend\n");
  //
  // Sts_MetaDeclarationsBlock_free(&block);
  // String_free(&string);
  // String_free(&ctx->filename);
}



void test_print_json() {
  Sts_MetaRegex regex = (Sts_MetaRegex) {
    .regex = String_by("Hello \n wrold\"\\")
  };
  String output = Sts_MetaRegex_print_json(&regex, 1);
  printf("%s\n", output.buffer);
  String_free(&output);
  Sts_MetaRegex_free(&regex);


  String text = String_by("\n\nHello world\nLines ln\n12 11\n\n");
  Iter iter = Iter_new(ViewString_by(text));
  int i = 0;
  char c; Iter_foreachChars(c, &iter) {
    if (c == '\n') i++;
    if (i == 3) {
      Iter_nextChar(&iter);
      break;
    }
  }
  ViewString filename = ViewString_of("input.sts");
  Source src = Source_byIter(
    filename, &iter,
    SPD_new2(SPDMode_CURR_LINE),
    SPD_new1(SPDMode_FORWARD_LINE_SHIFT, 2)
  );
  Source_updateCache(&src);

  StringMap extra;
  StringMap_init(&extra);
  StringMap_set(&extra, ViewString_of("token"), String_by("abcdef"));

  ErrorLog elog = (ErrorLog) {
    .v = 1,
    .severity = ErrorLogSeverity_WARNING,
    .code = String_by("metaparser.unknownToken"),
    .category = String_by("metaparser"),
    .method = String_by("parseDeclarations"),
    .message = String_by("unknown token"),
    .source = src,
    .excerpt = ErrorLogExcerpt_new(src),
    .hint = String_by("replace token"),
    .extra = extra,
    .seq = 12,
  };
  // output = ErrorLog_print_json(&erlog, 1);
  // printf("%s\n", output.buffer);
  // String_free(&output);
  ErrorLog_send(&elog);
  ErrorLog_send(&elog);
  ErrorLog_send(&elog);
  Errors_internal_nullPointer(ViewString_of("v1"), ViewString_of("main()"));

  ErrorLog_free(&elog);
  String_free(&text);
}
