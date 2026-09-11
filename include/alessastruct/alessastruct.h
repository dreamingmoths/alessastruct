#ifndef ALESSASTRUCT_H
#define ALESSASTRUCT_H

#include "alessastruct/common.h"
#include "alessastruct/parse.h"

typedef void NodeStreamCallback(AlessaSyntaxTreeNode* node);

void alessaYamlNodeStreamWriter(AlessaSyntaxTreeNode* node);

void alessaPlaintextNodeStreamWriter(AlessaSyntaxTreeNode* node);

void alessaCNodeStreamWriter(AlessaSyntaxTreeNode* node);

void alessaNodeStreamReader(FILE* file, NodeStreamCallback nodeCallback);

#endif // ALESSASTRUCT_H
