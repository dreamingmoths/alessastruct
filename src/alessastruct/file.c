#include "alessastruct/definitions.h"
#include "alessastruct/file.h"
#include "alessastruct/debug.h"

void withCommandStream(const char* command, FileStreamReader reader) {
    FILE* file = popen(command, "r");

    reader(file);

    pclose(file);
}

inline char* readNext(FILE* file, FileStreamBuffer buffer) {
    return fgets(buffer, FILE_STREAM_BUFFER_SIZE, file);
}


int readWhile(ReadResult* result, char* dst, char* src, CharacterPredicate predicate) {
    u_int length = 0;
    u_long hash = 0;

    while (predicate(*src)) {
        char value = *src++;
        *dst++ = value;
        if (++length > MAX_TOKEN_READ_SIZE) {
            alessaError("exceeded the maximum length");
        }
        hash += value;
        hash *= NAME_HASH_PRIME;
    }

    *dst++ = 0;

    result->length = length;
    result->hash = hash;

    return length;
}
