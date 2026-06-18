#include "metaparser.h"

#include "errors.h"
#include "metaparser_errors.h"

#include "mpmodules/utils.h"
#include "mpmodules/group.h"
#include "mpmodules/regexlink.h"
#include "mpmodules/setmainzone.h"
#include "mpmodules/token.h"
#include "mpmodules/zone.h"
#include "mpmodules/ssts.h"

typedef Sts_MetaParser_Context Context;


void Sts_MetaParser_Arguments_init(Sts_MetaParser_Arguments* arguments) {
  arguments->metadata.filename = (String) {0};
}
void Sts_MetaParser_Arguments_free(Sts_MetaParser_Arguments* arguments) {
  String_free(&arguments->metadata.filename);
}

#define vs_one(c) (ViewString_of((char[]) {c, '\0'}))
#define vs_two(c1, c2) (ViewString_of((char[]) {c1, c2, '\0'}))

void parseLoop(Context* context);


void_errno Sts_MetaParser_parse(MUT_BORROW(Sts_MetaFile*) metaFile, Iter iter, Sts_MetaParser_Arguments args) {
  ViewString errLocation = ViewString_of("Sts_MetaParser_parse");
  if (metaFile == null) Errors_internal_nullPointer(ViewString_of("Sts_MetaFile* metaFile"), errLocation);
  // if (args == null) Errors_internal_nullPointer(ViewString_of("Sts_MetaParser_Arguments* args"), errLocation);
  
  Context context = {
    .filename = args.metadata.filename,
    .metaFile = metaFile,
    .iter = iter,
    // .args = args,
  };

  if (setjmp(context.errjmp) != 0) { // ERROR EXIT
    errno = 1; return;
  }
  
  parseLoop(&context);
  errno = 0; return;
}

void parseLoop(Context* context) {
  Iter* iter = &context->iter;

  ViewString filename = ViewString_by(context->filename);

  bool flagModificator = false;
  for (char c = Iter_currChar(iter); c != '\0'; c = Iter_currChar(iter)) {
    // TODO: In the future, it's worth switching to the dispatch table.

    if (c == '#' || Chars_isVoid(c)) { 
      Utils_Iter_skipVoid(context, false);
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
        Iter iter2 = *iter;
        while (Iter_currChar(&iter2) != '~') {
          Iter_unsafeBackChar(&iter2);
        }
        Errors_metaparser_unknownToken(context, Source_byIters(
          filename,
          &iter2, SPD_new2(SPDMode_CURR_CHAR),
          iter, SPD_new2(SPDMode_CURR_CHAR)
        ));
      }
    }
    else if (c == '-') {
      c = Iter_nextChar(iter);
      if (errno != 0) {
        Errors_metaparser_unexpectedEnd(context, Source_byIter(
          filename,
          iter,
          SPD_new2(SPDMode_CURR_LINE),
          SPD_new2(SPDMode_CURR_CHAR)
        ));
      }

      if (c == '-') {
        Iter_nextChar(iter);
        parseSetMainZone(context);
      }
      else {
        parseZone(context);
      }
    }
    else if (c == '/') { 
      parseRegexLink(context);
    }
    else if (c == '[') {
      // TODO: supertokens deleted
      Errors_metaparser_unknownToken(context, Source_byIter(
        filename,
        iter,
        SPD_new2(SPDMode_CURR_CHAR),
        SPD_new2(SPDMode_CURR_CHAR)
      ));
    }
    else if (c == '*') {
      parseGroup(context); // TODO:
    }
    else if (c == ':') { 
      parseSstsFunction(context); // TODO:
    }
    else {
      Errors_metaparser_unknownToken(context, Source_byIter(
        filename,
        iter,
        SPD_new2(SPDMode_CURR_CHAR),
        SPD_new2(SPDMode_CURR_CHAR)
      ));
    }
  }
}
