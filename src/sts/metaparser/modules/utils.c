#include "modules/utils.h"

#include "allocator.h"


String readName(Iter* iter) {
  char* buffer = A_loc(16);
  size_t bufferSize = 16;
  size_t nameSize = 0;

  Iter_foreachChars(char c, iter) {
    if (!Chars_isLetter(c)) break;
    if (bufferSize == nameSize) {
      bufferSize *= 2;
      buffer = A_reloc(buffer, bufferSize);
    }
    bufferSize[nameSize] = c;
    nameSize++;
  }
  buffer[nameSize] = '\0';
  nameSize++;
  buffer = A_reloc(buffer, nameSize);
  return String_by(buffer, nameSize);
}
void skipVoid(Iter* iter, bool strict) {
  char c;
  if (strict) {
    c = Iter_currChar(iter)
    if (!Chars_isVoid(c)) return;
  }
  Iter_foreachChars(c, iter) {
    if (!Chars_isVoid(c)) return;
  }
}
void readChar(Context* ctx, char c) {
  if (Iter_readChar(ctx->iter) != c) {
    // TODO: ERROR 
  }
}

struct StaticParamValue {
  String name;
  Sts_MetaStaticParam param;
};

enum ModificatorType {
  ModificatorType_add
  // TODO:
};
struct StaticParamModificatorValue {
  String name;
  Sts_MetaStaticParam param;
  ModificatorType type;
};


enum ParamType {
  ParamType_STATIC_PARAM,
  ParamType_STATIC_PARAM_MODIFICATOR,
  ParamType_EVENTS,
  ParamType_META_SUPER_TOKEN_BODY,
  ParamType_ZONE_EXPAND,
  ParamType_VARIABLE
};
union ParamValue {
  StaticParamValue staticParam;
  StaticParamModificatorValue staticParamModificator;
  Sts_MetaEvents events;
  Sts_MetaSuperTokenBody superTokenBody;
  String zoneExpand;
  Sts_MetaVariable variable;
};
struct Param {
  ParamType type;
  ParamValue value;
  String tokenStart;
  String tokenEnd;
};

Params readParams(Context* ctx) {
  char c = Iter_currChar(ctx->iter);
  if (Chars_isLetter(c)) {
    // read name
    String name = readName(ctx);
    skipVoid(ctx);
    c = Iter_readChar(ctx->iter);
    if (errno != 0) {
      // TODO: error
    }

    if (c == ':') {
      // read static param
      Iter_skipVoid(ctx, false);
    }
    else if (c == '{') {
      // read event or super token body
      // TODO:
    }
    else {
      // modifiactor
      // TODO:
    }
  }
  else if (c == '$') {
    // readVariable
    // TODO:
  }
  else if (c == '<') {
    // zone expand
    // TODO:
  }
}
