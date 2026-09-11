#include <string.h>
#include <stdlib.h>

#include "alessastruct/debug.h"
#include "alessastruct/parse.h"
#include "alessastruct/string.h"
#include "alessastruct/print.h"

static AlessaParserState alessaParserState;

static void storeStash(AlessaParserState* state, AlessaParserStateMode mode);

static void popStash(AlessaParserState* state);

static void storeStash(AlessaParserState* state, AlessaParserStateMode mode) {
    if (state->stash != 0) {
        alessaDebug("stash contents not empty: %d", state->stash);
        alessaError("something was already in the stash!");
    }

    if (mode == 0) {
        alessaError("cannot stash the zeroth state");
    }

    state->stash = mode;

    alessaDebug("storeStash: %d\n", mode);
}

static void popStash(AlessaParserState* state) {
    int stashed = state->stash;

    if (stashed != 0) {
        state->stash = 0;
        state->mode = stashed;
        alessaDebug("popStash: restored state %d\n", stashed);
    } else {
        alessaError("there wasn't anything in the stash.");
    }
}

inline AlessaSyntaxTreeNode* getNodeMother(AlessaSyntaxTreeNode* node) {
    if (node && node->id) {
        AlessaSyntaxTreeNode* mother = node->mother;

        if (mother != NULL && node->motherId == mother->id) {
            return mother;
        }
    }

    return NULL;
}

inline void setNodeMother(AlessaSyntaxTreeNode* node, AlessaSyntaxTreeNode* mother) {
    node->mother = mother;
    node->motherId = mother ? mother->id : 0;
}


AlessaSyntaxTreeNode* alessaParseToken(AlessaParserState* state, Token* token) {
    AlessaSyntaxTreeNode* node = state->node;

    #ifdef ALESSA_DEBUG
    if (!state->unhandled) {
        alessaDebug("\nalessaParseToken\n");
        switch (token->kind) {
            default:
            case AnyToken:
                alessaDebug("some token:\t'%c' (Kind = %d)\n", token->data.character, token->kind);
                break;

            case Semicolon:
                alessaDebug("semicolon:\t'%c' (Kind = %d)\n", token->data.character, token->kind);
                break;

            case Number:
                alessaDebug("number:\t\t'%s' (Kind = %d)\n", token->data.number.literal, token->kind);
                break;

            case Keyword:
            case Identifier:
                alessaDebug("identifier:\t'%s' (Kind = %d, Keyword = %d)\n", token->data.identifier.name, token->kind, token->data.identifier.keywordIndex);
                break;

            case Paren:
            case Brace:
            case Bracket:
                alessaDebug("parenthetical:\t'%c' (Kind = %d)\n", token->data.parenthetical.character, token->kind);
                break;
        }     
    }
    #endif

    while (true) {
        int keywordIndex;
        KeywordInfo* keywordInfo;

        node = state->node;
        if (node->id == 0) {
            node->id = ++state->nodeCounter;
            memset(&node->data, 0, sizeof(DeclarationNodeData));
        }

        keywordIndex = token->kind == Keyword ? token->data.identifier.keywordIndex : -1;
        keywordInfo = keywordIndex >= 0 ? (KeywordInfo*) &alessaKeywordTable[keywordIndex] : NULL;

        if (!state->unhandled) {
            alessaDebug("[state] %d [keyword index] %d\n", state->mode, keywordIndex);
        }
    
        switch (state->mode) {
            case SearchingState: {
                if (keywordInfo == NULL) {
                    if (token->kind == Hash) {
                        state->mode = PragmaState;
                        state->submode = 0;
                    } else if (token->kind == Identifier) {
                        // starting with an identifier may indicate the return
                        // type of a function declaration
                        // unhandled...
                        alessaDebug("unhandled: identifier at start of declaration?\n");
                        state->unhandled = true;
                        state->mode = JustSkipDeclaration;
                    }
                    return NULL;
                }

                switch (keywordInfo->kind) {
                    case StorageClassSpecifier:
                    case TypeSpecifier:
                    case TypeQualifier:
                    case FunctionSpecifier: {
                        DeclarationNodeData* data = &node->data.declaration;
                        state->mode = DeclarationState;
                        node->kind = DeclarationNode;
                        memset(data, 0, sizeof(DeclarationNodeData));
                        data->specifierKind = keywordInfo->kind;
                        data->specifierKeywordIndex = keywordIndex;
                        data->storageClass = -1;
                        /*
                        data->typeSign = NoSign;
                        data->typeFlags = 0;
                        data->isStruct = false;
                        data->isUnion = false;
                        data->isEnum = false;
                        data->tagName = NULL;
                        data->functionName = NULL;
                        data->attributeIdentifierName = NULL;
                        data->attributeParameters = NULL;
                        */
                        alessaDebug("identifier:\t'%s' (Kind = %d, Keyword = %d)\n", token->data.identifier.name, token->kind, token->data.identifier.keywordIndex);
                        break;
                    }
                    default:
                        return NULL;
                }
                continue;
            }

            case DeclarationState: {
                DeclarationNodeData* data = &node->data.declaration;
                if (data->specifierKind == FunctionSpecifier ||
                    data->specifierKind == TypeQualifier) {
                    /* unhandled */
                    state->mode = SearchingState;
                    break;
                }

                if (data->specifierKind == StorageClassSpecifier &&
                    data->specifierKeywordIndex != KeywordTypedef) {
                    /* unhandled */
                    state->mode = DeclarationTypeState;
                    break;
                }

                state->mode = DeclarationTypeState;

                if (data->specifierKeywordIndex == KeywordTypedef) {
                    data->storageClass = KeywordTypedef;
                    break;
                }

                continue;
            }

            case DeclarationTypeState: {
                DeclarationNodeData* data = &node->data.declaration;

                if (keywordInfo == NULL) {
                    if (token->kind != Identifier) {
                        if (token->kind == Brace) {
                            AlessaSyntaxTreeNode* mother = getNodeMother(node);
                            alessaDebug("encountered brace in declarator\n");
                            alessaDebug("node %p <- %p <- %p\n", node, mother, mother->mother);
                            alessaAssert(token->data.parenthetical.direction == Right);
                            alessaAssert(mother);
                            state->braceDepth--;
                            state->node = mother;
                            break;
                        }

                        if (token->kind == Asterisk) {
                            data->pointerCount++;
                            break;
                        }

                        if (token->kind == Paren) {
                            alessaDebug("unhandled (!) skipping this member...");
                            state->mode = JustSkipDeclaration;
                            data->incomplete = true;
                            break;
                        }

                        if (token->kind == Semicolon) {
                            state->mode = EndOfDeclarationState;
                            continue;
                        }

                        alessaError("expected an identifier");
                    }


                    if (data->firstIdentifierString != NULL) {
                        printStringTable();
                    }
                    alessaAssert(data->firstIdentifierString == NULL);

                    data->firstIdentifierString = intoStringTable(token->data.identifier.name);
                    alessaDebug("set first identifier: %s\n", data->firstIdentifierString);
                    if (data->typeFlags == 0) {
                        // if typeFlags == 0 here, then the type specifier is
                        // only a typedef name. otherwise, the identifier has to
                        // be part of the type declarator
                        data->typeSpecifierName = data->firstIdentifierString;
                    }

                    state->mode = DeclarationDeclaratorState;
                    continue;
                }

                if (data->typeFlags == 0) {
                    if (keywordIndex == KeywordStruct) {
                        data->isStruct = true;
                        state->mode = DeclarationDeclaratorState;
                    } else if (keywordIndex == KeywordUnion) {
                        data->isUnion = true;
                        state->mode = DeclarationDeclaratorState;
                    } else if (keywordIndex == KeywordEnum) {
                        data->isEnum = true;
                        state->mode = DeclarationDeclaratorState;
                    } else if (keywordInfo->kind == FunctionSpecifier) {
                        /* unhandled */
                        break;
                    } else if (keywordInfo->kind == TypeQualifier) {
                        /* unhandled */
                        data->typeFlags |= (1 << keywordIndex);
                        break;
                    } else if (keywordInfo->kind != TypeSpecifier) {
                        alessaError("expected keyword to be a type specifier");
                    }
                }
                
                if (keywordInfo->kind != TypeSpecifier) {
                    if (data->typeFlags != 0) {
                        alessaError("invalid combination of type specifiers");
                    }
                    if (!(data->isStruct || data->isEnum || data->isUnion)) {
                        state->mode = DeclarationDeclaratorState;
                        continue;
                    }
                }

                data->typeFlags |= (1 << keywordIndex);

                break;
            }

            case DeclarationDeclaratorState: {
                DeclarationNodeData* data = &node->data.declaration;

                alessaDebug("test\n");

                if (data->isArray && data->arrayNeedsUpdate) {
                    if (token->kind == Bracket && token->data.parenthetical.direction == Right) {
                        data->repeatCount = 0;
                        data->arrayNeedsUpdate = false;
                        data->pointerCount++;
                        break;
                    }

                    alessaAssert(token->kind == Number);
                    if (data->repeatCount == 0) {
                        data->repeatCount = 1;
                    }
                    data->arrayNeedsUpdate = false;
                    data->repeatCount *= strtol(token->data.number.literal, NULL, token->data.number.base);
                    break;
                } else if (data->isBitfield && data->bitfieldSize == 0) {
                    alessaAssert(token->kind == Number);
                    data->bitfieldSize = strtol(token->data.number.literal, NULL, token->data.number.base);
                    break;
                }
                if (token->kind == Colon) {
                    data->isBitfield = true;
                    break;
                }

                 if (token->kind == Asterisk) {
                    data->pointerCount++;
                    alessaDebug("incr pointer count %d", data->pointerCount);
                    break;
                }

                if (token->kind == Bracket) {
                    // alessaDebug("unhandled: array declarators\n");
                    // storeStash(state, state->mode);
                    // state->mode = JustRunUntilBracketsEnd;
                    if (token->data.parenthetical.direction == Left) {
                        data->isArray = true;
                        data->arrayNeedsUpdate = true;
                    }
                    break;
                }

                if (data->isStruct || data->isUnion || data->isEnum) {
                    if (token->kind == Identifier) {
                        data->tagName = intoStringTable(token->data.identifier.name);
                        break;
                    }
                    if (token->kind == Semicolon || keywordIndex == KeywordAttribute) {
                        state->mode = EndOfDeclarationState;
                        continue;
                    }
                    if (token->kind != Brace && token->data.parenthetical.direction != Left) {
                        alessaError("expected an opening brace following struct/union/enum declaration");
                    }
                    state->braceDepth++;
                    if (data->isStruct || data->isUnion) {
                        state->mode = StructOrUnionState;
                    } else {
                        state->mode = EnumState;
                    }
                    break;
                }

                if (token->kind == Identifier) {
                    alessaDebug("identifier in declarator: %s %s\n", data->firstIdentifierString, data->declaratorString);
                    if (data->firstIdentifierString == NULL) {
                        data->firstIdentifierString = intoStringTable(token->data.identifier.name);
                    } 
                    data->declaratorString = intoStringTable(token->data.identifier.name);
                    break;
                }

                if (token->kind == Paren) {
                    alessaAssert(data->firstIdentifierString != NULL);
                    data->functionName = data->firstIdentifierString;

                    if (token->data.parenthetical.direction == Right) {
                        alessaError("invalid parenthesis in declarator");
                    }
                    state->mode = FunctionState;
                    state->submode = 0;
                    state->parenDepth++;
                    break;
                }

                state->mode = EndOfDeclarationState;

                continue;
            }

            case StructOrUnionState: {
                AlessaSyntaxTreeNode* mother = getNodeMother(node);
                AlessaSyntaxTreeNode* next = ++state->node;

                memset(next, 0, sizeof(AlessaSyntaxTreeNode));
                next->kind = DeclarationNode;
                
                setNodeMother(next, mother ? mother : node);
                
                state->mode = DeclarationTypeState;

                continue;
            }

            case EnumState: {
                alessaDebug("@warning: enums not implemented yet\n\t");

                storeStash(state, DeclarationTypeState);
                state->mode = JustRunUntilBracesEnd;
                
                continue;
            }

            case JustRunUntilBracesEnd: {
                if (token->kind == Brace) {
                    state->braceDepth += token->data.parenthetical.direction;
                }
                if (state->braceDepth == 0) {
                    popStash(state);
                    state->unhandled = false;
                    break;
                }
                break;
            }

            case JustRunUntilBracketsEnd: {
                if (token->kind == Bracket) {
                    state->bracketDepth += token->data.parenthetical.direction;
                }
                if (state->bracketDepth == 0) {
                    popStash(state);
                    state->unhandled = false;
                    break;
                }
                break;
            }
            
            case JustSkipDeclaration: {
                if (token->kind == Brace) {
                    state->mode = JustRunUntilBracesEnd;
                    storeStash(state, EndOfDeclarationState);
                    continue;
                } else if (token->kind == Semicolon) {
                    state->mode = EndOfDeclarationState;
                    continue;
                }
                break;
            }
            
            case FunctionState: {
                state->unhandled = true;
                if (token->kind == Paren) {
                    state->parenDepth += token->data.parenthetical.direction;
                }
                alessaDebug("@warning: functions not implemented (paren depth: %d)\n\t", state->parenDepth);
                if (state->parenDepth == 0) {
                    switch (state->submode) {
                        case 0:
                            if (token->kind == Paren) {
                                state->submode++;
                            } else {
                                state->unhandled = false;
                                state->mode = EndOfDeclarationState;
                            }
                            break;
                        
                        default:
                            if (token->kind == Brace) {
                                storeStash(state, SearchingState);
                                state->mode = JustRunUntilBracesEnd;
                                continue;
                            } else {
                                state->unhandled = false;
                                state->mode = EndOfDeclarationState;
                                continue;
                            }
                            break;
                    }
                    break;
                }

                break;
            }


            case AttributeSpecifierState: {
                switch (state->submode) {
                    case 0:
                    case 1:
                        if (token->kind != Paren && token->data.parenthetical.direction != Left) {
                            alessaError("invalid __attribute__ syntax");
                        }
                        state->submode++;
                        break;
                    
                    case 2:
                        if (token->kind != Identifier) {
                            alessaError("expected an identifier in __attribute__");
                        }
                        node->data.declaration.attributeIdentifierName = intoStringTable(token->data.identifier.name);
                        state->submode++;
                        break;
                    
                    case 3:
                        if (token->kind != Paren) {
                            alessaError("expected parenthesis following __attribute__ identifier");
                        }
                        if (token->data.parenthetical.direction == Left) {
                            state->submode = 4;
                        } else {
                            state->submode = 6;
                        }
                        break;
                    
                    case 4:
                        if (token->kind != Identifier && token->kind != Number) {
                            alessaError("expected an identifier in __attribute__ parameters");
                        }
                        node->data.declaration.attributeParameters = intoStringTable(token->data.identifier.name);
                        state->submode++;
                        break;

                    case 5:
                    case 6:
                    case 7:
                        if (token->kind != Paren && token->data.parenthetical.direction != Right) {
                            alessaError("expected closed parenthesis following __attribute__ parameters");
                        }
                        if (++state->submode == 8) {
                            state->submode = 0;
                            popStash(state);
                        }
                        break;
                }

                break;
            }

            case PragmaState: {
                if (state->submode == 0) {
                    alessaAssert(token->kind == Identifier);
                    alessaAssert(strcmp(token->data.identifier.name, "pragma") == 0);
                    state->submode++;
                } else if (state->submode == 1) {
                    alessaAssert(token->kind == Identifier);
                    alessaDebug("pragma: %s", token->data.identifier.name);
                    state->submode++;
                } else if (state->submode == 2) {
                    char* name = token->data.identifier.name;
                    alessaAssert(token->kind == Identifier);
                    alessaAssert((strcmp(name, "on") == 0) || (strcmp(name, "off") == 0));
                    alessaDebug("pragma %s", name);
                    state->mode = SearchingState;
                    state->submode = 0;
                }
                break;
            }

            case EndOfDeclarationState: {
                if (keywordInfo != NULL && keywordInfo->kind == AttributeSpecifier) {
                    // @todo: store whether the attribute is on type, tag, or something else
                    storeStash(state, EndOfDeclarationState);
                    state->mode = AttributeSpecifierState;
                    state->submode = 0;
                    break;
                }
                if (token->kind != Semicolon) {
                    alessaError("expected end of declaration");
                }
                if (!getNodeMother(node)) {
                    alessaDebug("node->mother: %p\n", node->mother);
                    state->mode = SearchingState;
                    return node;
                } else {
                    alessaDebug("node->mother: %p\n", node->mother);
                    if (ALESSA_DEBUG) {
                        prettyPrintOneNode(node, "----\t\t\t");
                    }
                    state->mode = StructOrUnionState; // @todo: get this from node?
                }
                break;
            }

            case None:
            default:
                alessaDebug("unhandled state %d", state->mode);
                alessaAssert(0);
        }

        break;
    }

    return NULL;
}

AlessaParserState* alessaInitParserState(void) {
    AlessaParserState* state = &alessaParserState;

    state->mode = SearchingState;
    state->node = state->nodeBuffer;

    return state;
}

