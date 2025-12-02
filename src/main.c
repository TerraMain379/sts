#include "utils.h"

int main() {
  // input.sts
  String data = Files_readFile("input.sts");
  
  Sts_MetaFile metaFile;
  Sts_MetaFile_init(&metaFile);

  Sts_MetaParserArguments args;
  Sts_MetaParserArguments_init(&args);

  Sts_MetaParser_parse(&metaFile, data, &args);
}
