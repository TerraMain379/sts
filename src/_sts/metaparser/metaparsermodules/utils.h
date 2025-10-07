#include "metablocks.h"

String readName(struct StsFile* stsFile, char** iter);
String readRegex(struct StsFile* stsFile, char** iter);

void parseErrorsProcessing(struct StsFile* stsFile, char* ch, const char* unkownToken, size_t unexpectedEndEndCharNum);

void skipVoid(char** iter);

bool isLetter(char c);
bool isDigit(char c);
bool isNameChar(char c);
bool isVoid(char c);
