#include "metaparser.h"
#include "metaparser_ctx.h"
#include "metaparser_errors.h"

#include "modules/group.h"
#include "modules/regexlink.h"
#include "modules/setmainzone.h"
#include "modules/sstsfunction.h"
#include "modules/token.h"
#include "modules/zone.h"


void Sts_MetaParser_Arguments_init(Sts_MetaParser_Arguments* arguments) {
  // TODO:
}
void Sts_MetaParser_Arguments_free(Sts_MetaParser_Arguments* arguments) {
  // TODO:
}

#define vs_one(c) (ViewString_of((char[]) {c, '\0'}))
#define vs_two(c1, c2) (ViewString_of((char[]) {c1, c2, '\0'}))

void parseLoop(Context* context);


void Sts_MetaParser_parse(MUT_BORROW(Sts_MetaFile) metaFile, Iter iter, BORROW(Sts_MetaParser_Arguments) args) {
  String errLocation = String_const("Sts_MetaParser_parse");
  if (metaFile == 0) Errors_internal_nullPointer(String_const("Sts_MetaFile* metaFile"), errLocation);
  if (args == 0) Errors_internal_nullPointer(String_const("Sts_MetaParser_Arguments* args"), errLocation);
  
  Context context = {
    .metaFile = metaFile,
    .iter = iter,
    .args = args
  };
  
  parseLoop(&context);
}

void parseLoop(Context* context) {
  Iter* iter = &context->iter;

  bool flagModificator;
  Iter_foreachChars(c, iter) {
    // TODO: In the future, it's worth switching to the dispatch table.

    if (c == '#') { 
      // skip comment
      Iter_foreachChars(c, iter) {
        if (c == '\n') break;
      }
    }
    else if (Chars_isVoid(c)) {
      continue;
    }
    else if (Chars_isLetter(c)) {
      parseToken(context); // TODO:
    }
    else if (c == '~') {
      // modificator flag
      if (!flagModificator) {
        flagModificator = true;
      }
      else {
        Iter_unsafeBackChar(iter);
        Errors_metaparser_unkownToken(vs_two('~','~'), context);
      }
    }
    else if (c == '-') {
      c = Iter_readChar(iter);
      if (errno == 0) {
        Errors_metaparser_unexpectedEnd() // TODO: 
      }

      if (c == '-') {
        parseSetMainZone(context);
      }
      else {
        parseZone(context); // TODO:
      }
    }
    else if (c == '/') { 
      parseRegexLink(context);
    }
    else if (c == '[') {
      // TODO: supertokens deleted
      Errors_metaparser_unkownToken(vs_one('['), context);
    }
    else if (c == '*') {
      parseGroup(context); // TODO:
    }
    else if (c == ':') { 
      parseSstsFunction(context); // TODO:
    }
    else {
      Errors_metaparser_unkownToken(vs_one(c), context);
    }
  }
}
