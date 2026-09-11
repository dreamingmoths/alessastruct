#ifndef ALESSASTRUCT_PRINT_H
#define ALESSASTRUCT_PRINT_H

#include "alessastruct/parse.h"

void prettyPrintOneNode(AlessaSyntaxTreeNode* node, char* prefix);

void prettyPrintNode(AlessaSyntaxTreeNode* node);

void writeNodeAsC(FILE* file, AlessaSyntaxTreeNode* node);

void writeNodeAsYaml(FILE* file, AlessaSyntaxTreeNode* node);

void alessaPrintKeywords(void);

#endif // ALESSASTRUCT_PRINT_H
