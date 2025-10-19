#pragma once

#include "string.h"

typedef enum SourceType {
  SourceType_NON=0,
  SourceType_FILE,
  SourceType_NETWORK,
  SourceType_INPUT
    // TODO: 
} SourceType;

typedef struct Source {
  SourceType type;
  // TODO: 
} Source;

#define PNAME Sources
#define PTYPE Source
#include "plist.h"
#undef PNAME
#undef PTYPE
