#include "mp_parse/declarations.h"

#include "allocator.h"
#include "iter.h"
#include "metablocks.h"
#include "metaparser_errors.h"
#include "mp_parse/utils.h"
#include "mp_parse/expressions.h"
#include "sources.h"

static void_stop error_readName(Context* ctx, int backCharsDistance) {
  if (Iter_currChar(&ctx->iter) == '\0') {
    Errors_metaparser_unexpectedEnd(ctx, Source_byIter(
      ViewString_by(ctx->filename),
      &ctx->iter,
      SPD_new1(SPDMode_BACK_CHAR_SHIFT, backCharsDistance),
      SPD_new1(SPDMode_BACK_CHAR_SHIFT, 1)
    ));
  }
  else {
    Errors_metaparser_anotherTokenExpected(ctx, Source_byIter(
      ViewString_by(ctx->filename),
      &ctx->iter,
      SPD_new1(SPDMode_BACK_CHAR_SHIFT, backCharsDistance),
      SPD_new2(SPDMode_CURR_CHAR)
    ), ViewString_of("<name>"));
  }
  non_call_return;
}


static inline char parseDeclarationsBlockHeader_links(Sts_MetaDeclarationHead* head, Sts_MetaParser_Context* ctx);
static inline char parseDeclarationsBlockHeader_extend(Sts_MetaDeclarationHead* head, Sts_MetaParser_Context* ctx, char exitChar);
static inline char parseDeclarationsBlockHeader_extend_links(Sts_MetaDeclarationExtendElement* decName, Sts_MetaDeclarationHead* head, Sts_MetaParser_Context* ctx);

size_t Declarations_parseDeclarationHead(Sts_MetaDeclarationHead* head, Sts_MetaParser_Context* ctx, char exitChar) {
  Iter* iter = &ctx->iter;

  head->isGeneric = false;
  head->isGhost = false;

  Utils_Iter_skipVoid(ctx, false);
  char c = Iter_currChar(iter);
  
  if (c == '!') {
    head->isGhost = true;
    Iter_nextChar(iter);
    Utils_Iter_skipVoid(ctx, false);
    c = Iter_currChar(iter);
  }
  else if (c == '<') {
    head->isGeneric = true;
    c = parseDeclarationsBlockHeader_links(head, ctx);
  }
  size_t linkNamesInBufferNumber = Sts_MetaParser_Context_pushLinkNames(ctx, head->linkNames);

  if (c == ':') {
    c = parseDeclarationsBlockHeader_extend(head, ctx, exitChar);
  }

  if (c != exitChar) {
    Errors_metaparser_unknownToken(ctx, Source_byIter(
      ViewString_by(ctx->filename),
      iter,
      SPD_new2(SPDMode_CURR_CHAR),
      SPD_new2(SPDMode_CURR_CHAR)
    ));
  }
  Iter_nextChar(&ctx->iter);

  return linkNamesInBufferNumber;
}
static inline char parseDeclarationsBlockHeader_links(Sts_MetaDeclarationHead* head, Sts_MetaParser_Context* ctx) {
  Iter* iter = &ctx->iter;
  Iter_nextChar(iter);
  while (true) {
    Utils_Iter_skipVoid(ctx, false);
    type_errno(String) linkName = Utils_Iter_readName(ctx);
    if (errno != 0) {
      error_readName(ctx, 1);
      non_call_return 0;
    }
    StringList_add(&head->linkNames, linkName);
    Utils_Iter_skipVoid(ctx, false);
    char c = Iter_currChar(iter);
    if (c == '>') break;
    else if (c == ',') {
      Iter_nextChar(iter);
    }
    else {
      Errors_metaparser_unknownToken(ctx, Source_byIter(
        ViewString_by(ctx->filename),
        iter,
        SPD_new2(SPDMode_CURR_CHAR),
        SPD_new2(SPDMode_CURR_CHAR)
      ));
      non_call_return 0;
    }
  }
  Iter_nextChar(iter);
  Utils_Iter_skipVoid(ctx, false);
  return Iter_currChar(iter);
}
static inline char parseDeclarationsBlockHeader_extend(Sts_MetaDeclarationHead* head, Sts_MetaParser_Context* ctx, char exitChar) {
  Iter* iter = &ctx->iter;
  char c;
  Iter_nextChar(iter);
  do {
    Utils_Iter_skipVoid(ctx, false);
    type_errno(String) extendName = Utils_Iter_readName(ctx);
    if (errno != 0) {
      error_readName(ctx, 1);
      non_call_return 0;
    }

    Sts_MetaDeclarationValue extendNameValue = Sts_MetaDeclarationValue_byName1(extendName, ctx);
    Sts_MetaDeclarationValue_checkForLink(&extendNameValue, ctx);
    Sts_MetaDeclarationExtendElement decName = {
      .name = extendNameValue,
      .linksValues = {}
    };
    Sts_MetaDeclarationValueList_init(&decName.linksValues, 1);


    Utils_Iter_skipVoid(ctx, false);
    c = Iter_currChar(iter);
    if (c == '<') {
      parseDeclarationsBlockHeader_extend_links(&decName, head, ctx);
      Utils_Iter_skipVoid(ctx, false);
      c = Iter_currChar(iter);
    }

    Sts_MetaDeclarationExtendElementList_add(&head->extenders, decName);

    if (c == exitChar) {
      break;
    }
    else if (c != ',') {
      Errors_metaparser_unknownToken(ctx, Source_byIter(
        ViewString_by(ctx->filename),
        iter,
        SPD_new2(SPDMode_CURR_CHAR),
        SPD_new2(SPDMode_CURR_CHAR)
      ));
      non_call_return 0;
    }
    Iter_nextChar(iter);
  } while (true);
  return c;
}
static inline char parseDeclarationsBlockHeader_extend_links(Sts_MetaDeclarationExtendElement* decName, Sts_MetaDeclarationHead* head, Sts_MetaParser_Context* ctx) {
  Iter* iter = &ctx->iter;
  Iter_nextChar(iter);
  while (true) {
    Utils_Iter_skipVoid(ctx, false);
    Sts_MetaDeclarationValue linkValue = Expressions_parseValue(ctx, ViewString_of(",>"));
    Sts_MetaDeclarationValueList_add(&decName->linksValues, linkValue);

    char c = Iter_currChar(iter);
    if (c == '>') break;
    else /* if (c == ',') */ {
      Iter_nextChar(iter);
    }
  }
  Iter_nextChar(iter);
  Utils_Iter_skipVoid(ctx, false);
  return Iter_currChar(iter);
}



typedef enum OpenType {
  OpenType_BODY,
  OpenType_VALUE,
  OpenType_SHORT_CLOSE,
} OpenType;

static inline void parseDeclarations_name(Sts_MetaLineDeclarationList* declarations, Sts_MetaParser_Context* ctx, char c);
static inline void parseDeclarations_name_param(Sts_MetaLineDeclarationList* declarations, Sts_MetaParser_Context* ctx, Sts_MetaDeclarationValue nameDec, OpenType openType, bool isGhost);
static inline void parseDeclarations_name_event(Sts_MetaLineDeclarationList* declarations, Sts_MetaParser_Context* ctx, bool isGhost);
static inline void parseDeclarations_name_superregex(Sts_MetaLineDeclarationList* declarations, Sts_MetaParser_Context* ctx, bool isGhost);
static inline void parseDeclarations_variable(Sts_MetaLineDeclarationList* declarations, Sts_MetaParser_Context* ctx);
static inline void parseDeclarations_zoneExpand(Sts_MetaLineDeclarationList* declarations, Sts_MetaParser_Context* ctx, bool isExport);

void Declarations_parseDeclarations(Sts_MetaLineDeclarationList* declarations, Sts_MetaParser_Context* ctx, char exitChar) {
  while (true) {
    Utils_Iter_skipVoid(ctx, false);
    char c = Iter_currChar(&ctx->iter);

    if (Chars_isNameStart(c)) {
      parseDeclarations_name(declarations, ctx, c);
    }
    else if (c == '$') {
      parseDeclarations_variable(declarations, ctx);
    }
    else if (c == '<') {
      parseDeclarations_zoneExpand(declarations, ctx, false);
    }
    else if (c == '>') {
      parseDeclarations_zoneExpand(declarations, ctx, true);
    }
    else if (c == exitChar) {
      Iter_nextChar(&ctx->iter);
      break;
    }
    else if (c == '\0') {
      Errors_metaparser_unexpectedEnd(ctx, Source_byIter(
        ViewString_by(ctx->filename),
        &ctx->iter,
        SPD_new1_double(SPDMode_BACK_CHAR_SHIFT, 1)
      ));
    }
    else {
      Errors_metaparser_unknownToken(ctx, Source_byIter(
        ViewString_by(ctx->filename),
        &ctx->iter,
        SPD_new2(SPDMode_CURR_CHAR),
        SPD_new2(SPDMode_CURR_CHAR)
      ));
    }
  }
  Iter_nextChar(&ctx->iter);
}
static inline void parseDeclarations_name(Sts_MetaLineDeclarationList* declarations, Sts_MetaParser_Context* ctx, char c) {
  String name = Utils_Iter_readName(ctx);
  Sts_MetaDeclarationValue nameValue = Sts_MetaDeclarationValue_byName1(name, ctx);
  bool contains = Sts_MetaDeclarationValue_checkForLink(&nameValue, ctx);


  Utils_Iter_skipVoid(ctx, false);
  bool isGhost = Iter_currChar(&ctx->iter) == '!';
  if (isGhost) Iter_nextChar(&ctx->iter);
  Utils_Iter_skipVoid(ctx, false);
  c = Iter_currChar(&ctx->iter);

  OpenType openType;
  if (c == '{') openType = OpenType_BODY;
  else if (c == ':') openType = OpenType_VALUE;
  else if (c == ';') openType = OpenType_SHORT_CLOSE;
  else {
    Errors_metaparser_unknownToken(ctx, Source_byIter(
      ViewString_by(ctx->filename),
      &ctx->iter,
      SPD_new2_double(SPDMode_CURR_CHAR)
    ));
    return;
  }
  Iter_nextChar(&ctx->iter);

  if (ViewStrings_equals(ViewString_by(name), ViewString_of("event")) && !contains) {
    if (openType == OpenType_BODY) {
      String_free(&name);
      parseDeclarations_name_event(declarations, ctx, isGhost);
    }
    else if (openType == OpenType_SHORT_CLOSE) {
      Iter_nextChar(&ctx->iter);
    }
    else {
      Errors_metaparser_anotherTokenExpected(ctx, Source_byIter(
        ViewString_by(ctx->filename),
        &ctx->iter,
        SPD_new1_double(SPDMode_BACK_CHAR_SHIFT, 1)
      ), ViewString_of("{"));
    }
  }
  else if (ViewStrings_equals(ViewString_by(name), ViewString_of("regex")) && openType == OpenType_BODY && !contains) {
    String_free(&name);
    parseDeclarations_name_superregex(declarations, ctx, isGhost);
  }
  else { // default param
    parseDeclarations_name_param(declarations, ctx, nameValue, openType, isGhost);
  }
}
static inline void parseDeclarations_name_param(Sts_MetaLineDeclarationList* declarations, Sts_MetaParser_Context* ctx, Sts_MetaDeclarationValue nameDec, OpenType openType, bool isGhost) {
  char c;
  Sts_MetaDeclarationValueList values;
  Sts_MetaDeclarationValueList_init(&values, 1);
  if (openType == OpenType_SHORT_CLOSE) { // short true
    Sts_MetaDeclarationValue trueValue = (Sts_MetaDeclarationValue) {
      .type = Sts_MetaDeclarationValueType_NUMBER,
      .value.number = 1,
    };
    Sts_MetaDeclarationValueList_add(&values, trueValue);
  }
  else if (openType == OpenType_VALUE) {
    do {
      Utils_Iter_skipVoid(ctx, false);

      Sts_MetaDeclarationValue valueDec = Expressions_parseValue(ctx, ViewString_of(",;"));
      Sts_MetaDeclarationValue* valueDecPtr = Sts_MetaDeclarationValueList_add(&values, valueDec);

      Utils_Iter_skipVoid(ctx, false);
      c = Iter_currChar(&ctx->iter);
      Iter_nextChar(&ctx->iter);
    } while (c == ',');
  }
  else {
    Errors_metaparser_anotherTokenExpected(ctx, Source_byIter(
      ViewString_by(ctx->filename),
      &ctx->iter,
      SPD_new1_double(SPDMode_BACK_CHAR_SHIFT, 1)
    ), ViewString_of(":"));
  }
  Sts_MetaLineParamDeclaration paramDec = (Sts_MetaLineParamDeclaration) {
    .name = nameDec,
    .values = values,
    .isGhost = isGhost,
  };
  Sts_MetaLineDeclaration* lineDec = A_xloc(sizeof(Sts_MetaLineDeclaration));
  *lineDec = Sts_MetaLineDeclaration_byParam(paramDec);
  Sts_MetaLineDeclarationList_add(declarations, lineDec);
}
static inline void parseDeclarations_name_event(Sts_MetaLineDeclarationList* declarations, Sts_MetaParser_Context* ctx, bool isGhost) {
  Iter* iter = &ctx->iter;
  while (true) {
    Utils_Iter_skipVoid(ctx, false);
    type_errno(char) c = Iter_currChar(iter);
    if (c == '}') {
      Iter_nextChar(iter);
      break;
    }
    else if (errno != 0) {
      Errors_metaparser_unexpectedEnd(ctx, Source_byIter(
        ViewString_by(ctx->filename),
        iter,
        SPD_new1(SPDMode_BACK_CHAR_SHIFT, 1),
        SPD_new1(SPDMode_BACK_WORD_SHIFT, 2)
      ));
      non_call_return;
    }
    else { // if isGhost parser skip events block
      Sts_MetaDeclarationValue name = Expressions_parseValue(ctx, ViewString_of(":,;"));
      Utils_Iter_skipChar(ctx, ':');
      Utils_Iter_skipVoid(ctx, false);
      Sts_MetaDeclarationValue event = Expressions_parseValue(ctx, ViewString_of(",;"));
      Utils_Iter_skipChar(ctx, ';');

      if (!isGhost) {
        Sts_MetaLineEventDeclaration eventDec = (Sts_MetaLineEventDeclaration) {
          .name = name,
          .event = event,
        };
        Sts_MetaLineDeclaration* lineDec = A_xloc(sizeof(Sts_MetaLineDeclaration));
        *lineDec = Sts_MetaLineDeclaration_byEvent(eventDec);
        Sts_MetaLineDeclarationList_add(declarations, lineDec);
      }
      else {
        Sts_MetaDeclarationValue_free(&name);
        Sts_MetaDeclarationValue_free(&event);
      }
    }
  }
}
static inline void parseDeclarations_name_superregex(Sts_MetaLineDeclarationList* declarations, Sts_MetaParser_Context* ctx, bool isGhost) {
  Iter* iter = &ctx->iter;
  Sts_MetaLineSuperRegexDeclarationElements elements;
  Sts_MetaLineSuperRegexDeclarationElements_init(&elements, 5);
  Utils_Iter_skipVoid(ctx, false);
  while (Iter_currChar(iter) != '}') {
    type_errno(Sts_MetaDeclarationValue) token = Utils_Iter_readPath(ctx);
    if (errno != 0) {
      Errors_metaparser_anotherTokenExpected(ctx, Source_byIter(
        ViewString_by(ctx->filename),
        &ctx->iter,
        SPD_new2_double(SPDMode_CURR_CHAR)
      ), ViewString_of("<name>"));
    }
    Utils_Iter_skipVoid(ctx, false);
    bool isOptional = Iter_currChar(iter) == '?';
    if (isOptional) {
      Iter_nextChar(iter);
      Utils_Iter_skipVoid(ctx, false);
    }
    
    type_errno(String) name = Utils_Iter_readName(ctx);
    Sts_MetaDeclarationValue nameValue = {0};
    bool isNonName = errno != 0;
    if (!isNonName) {
      nameValue = Sts_MetaDeclarationValue_byName1(name, ctx);
      Sts_MetaDeclarationValue_checkForLink(&nameValue, ctx);
    }
    Utils_Iter_skipVoid(ctx, false);
    Utils_Iter_skipChar(ctx, ';');
    Utils_Iter_skipVoid(ctx, false);

    Sts_MetaLineSuperRegexDeclarationElement element = (Sts_MetaLineSuperRegexDeclarationElement) {
      .token = token,
      .name = nameValue,
      .isOptional = isOptional,
      .isNonName = isNonName,
    };
    Sts_MetaLineSuperRegexDeclarationElements_add(&elements, element);
  }
  Iter_nextChar(iter);

  Sts_MetaLineSuperRegexDeclaration superRegexDec = (Sts_MetaLineSuperRegexDeclaration) {
    .elements = elements,
    .isGhost = isGhost,
  };
  Sts_MetaLineDeclaration* lineDec = A_xloc(sizeof(Sts_MetaLineDeclaration));

  *lineDec = Sts_MetaLineDeclaration_bySuperRegex(superRegexDec);
  Sts_MetaLineDeclarationList_add(declarations, lineDec);
}
static inline void parseDeclarations_variable(Sts_MetaLineDeclarationList* declarations, Sts_MetaParser_Context* ctx) {
  Iter* iter = &ctx->iter;

  Sts_MetaDeclarationValue name = (Sts_MetaDeclarationValue) {
    .type = Sts_MetaDeclarationValueType_NULL
  };
  Sts_MetaDeclarationValue typing = (Sts_MetaDeclarationValue) {
    .type = Sts_MetaDeclarationValueType_NULL
  };
  Sts_MetaDeclarationValue value = (Sts_MetaDeclarationValue) {
    .type = Sts_MetaDeclarationValueType_NULL
  };
  bool isInit = false;

  Iter_nextChar(iter);
  Utils_Iter_skipVoid(ctx, false);
  char c = Iter_currChar(iter);
  if (c == '[') {
    isInit = true;
    Iter_nextChar(iter);
  }

  type_errno(String) nameString = Utils_Iter_readName(ctx);
  if (errno != 0) {
    Errors_metaparser_anotherTokenExpected(ctx, Source_byIter(
      ViewString_by(ctx->filename),
      iter,
      SPD_new1(SPDMode_BACK_CHAR_SHIFT, 1),
      SPD_new2(SPDMode_CURR_CHAR)
    ), ViewString_of("<name>"));
    non_call_return;
  }
  name = Sts_MetaDeclarationValue_byName1(nameString, ctx);
  Sts_MetaDeclarationValue_checkForLink(&name, ctx);

  Utils_Iter_skipVoid(ctx, false);
  c = Iter_currChar(iter);

  if (c == ':') {
    if (!isInit) {
      Errors_metaparser_tokenNotAvailableHere(ctx, Source_byIter(
        ViewString_by(ctx->filename),
        iter,
        SPD_new2_double(SPDMode_CURR_CHAR)
      ), ViewString_of("type is specified when declaring"));
      non_call_return;
    }
    Iter_nextChar(iter);
    type_errno(String) typingString = Utils_Iter_readName(ctx);
    if (errno != 0) {
      Errors_metaparser_anotherTokenExpected(ctx, Source_byIter(
        ViewString_by(ctx->filename),
        iter,
        SPD_new1(SPDMode_BACK_CHAR_SHIFT, 1),
        SPD_new2(SPDMode_CURR_CHAR)
      ), ViewString_of("<name>"));
      non_call_return;
    }

    typing = Sts_MetaDeclarationValue_byName1(typingString, ctx);
    Sts_MetaDeclarationValue_checkForLink(&typing, ctx);

    Utils_Iter_skipVoid(ctx, false);
    c = Iter_currChar(iter);
  }

  if (isInit) {
    if (c != ']') {
      Errors_metaparser_anotherTokenExpected(ctx, Source_byIter(
        ViewString_by(ctx->filename),
        iter,
        SPD_new2_double(SPDMode_CURR_CHAR)
      ), ViewString_of("]"));
      non_call_return;
    }
    Iter_nextChar(iter);
    Utils_Iter_skipVoid(ctx, false);
    c = Iter_currChar(iter);
  }

  if (c == '=') {
    Iter_nextChar(iter);
    value = Expressions_parseValue(ctx, ViewString_of(";}")); // `}` for smart error log
    c = Iter_currChar(iter);
  }

  if (c != ';') {
    Errors_metaparser_anotherTokenExpected(ctx, Source_byIter(
      ViewString_by(ctx->filename),
      iter,
      SPD_new2_double(SPDMode_CURR_CHAR)
    ), ViewString_of(";"));
    non_call_return;
  }
  Iter_nextChar(iter);

  Sts_MetaLineVariableDeclaration variableDec = (Sts_MetaLineVariableDeclaration) {
    .isInit = isInit,
    .name = name,
    .typing = typing,
    .value = value
  };
  Sts_MetaLineDeclaration* lineDec = A_xloc(sizeof(Sts_MetaLineDeclaration));
  *lineDec = Sts_MetaLineDeclaration_byVariable(variableDec);
  Sts_MetaLineDeclarationList_add(declarations, lineDec);
}
static inline void parseDeclarations_zoneExpand(Sts_MetaLineDeclarationList* declarations, Sts_MetaParser_Context* ctx, bool isExport) {
  Iter_nextChar(&ctx->iter);
  Utils_Iter_skipVoid(ctx, false);
  type_errno(String) nameString = Utils_Iter_readName(ctx);
  if (errno != 0) {
    Errors_metaparser_anotherTokenExpected(ctx, Source_byIter(
      ViewString_by(ctx->filename),
      &ctx->iter,
      SPD_new2_double(SPDMode_CURR_CHAR)
    ), ViewString_of("<name>"));
    non_call_return;
  }
  Sts_MetaDeclarationValue nameValue = Sts_MetaDeclarationValue_byName1(nameString, ctx);
  Sts_MetaDeclarationValue_checkForLink(&nameValue, ctx);
  Utils_Iter_skipVoid(ctx, false);
  Utils_Iter_skipChar(ctx, ';');
  Sts_MetaLineExpandDeclaration expandDec = (Sts_MetaLineExpandDeclaration) {
    .zoneName = nameValue,
    .isExport = isExport,
  };
  Sts_MetaLineDeclaration* lineDec = A_xloc(sizeof(Sts_MetaLineDeclaration));
  *lineDec = Sts_MetaLineDeclaration_byExpand(expandDec);
  Sts_MetaLineDeclarationList_add(declarations, lineDec);
}
