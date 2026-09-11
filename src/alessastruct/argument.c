#include <stdio.h>

#include "alessastruct/debug.h"
#include "alessastruct/print.h"
#include "alessastruct/alessastruct.h"
#include "alessastruct/argument.h"

static const char* PREPROCESSOR_COMMAND = "gcc -Itarget -E -P %s\n";

// static const char inputFilePath[] = "target/include/sce/libgraph.h";
// static const char inputFilePath[] = "target/sh2src/Chacter/character.h";
// static const char inputFilePath[] = "target/include/shared/Font/font.h";
// static const char inputFilePath[] = "include/alessastruct/alessastruct.h";

static AlessaArgumentInfo argumentInfo;

void alessaPrintUsage(void) {
    printf("alessastruct <c|yaml|text> <filepath>\n");
}

AlessaArgumentInfo* alessaCreateArgumentInfo(int argc, char** argv) {
    if (argc != 3) {
        return NULL;
    }

    argumentInfo.inputFilePath = argv[2];

    switch (argv[1][0]) {
        case 'c':
            argumentInfo.nodeStreamCallback = alessaCNodeStreamWriter;
            break;

        case 'y':
            argumentInfo.nodeStreamCallback = alessaYamlNodeStreamWriter;
            break;

        case 't':
            argumentInfo.nodeStreamCallback = alessaPlaintextNodeStreamWriter;
            break;
        
        default:
            return NULL;
    }

    sprintf(argumentInfo.command, PREPROCESSOR_COMMAND, argumentInfo.inputFilePath);

    return &argumentInfo;
}

void alessaCommandStreamReader(FILE* file) {
    alessaAssert(argumentInfo.nodeStreamCallback);
    alessaNodeStreamReader(file, argumentInfo.nodeStreamCallback);
}
