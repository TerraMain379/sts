#include "files.h"

#include <stdio.h>
#include <string.h>

#include "utils.h"
#include "allocator.h"

type_errno(OWNER(String)) Files_readFile(BORROW(ViewString) filename) {
  const char* filenameBuffer = filename.buffer;;
  char buffer[filename.size + 1];

  FILE* file = fopen(filenameBuffer, "rb");
  if (file == null) {
    errno = 2; return String_new(null, 0, false);
  }

  if (fseek(file, 0, SEEK_END) != 0) {
    fclose(file);
    errno = 3; return String_new(null, 0, false);
  }
  
  long fileSize = ftell(file);
  
  if (fseek(file, 0, SEEK_SET) != 0) {
    fclose(file);
    errno = 4; return String_new(null, 0, false);
  }

  if (fileSize < 0) {
    fclose(file);
    errno = 5; return String_new(null, 0, false);
  }
  
  OWNER(char*) data = A_xloc(sizeof(char) * (fileSize + 1));
  
  size_t bytesRead = fread(data, sizeof(char), fileSize, file);

  if (bytesRead < (size_t) fileSize) {
    if (ferror(file)) { // if this is real system error
      fclose(file);
      A_free(data); 
      errno = 6; return String_new(null, 0, false);
    }

    if (bytesRead == 0) {
      fclose(file);
      A_free(data);
      errno = 0; return String_const("");
    }
    else if ((size_t) fileSize - bytesRead > 512) {
      data = A_xreloc(data, bytesRead + 1);
    }
  }

  data[bytesRead] = '\0';
  
  fclose(file);
  
  errno = 0; return String_new(data, bytesRead, true);
}
