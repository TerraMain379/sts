#pragma once

#include <setjmp.h>

#include "metablocks.h"
#include "utils.h"
#include "iter.h"
#include "viewstringlist.h"
#include "stringlist.h"

typedef struct Sts_MetaParser_Arguments {
  struct {
    String filename;
  } metadata;
  // TODO: write params for parser
} Sts_MetaParser_Arguments;

void Sts_MetaParser_Arguments_init(Sts_MetaParser_Arguments* arguments);
void Sts_MetaParser_Arguments_free(Sts_MetaParser_Arguments* arguments);

void_errno Sts_MetaParser_parse(MUT_BORROW(Sts_MetaFile*) metaFile, Iter iter, Sts_MetaParser_Arguments args);



typedef struct Sts_MetaParser_Context {
  MUT_BORROW(Sts_MetaFile*) metaFile;
  Iter iter;
  String filename;
  jmp_buf errjmp;
  ViewStringList linkNamesBuffer;
} Sts_MetaParser_Context;
size_t Sts_MetaParser_Context_pushLinkNames(Sts_MetaParser_Context* context, BORROW(StringList) pushLinks);
void Sts_MetaParser_Context_popLinkNames(Sts_MetaParser_Context* context, size_t linkNamesNumber);



bool Sts_MetaDeclarationValue_checkForLink(Sts_MetaDeclarationValue* decValue, Sts_MetaParser_Context* context);
