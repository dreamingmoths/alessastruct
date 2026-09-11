#include <stdio.h>
#include <stdlib.h>

#include "alessastruct/common.h"
#include "alessastruct/debug.h"

ATTRIBUTE(noreturn) void alessaError(const char* errorMessage) {
    fprintf(stderr, "[error] %s\n", errorMessage);
    exit(1);
}
