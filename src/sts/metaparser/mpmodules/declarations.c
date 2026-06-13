#include "mpmodules/declarations.h"

#include "allocator.h"
#include "iter.h"
#include "metablocks.h"
#include "metaparser_errors.h"
#include "errors.h"
#include "mpmodules/utils.h"
#include "mpmodules/expressions.h"
#include "sources.h"

static void registerDeclarationValue(Sts_MetaDeclarationsBlock* decBlock, Sts_MetaDeclarationValue* value) {
  if (value->type == Sts_MetaDeclarationValueType_LINK) {
    Sts_MetaDeclarationValuesLinks_registerDeclaratonValue(&decBlock->links, value);
  }
}

typedef enum OpenType {
  OpenType_BODY,
  OpenType_VALUE,
  OpenType_SHORT_CLOSE,
} OpenType;

static inline void parseDeclarations_name(Sts_MetaDeclarationsBlock* decBlock, Sts_MetaParser_Context* ctx, char c);
static inline void parseDeclarations_name_param(Sts_MetaDeclarationsBlock* decBlock, Sts_MetaParser_Context* ctx, Sts_MetaDeclarationValue nameDec, OpenType openType);
static inline void parseDeclarations_name_event(Sts_MetaDeclarationsBlock* decBlock, Sts_MetaParser_Context* ctx);
static inline void parseDeclarations_variable(Sts_MetaDeclarationsBlock* decBlock, Sts_MetaParser_Context* ctx);
static inline Stss_Type parseDeclarations_variable_type(Sts_MetaDeclarationsBlock* decBlock, Sts_MetaParser_Context* ctx);

void parseDeclarations(Sts_MetaDeclarationsBlock* decBlock, Sts_MetaParser_Context* ctx) {
  Sts_MetaDeclarationsBlockType type = decBlock->type;
  char exitChar =
    type == Sts_MetaDeclarationsBlockType_TOKEN ? '}' :
    type == Sts_MetaDeclarationsBlockType_ZONE ? ')' :
    type == Sts_MetaDeclarationsBlockType_GROUP ? ')' :
    type == Sts_MetaDeclarationsBlockType_SUPER_TOKEN ? '}' :
    '\0';
  if (exitChar == '\0') {
    Errors_internal_unexpectedEnumType(ViewString_of("parseDeclarations().decBlock->type"));
    non_call_return;
  }
  
  while (true) {
    Utils_Iter_skipVoid(ctx, false);
    char c = Iter_currChar(&ctx->iter);

    if (Chars_isNameStart(c)) {
      parseDeclarations_name(decBlock, ctx, c);
    }
    else if (c == '$') {
      parseDeclarations_variable(decBlock, ctx);
    }
    else if (c == exitChar || c == '\0') {
      break;
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
}
static inline void parseDeclarations_name(Sts_MetaDeclarationsBlock* decBlock, Sts_MetaParser_Context* ctx, char c) {
  String name = Utils_Iter_readName(ctx);
  Sts_MetaDeclarationValue nameDec;

  bool contains = StringList_contains(&decBlock->linkNames, ViewString_by(name));
  if (contains) {
    nameDec.type = Sts_MetaDeclarationValueType_LINK;
    nameDec.value.linkName = name;
  }
  else {
    nameDec.type = Sts_MetaDeclarationValueType_NAME;
    nameDec.value.name = name;
  }

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
      parseDeclarations_name_event(decBlock, ctx);
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
    // TODO: super regex
  }
  else { // default param
    parseDeclarations_name_param(decBlock, ctx, nameDec, openType);
  }
}
static inline void parseDeclarations_name_param(Sts_MetaDeclarationsBlock* decBlock, Sts_MetaParser_Context* ctx, Sts_MetaDeclarationValue nameDec, OpenType openType) {
  char c;
  Sts_MetaDeclaration* dec = A_xloc(sizeof(Sts_MetaDeclaration));
  *dec = (Sts_MetaDeclaration) {
    .type = Sts_MetaDeclarationType_PARAM,
  };
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

      Sts_MetaDeclarationValue valueDec = Expressions_parseValue(decBlock, ctx, ViewString_of(",;"));
      Sts_MetaDeclarationValue* valueDecPtr = Sts_MetaDeclarationValueList_add(&values, valueDec);
      registerDeclarationValue(decBlock, valueDecPtr);

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
  dec->value.param = (Sts_MetaParamDeclaration) {
    .name = nameDec,
    .values = values,
  };
  registerDeclarationValue(decBlock, &dec->value.param.name);
  Sts_MetaDeclarationList_add(&decBlock->declarations, dec);
}
static inline void parseDeclarations_name_event(Sts_MetaDeclarationsBlock* decBlock, Sts_MetaParser_Context* ctx) {
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
    else {
      Sts_MetaDeclaration* eventDec = A_xloc(sizeof(Sts_MetaDeclaration));
      eventDec->type = Sts_MetaDeclarationType_EVENT;

      eventDec->value.event.name = Expressions_parseValue(decBlock, ctx, ViewString_of(":,;"));
      Utils_Iter_skipChar(ctx, ':');
      Utils_Iter_skipVoid(ctx, false);
      eventDec->value.event.event = Expressions_parseValue(decBlock, ctx, ViewString_of(",;"));
      Utils_Iter_skipChar(ctx, ';');

      Sts_MetaDeclarationList_add(&decBlock->declarations, eventDec);
    }
  }
}
static inline void parseDeclarations_variable(Sts_MetaDeclarationsBlock* decBlock, Sts_MetaParser_Context* ctx) {
  Iter* iter = &ctx->iter;

  bool isInit = false;
  String name;
  Stss_Type type;
  Sts_MetaDeclarationValue value = (Sts_MetaDeclarationValue) {
    .type = Sts_MetaDeclarationValueType_NULL
  };

  Iter_nextChar(iter);
  Utils_Iter_skipVoid(ctx, false);
  char c = Iter_currChar(iter);
  if (c == '[') {
    isInit = true;
    c = Iter_nextChar(iter);
  }

  if (!Chars_isNameStart(c)) {
    Errors_metaparser_anotherTokenExpected(ctx, Source_byIter(
      ViewString_by(ctx->filename),
      iter,
      SPD_new1(SPDMode_BACK_CHAR_SHIFT, 1),
      SPD_new2(SPDMode_CURR_CHAR)
    ), ViewString_of("<name>"));
  }
  name = Utils_Iter_readName(ctx);

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
    type = parseDeclarations_variable_type(decBlock, ctx);
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
    value = Expressions_parseValue(decBlock, ctx, ViewString_of(";"));
    c = Iter_currChar(iter);
  }

  if (c != ';') {
    // TODO: delete if parseValue return guarantee
    Errors_metaparser_anotherTokenExpected(ctx, Source_byIter(
      ViewString_by(ctx->filename),
      iter,
      SPD_new2_double(SPDMode_CURR_CHAR)
    ), ViewString_of(";"));
    non_call_return;
  }
  Iter_nextChar(iter);

  Sts_MetaDeclarationValue nameValue = (Sts_MetaDeclarationValue) {
    .type = Sts_MetaDeclarationValueType_STRING,
    .value = {
      .string = name
    }
  };
  Sts_MetaVariableDeclaration variableDec = (Sts_MetaVariableDeclaration) {
    .isInit = isInit,
    .name = nameValue,
    .typing = {/*  TODO: */},
    .value = value
  };
  Sts_MetaDeclaration* declaration = A_xloc(sizeof(Sts_MetaDeclaration));
  *declaration = (Sts_MetaDeclaration) {
    .type = Sts_MetaDeclarationType_VARIABLE,
    .value = {
      .variable = variableDec
    }
  };
  Sts_MetaDeclarationList_add(&decBlock->declarations, declaration);
}
static inline Stss_Type parseDeclarations_variable_type(Sts_MetaDeclarationsBlock* decBlock, Sts_MetaParser_Context* ctx) {
  // TODO: 
  return (Stss_Type) {0};
}
