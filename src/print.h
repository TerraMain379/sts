#pragma once

#define dec_print(type) String type##_print(type* input, size_t depth)
#define _dec_print(typeName, typeValue) String typeName##_print(typeValue* input, size_t depth)
