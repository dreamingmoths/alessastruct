#include "alessastruct/token.h"
#include "alessastruct/file.h"
#include "alessastruct/keyword.h"

inline bool isDigitCharacter(char character) {
    return (character >= '0' && character <= '9');
}

inline bool isSpacingCharacter(char character) {
    switch (character) {
        case ' ':
        case '\n':
        case '\r':
        case '\t':
            return true;

        default:
            return false;
    }
}

inline bool isIdentifierStartingCharacter(char character) {
    return (character >= 'a' && character <= 'z') || 
           (character >= 'A' && character <= 'Z') || 
           (character == '_');
}

inline bool isIdentifierCharacter(char character) {
    return isIdentifierStartingCharacter(character) ||
           isDigitCharacter(character);
}

Token* alessaReadToken(AlessaTokenState* state) {
    Token* token = &state->token;
    char value;

    state->currentCharacter = state->nextCharacter;
    state->nextCharacter = state->currentCharacter + 1;

    value = *state->currentCharacter;
    token->data.character = value;
    token->kind = AnyToken;

    if (isSpacingCharacter(value)) {
        state->currentCharacter++;
        return NULL;
    }

    switch (value) {
        case 0:
            token->kind = EmptyToken;
            return token;

        case '{':
            token->kind = Brace;
            token->data.parenthetical.direction = Left;
            break;

        case '}':
            token->kind = Brace;
            token->data.parenthetical.direction = Right;
            break;

        case '[':
            token->kind = Bracket;
            token->data.parenthetical.direction = Left;
            break;

        case ']':
            token->kind = Bracket;
            token->data.parenthetical.direction = Right;
            break;

        case '(':
            token->kind = Paren;
            token->data.parenthetical.direction = Left;
            break;

        case ')':
            token->kind = Paren;
            token->data.parenthetical.direction = Right;
            break;

        case ';':
            token->kind = Semicolon;
            break;

        case ':':
            token->kind = Colon;
            break;

        case ',':
            token->kind = Comma;
            break;

        case '*':
            token->kind = Asterisk;
            break;

        case '#':
            token->kind = Hash;
            break;
    }

    if (token->kind == AnyToken) {
        ReadResult result;
        char* current = state->currentCharacter;

        if (isIdentifierStartingCharacter(value)) {
            char* name = token->data.identifier.name;

            int length = readWhile(&result, name, current, isIdentifierCharacter);
            int keywordIndex = searchKeywordTable(result.hash);

            state->nextCharacter = current + length;

            token->kind = keywordIndex > 0 ? Keyword : Identifier;
            token->data.identifier.nameLength = length;
            token->data.identifier.hash = result.hash;
            token->data.identifier.keywordIndex = keywordIndex;

            return token;
        }
        
        if (isDigitCharacter(value)) {
            NumberTokenData* data = &token->data.number;
            char* literal = data->literal;
            int length = 0;
            int base = 10;

            if (value == '0') {
                *literal++ = *current++;
                length++;

                if (*current == 'x') {
                    base = 16;
                    *literal++ = *current++;
                    length++;
                }
            }

            length += readWhile(&result, literal, current, isDigitCharacter);
            state->nextCharacter = current + length;

            token->kind = Number;
            data->base = base;
            data->literalLength = length;

            return token;
        }
    }

    return token;
}
