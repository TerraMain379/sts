#pragma once

#include "prints.h"

typedef struct {
  void* v;
} Stss_Type; // TODO: 
dec_prints(Stss_Type);

void Stss_Type_free(Stss_Type* type);

typedef struct {
  void* v;
} Stss_UntypeValue; // TODO: 
dec_prints(Stss_UntypeValue);
void Stss_UntypeValue_free(Stss_UntypeValue* untypeValue);
