#include "utils.h"
#include "strings.h"
#include "metablocks.h"
#include "metaparser.h"

int main() {
  // input.sts
  // String data = Files_readFile("input.sts");
  ViewString data = ViewString_of("hello world");
  Iter iter = Iter_new(data);
  
  Sts_MetaFile metaFile;
  Sts_MetaFile_init(&metaFile);

  Sts_MetaParser_Arguments args;
  Sts_MetaParser_Arguments_init(&args);

  Sts_MetaParser_parse(&metaFile, iter, &args);
}
