void_stop Errors_metaparser_unkownToken(String token, Iter* context);
void_stop Errors_metaparser_invalidName(String name, char* context, String ownerOfName, char* start);
void_stop Errors_metaparser_unexpectedEnd(size_t endCharsNum, char* end, char* start);
void_stop Errors_metaparser_expandingByYourself(String zone, String expander, char* context);
