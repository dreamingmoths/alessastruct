#include <stdio.h>

#include "alessastruct/debug.h"
#include "alessastruct/string.h"

static StringTable stringTable = {
    .index = 0,
    .table = {}
};

char* intoStringTable(char* src) {
    char* dst = stringTable.table[stringTable.index];
    char* dstTop = dst;
    int i;

    for (i = 0; i < STRING_MAX_SIZE; i++) {
        char value = *src++;
        *dst++ = value;
        if (value == 0) {
            stringTable.index++;
            alessaDebug("........ string table index %d ........\n", stringTable.index);
            return dstTop;
        }
    }

    alessaError("exceeded max string table size");

    return NULL;
}

void printStringTable(void) {
    int i = 0;
    
    alessaDebug("....................");
    
    for (i = 0; i < STRING_TABLE_SIZE; i++) {
        printf("%d) %s%s\n", i, stringTable.table[i], i == stringTable.index ? " <-" : "");
    }

    alessaDebug("....................");
}

inline void resetStringTable(void) {
    stringTable.index = 0;
}

StringTable* getStringTable(void) {
    return &stringTable;
}
