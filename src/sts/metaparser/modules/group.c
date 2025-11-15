#include "modules/group.h"

#include "modules/utils.h"

void parseGroup(Context* ctx) {
  skipVoid(ctx);
  String name = readName(ctx);
  skipVoid(ctx);
  readChar(ctx, '(');

  Params params = readParams(ctx);
  for (size_t i = 0; i < params->size; i++) {
    Param* param = &Params_get(params, i);
    // TODO:
  }
}
