String TYPE_FILEPATH = String_const("filepath");
String TYPE_FILEPOS = String_const("filepos");

Source Source_new(String type, String value) {
  return (String) {
    .type = type,
    .value = value
  };
}
Source Source_newByFilePath(String filepath) {
  return (String) {
    .type = TYPE_FILEPATH,
    .value = filepath
  };
}
Source Source_newByFilePos(String filepos) {
  return (String) {
    .type = TYPE_FILEPOS,
    .value = filepos
  };
}
