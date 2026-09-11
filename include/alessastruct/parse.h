#ifndef ALESSASTRUCT_PARSE_H
#define ALESSASTRUCT_PARSE_H

#include "alessastruct/common.h"
#include "alessastruct/file.h"
#include "alessastruct/token.h"
#include "alessastruct/keyword.h"

typedef enum {
    None,
    SearchingState,
    DeclarationState,
    DeclarationTypeState,
    DeclarationDeclaratorState,
    EndOfDeclarationState,
    AttributeSpecifierState,
    StructOrUnionState,
    EnumState,
    FunctionState,
    JustRunUntilBracesEnd,
    JustRunUntilBracketsEnd,
    JustSkipDeclaration,
    PragmaState
} AlessaParserStateMode;

typedef enum {
    NoSign,
    SignedSign,
    UnsignedSign,
} TypeSign;

typedef struct {
    KeywordKind specifierKind;
    KeywordIndex specifierKeywordIndex;
    int storageClass;

    char* firstIdentifierString;
    char* typeSpecifierName;
    char* declaratorString;
    TypeSign typeSign;
    u_long typeFlags;

    char* attributeIdentifierName;
    char* attributeParameters;

    char* tagName;
    char* functionName;

    bool isStruct;
    bool isUnion;
    bool isEnum;

    u_int pointerCount;
    u_int repeatCount;
    bool isArray;
    bool arrayNeedsUpdate;
    bool incomplete;

    bool isBitfield;
    u_int bitfieldSize;
} DeclarationNodeData;

typedef union {
    DeclarationNodeData declaration;
} NodeData;

typedef enum {
    DeclarationNode
} NodeKind;

typedef struct AlessaSyntaxTreeNode {
    u_long id;
    NodeKind kind;
    NodeData data;

    struct AlessaSyntaxTreeNode* mother;
    u_long motherId;
} AlessaSyntaxTreeNode;

typedef struct {
    AlessaParserStateMode mode;
    AlessaParserStateMode stash;
    int submode;
    int braceDepth;
    int parenDepth;
    int bracketDepth;
    bool unhandled;

    FileStreamBuffer buffer;
    AlessaTokenState tokenState;
    AlessaSyntaxTreeNode* node;
    AlessaSyntaxTreeNode nodeBuffer[NODE_BUFFER_SIZE];

    u_int nodeCounter;
} AlessaParserState;

AlessaSyntaxTreeNode* alessaParseToken(AlessaParserState* state, Token* token);

AlessaParserState* alessaInitParserState(void);

AlessaSyntaxTreeNode* getNodeMother(AlessaSyntaxTreeNode* node);

void setNodeMother(AlessaSyntaxTreeNode* node, AlessaSyntaxTreeNode* mother);

#endif // ALESSASTRUCT_PARSE_H
