#include "string.h"

typedef struct {
  String filename;
  String filepath;
  SourcePoint point1;
  SourcePoint point2;
} Source;

typedef struct {
  int line;
  int column;
} SourcePoint;
