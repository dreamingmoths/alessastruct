#ifndef ALESSASTRUCT_TOKEN_H
#define ALESSASTRUCT_TOKEN_H

#include "alessastruct/types.h"
#include "alessastruct/common.h"

typedef enum {
    Keyword,
    Identifier,
    Number,
    Brace,
    Paren,
    Bracket,
    Colon,
    Semicolon,
    Comma,
    Asterisk,
    Hash,
    AnyToken,
    EmptyToken
} TokenKind;

typedef enum {
    Left = 1,
    Right = -1
} LeftOrRight;

typedef struct {
    char name[MAX_TOKEN_READ_SIZE];
    int nameLength;
    u_long hash;
    int keywordIndex;
} IdentifierTokenData;

typedef struct {
    char literal[MAX_TOKEN_READ_SIZE];
    int literalLength;
    u_char base;
} NumberTokenData;

typedef struct {
    char character;
    LeftOrRight direction;
} ParentheticalTokenData;

typedef struct {
    char value;
} AnyTokenData;

typedef union {
    IdentifierTokenData identifier;
    NumberTokenData number;
    ParentheticalTokenData parenthetical;
    char character;
} TokenData;

typedef struct {
    TokenKind kind;
    TokenData data;
} Token;

typedef struct AlessaTokenState {
    Token token;

    char* currentCharacter;
    char* nextCharacter;
} AlessaTokenState;

bool isDigitCharacter(char character);

bool isSpacingCharacter(char character);

bool isIdentifierStartingCharacter(char character);

bool isIdentifierCharacter(char character);

Token* alessaReadToken(AlessaTokenState* state);

#endif // ALESSASTRUCT_TOKEN_H
