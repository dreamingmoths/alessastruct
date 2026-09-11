#ifndef ALESSASTRUCT_DEBUG_H
#define ALESSASTRUCT_DEBUG_H

#define ALESSA_DEBUG 0

#define alessaAssert(condition) do {        \
    if (!(condition)) {                     \
        alessaError("assert: " #condition); \
    }                                       \
} while (0)

#define alessaDebug(...) do {               \
    if (ALESSA_DEBUG) {                     \
        printf(__VA_ARGS__);                \
    }                                       \
} while (0)

void alessaError(const char* errorMessage);

#endif // ALESSASTRUCT_DEBUG_H
