#ifndef ALESSASTRUCT_FILE_H
#define ALESSASTRUCT_FILE_H

#include <stdio.h>
#include "alessastruct/types.h"

#define FILE_STREAM_BUFFER_SIZE  1024
#define NAME_HASH_PRIME          127

typedef char FileStreamBuffer[FILE_STREAM_BUFFER_SIZE];
typedef void FileStreamReader(FILE*);

typedef bool CharacterPredicate(char);

typedef struct {
    u_int length;
    u_long hash;
} ReadResult;

void withCommandStream(const char* command, FileStreamReader reader);

char* readNext(FILE* file, FileStreamBuffer buffer);

int readWhile(ReadResult* result, char* dst, char* src, CharacterPredicate predicate);

#endif // ALESSASTRUCT_FILE_H
