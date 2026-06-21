#pragma once

#include "metaparser.h"

typedef struct Lexem_OpData {
  bool isInfix;
  bool isPrefix;
  bool isPostfix;
  int binLbp; // binary priority
  int unaLbp; // unary priority
  int right; // open right priority shift (+1 for left-right ; -1 for right-left)
  Sts_MetaDeclarationExpressionType expType;
} Lexem_OpData;
#define Lexem_OpData_LEFT_ASSOCIATIVITY (+1)
#define Lexem_OpData_RIGHT_ASSOCIATIVITY (-1)

extern Lexem_OpData Lexem_OpData_ASSIGN;
extern Lexem_OpData Lexem_OpData_SUM;
extern Lexem_OpData Lexem_OpData_SUB;
extern Lexem_OpData Lexem_OpData_MUL;
extern Lexem_OpData Lexem_OpData_DIV;
extern Lexem_OpData Lexem_OpData_MOD;
extern Lexem_OpData Lexem_OpData_POW;

extern Lexem_OpData Lexem_OpData_NOT;
extern Lexem_OpData Lexem_OpData_INC;
extern Lexem_OpData Lexem_OpData_DEC;

extern Lexem_OpData Lexem_OpData_LOGICAL_OR;
extern Lexem_OpData Lexem_OpData_LOGICAL_AND;
extern Lexem_OpData Lexem_OpData_BITWISE_OR;
extern Lexem_OpData Lexem_OpData_BITWISE_XOR;
extern Lexem_OpData Lexem_OpData_BITWISE_AND;

extern Lexem_OpData Lexem_OpData_LOGICAL_EQL;
extern Lexem_OpData Lexem_OpData_LOGICAL_NOT_EQL;
extern Lexem_OpData Lexem_OpData_LOGICAL_GT;
extern Lexem_OpData Lexem_OpData_LOGICAL_LT;
extern Lexem_OpData Lexem_OpData_LOGICAL_GTE;
extern Lexem_OpData Lexem_OpData_LOGICAL_LTE;

extern Lexem_OpData Lexem_OpData_TERN_COND_IF;
extern Lexem_OpData Lexem_OpData_TERN_COND_ELSE;


typedef enum LexemType {
  LexemType_NULL = 0,
  LexemType_VALUE,
  LexemType_OPERATOR,
  LexemType_PAREN_OPEN,
  LexemType_PAREN_CLOSE,
  LexemType_BLOCK_OPEN,
  LexemType_BLOCK_CLOSE,
  LexemType_STATEMENT_IF,
  LexemType_STATEMENT_ELSE,
  LexemType_STATEMENT_FOR,
  LexemType_STATEMENT_FOREACH,
  LexemType_SEMICOLON,
} LexemType;
typedef struct Lexem {
  LexemType type;
  union {
    Sts_MetaDeclarationValue decValue;
    WEAK(Lexem_OpData*) opData;
  } value;
  Source src;
} Lexem;
void Lexem_free(Lexem* lexem);

#define NAME Lexems
#define TYPE Lexem
#define NULLV (Lexem) {0}
#define FREEFUN Lexem_free
#define TYPEDEFS 1
#include "glist.h"
#undef NAME
#undef TYPE
#undef NULLV
#undef FREEFUN
#undef TYPEDEFS

typedef struct Lexems_ParseSettings {
  struct {
    bool assign;
    bool statements;
    bool blocks;
    bool keyword_of;
    bool increments;
    bool semicolon;
  } available;
  ViewString exitChars;
} Lexems_ParseSettings;
Lexems Lexems_parseLexems(Sts_MetaParser_Context* ctx, Lexems_ParseSettings settings, Source* retExpressionSource);
