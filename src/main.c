#include "utils.h"
#include "strings.h"
#include "metablocks.h"
#include "metaparser.h"
#include "stringbuilder.h"
#include "files.h"
#include "mpmodules/declarations.h"
// #include "metaparser.h"
#include "mpmodules/utils.h"

void test_lexem_parser();

int main() {
  // input.sts
  // String data = Files_readFile(ViewString_of("input.sts"));
  // printf("%s", data.buffer);
  // Iter iter = Iter_new(ViewString_by(&data));
  //
  // Sts_MetaFile metaFile;
  // Sts_MetaFile_init(&metaFile);
  //
  // Sts_MetaParser_Arguments args;
  // Sts_MetaParser_Arguments_init(&args);
  //
  // Sts_MetaParser_parse(&metaFile, iter, &args);
  // if (errno != 0) {
  //   printf("%s", "parse error");
  // }
  //
  // Sts_MetaParser_Arguments_free(&args);
  // Sts_MetaFile_free(&metaFile);
  // String_free(&data);
  test_lexem_parser();
}

void test_lexem_parser() {
  String string = Files_readFile(ViewString_of("input.expression"));
  Iter iter = Iter_new((ViewString*)&string);

  Sts_MetaDeclarationsBlock block;
  Sts_MetaDeclarationsBlock_init(&block, Sts_MetaDeclarationsBlockType_TOKEN);
  StringList_add(&block.linkNames, String_by("g"));

  Sts_MetaParser_Context ctx = (Sts_MetaParser_Context){
      .metaFile = null,
      .iter = Iter_new((ViewString*)&string),
      .args = null,
      .filename = String_by("input.sts"),
  };
  if (setjmp(ctx.errjmp) != 0) { // ERROR EXIT
    printf("%s", "setjmp exit\n");
    return;
  }

  parseDeclarations(&block, &ctx);


  printf("%s", "block: \n");
  String output = Sts_MetaDeclarationsBlock_print(&block, 1);
  printf("%s", output.buffer);
  String_free(&output);
  printf("%s", "\nend\n");

  Sts_MetaDeclarationsBlock_free(&block);
  String_free(&string);
  String_free(&ctx.filename);
}
