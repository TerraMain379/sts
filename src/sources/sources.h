#include "string.h"

typedef struct Source {
  // TODO: я пока хз как это реализовать нормально
  String type;
  String value;
}

Source Source_new(String type, String value);
Source Source_newByFilePath(String filepath);
Source Source_newByFilePos(String filepos);

#define NAME Sources
#define TYPE Source
#define NULLV (Source) {0}
#include "glist.h"
#undef NAME
#undef TYPE
#undef NULLV
