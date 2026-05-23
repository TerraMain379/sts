#include "files.h"

#include <stdio.h>
#include <string.h>

#include "utils.h"
#include "allocator.h"

OWNER(String) Files_readFile(BORROW(ViewString) filename) {
  const char* filenameBuffer;
  char buffer[filename.size + 1];
  if (filename.buffer[filename.size] == '\0') {
    filenameBuffer = filename.buffer;
  }
  else {
    memcpy(buffer, filename.buffer, filename.size);
    buffer[filename.size] = '\0';
    filenameBuffer = buffer;
  }

  FILE* file = fopen(filenameBuffer, "rb");
  if (file == null) {
    return String_new(null, 0, false);
  }

  if (fseek(file, 0, SEEK_END) != 0) {
    fclose(file);
    return String_new(null, 0, false);
  }
  
  long fileSize = ftell(file);
  
  if (fseek(file, 0, SEEK_SET) != 0) {
    fclose(file);
    return String_new(null, 0, false);
  }

  if (fileSize < 0) {
    fclose(file);
    return String_new(null, 0, false);
  }
  
  OWNER(char*) data = A_xloc(sizeof(char) * (fileSize + 1));
  
  size_t bytesRead = fread(data, sizeof(char), fileSize, file);
  data[bytesRead] = '\0';
  
  fclose(file);
  
  return String_new(data, bytesRead, true);
}
