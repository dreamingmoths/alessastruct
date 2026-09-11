#ifndef ALESSASTRUCT_ARGUMENT_H
#define ALESSASTRUCT_ARGUMENT_H

#include "alessastruct/alessastruct.h"

typedef struct AlessaArgumentInfo {
    char command[255];
    char* inputFilePath;
    NodeStreamCallback* nodeStreamCallback;
} AlessaArgumentInfo;

void alessaPrintUsage(void);

AlessaArgumentInfo* alessaCreateArgumentInfo(int argc, char** argv);

void alessaCommandStreamReader(FILE* file);

#endif // ALESSASTRUCT_ARGUMENT_H
