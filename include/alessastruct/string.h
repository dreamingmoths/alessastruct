#ifndef ALESSASTRUCT_STRING_H
#define ALESSASTRUCT_STRING_H

#include "alessastruct/common.h"

#define STRING_TABLE_SIZE 256
#define STRING_MAX_SIZE   256

typedef char StringTableArray[STRING_TABLE_SIZE][STRING_MAX_SIZE];

typedef struct {
    u_int index;
    StringTableArray table ALIGNED(16);
} StringTable;

char* intoStringTable(char* src);

void printStringTable(void);

void resetStringTable(void);

StringTable* getStringTable(void);

#endif // ALESSASTRUCT_STRING_H
