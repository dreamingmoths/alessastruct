#include <stdio.h>
#include <stdlib.h>
#include <libc.h>

#include "alessastruct/file.h"
#include "alessastruct/parse.h"
#include "alessastruct/string.h"
#include "alessastruct/print.h"
#include "alessastruct/alessastruct.h"

void alessaYamlNodeStreamWriter(AlessaSyntaxTreeNode* node) {
    writeNodeAsYaml(stdout, node);
}

void alessaPlaintextNodeStreamWriter(AlessaSyntaxTreeNode* node) {
    prettyPrintNode(node);
}

void alessaCNodeStreamWriter(AlessaSyntaxTreeNode* node) {
    writeNodeAsC(stdout, node);
}

void alessaNodeStreamReader(FILE* file, NodeStreamCallback nodeCallback) {
    AlessaParserState* state = alessaInitParserState();
    AlessaTokenState* tokenState = &state->tokenState;
    char* buffer = (char*) &state->buffer;

    while (readNext(file, buffer)) {
        int i = 0;

        tokenState->nextCharacter = buffer;
        
        while (i++ < FILE_STREAM_BUFFER_SIZE) {
            Token* token = alessaReadToken(tokenState);
            AlessaSyntaxTreeNode* node;
            
            if (token == NULL) continue;
            if (token->kind == EmptyToken) break;
            
            node = alessaParseToken(state, token);

            if (node == NULL) continue;

            nodeCallback(node);

            resetStringTable();

            memset(node, 0, sizeof(AlessaSyntaxTreeNode));
        }
    }
}

