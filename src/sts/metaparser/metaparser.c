#include "metaparser.h"
#include "errors.h"

#include "modules/regexlink.h"

#define String_one(c) (String_const((char[]) {c, '\0'}))
#define String_two(c1, c2) (String_const((char[]) {c1, c2, '\0'}))

typedef Sts_MetaParser_Context Context;

void parseLoop(Context* context);


void Sts_MetaParser_parse(Sts_MetaFile* metaFile, Iter* iter, Sts_MetaParserArguments* args) {
  String errLocation = String_const("Sts_MetaParser_parse");
  if (metaFile == 0) Errors_internal_nullPointer(String_const("Sts_MetaFile* metaFile"), errLocation);
  if (iter == 0) Errors_internal_nullPointer(String_const("Iter* iter"), errLocation);
  if (iter->ch == 0) Errors_internal_nullPointer(String_const("char* iter.ch"), errLocation);
  if (args == 0) Errors_internal_nullPointer(String_const("Sts_MetaParserArguments args"), errLocation);
  
  Context context = {
    .metaFile = metaFile,
    .startIter = *iter;
    .iter = iter,
    .args = args
  };
  
  parseLoop(&context);
}

void parseLoop(Context* context) {
  Iter* iter = context->iter;

  bool flagModificator;
  Iter_foreachChars(char c, iter) {
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
        Errors_metaparser_unkownToken(String_two('~','~'), iter);
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
      parseSuperToken(context); // TODO:
    }
    else if (c == '*') {
      parseGroup(context); // TODO:
    }
    else if (c == ':') { 
      parseSstsFunction(context); // TODO:
    }
  }
}
