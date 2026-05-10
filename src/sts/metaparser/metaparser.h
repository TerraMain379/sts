#pragma once

#include <setjmp.h>

#include "metablocks.h"
#include "utils.h"
#include "iter.h"
#include "string.h"

typedef struct Sts_MetaParser_Arguments {
  struct {
    String filename;
  } metadata;
  // TODO: write params for parser
} Sts_MetaParser_Arguments;

void Sts_MetaParser_Arguments_init(Sts_MetaParser_Arguments* arguments);
void Sts_MetaParser_Arguments_free(Sts_MetaParser_Arguments* arguments);

void_errno Sts_MetaParser_parse(MUT_BORROW(Sts_MetaFile) metaFile, Iter iter, BORROW(Sts_MetaParser_Arguments) args);


typedef struct Sts_MetaParser_Context {
  MUT_BORROW(Sts_MetaFile) metaFile;
  Iter iter;
  BORROW(Sts_MetaParser_Arguments) args;
  String filename;
  jmp_buf errjmp;
} Sts_MetaParser_Context;
