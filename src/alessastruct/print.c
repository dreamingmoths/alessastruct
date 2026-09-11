#include <string.h>

#include "alessastruct/parse.h"
#include "alessastruct/token.h"
#include "alessastruct/print.h"

void prettyPrintOneNode(AlessaSyntaxTreeNode* node, char* prefix) {
    #define prefixedPrint(message, ...) printf("%s" message, prefix, __VA_ARGS__);
    int i;
    printf("\n");
    prefixedPrint("node (id = %lu, kind = %d, mother = %p)", node->id, node->kind, getNodeMother(node));
    switch (node->kind) {
        case DeclarationNode: {
            DeclarationNodeData* data = &node->data.declaration;
            if (data->incomplete) {
                printf(" [incomplete 🔴]\n");
            }
            if (data->isStruct) {
                printf(" [struct node]\n");
            } else if (data->isUnion) {
                printf(" [union node]\n");
            } else if (data->isEnum) {
                printf(" [enum node]\n");
            } else {
                printf("\n");
            }
            prefixedPrint("specifier: %s (kind: %d)\n", alessaKeywordTable[data->specifierKeywordIndex].name, data->specifierKind);
            
            if (data->storageClass >= 0) {
                prefixedPrint("storage class: %s\n", alessaKeywordTable[data->storageClass].name);
            }
            if (data->typeSpecifierName != NULL) {
                prefixedPrint("type string: %s\n", data->typeSpecifierName);
            }
            if (data->firstIdentifierString != NULL) {
                prefixedPrint("last stored string: %s\n", data->firstIdentifierString);
            }
            if (data->declaratorString != NULL) {
                prefixedPrint("declarator string: %s\n", data->declaratorString);
            }
            if (data->bitfieldSize) {
                prefixedPrint("bitfield size: %d\n", data->bitfieldSize);
            }
            if (data->repeatCount) {
                prefixedPrint("array part total size: %d\n", data->repeatCount);
            }

            prefixedPrint("type flags: %lu", data->typeFlags);
            for (i = 0; i < ALESSA_KEYWORD_COUNT; i++) {
                if (data->typeFlags & (1 << i)) {
                    printf(" %s", alessaKeywordTable[i].name);
                }
            }
            printf("\n");
            if (data->attributeIdentifierName != NULL) {
                prefixedPrint("attribute: %s = %s", data->attributeIdentifierName, data->attributeParameters);
                printf("\n");
            }
            if (data->tagName != NULL) {
                prefixedPrint("tag name: %s", data->tagName);
                printf("\n");
            }
            if (data->functionName != NULL) {
                prefixedPrint("function name: %s", data->functionName);
                printf("\n");
            }
            printf("\n");
        }
    }
    printf("\n");
    #undef prefixedPrint
}

void prettyPrintNode(AlessaSyntaxTreeNode* node) {
    AlessaSyntaxTreeNode* mother = NULL;
    AlessaSyntaxTreeNode* current = node;

    char prefix[MAX_TOKEN_READ_SIZE] = "\t";
    int depth = 0;
    
    prettyPrintOneNode(node, prefix);

    current++;

    if (!getNodeMother(current)) {
        return;
    }

    printf("\tmembers:\n");

    while (current->mother) {
        if (current->mother != mother) {
            mother = getNodeMother(current);

            if (mother == NULL) {
                break;
            }

            prefix[++depth] = '\t';
            prefix[++depth] = 0;
        }

        prettyPrintOneNode(current, prefix);

        current++;
    }
}

void writeNodeAsC(FILE* file, AlessaSyntaxTreeNode* node) {
    #define writeFormat(...) fprintf(file, __VA_ARGS__)
    #define write(...) writeFormat("%s", __VA_ARGS__)
    DeclarationNodeData* data;
    bool isStructUnionOrEnum;
    bool isTypedef;

    if (!node || node->kind != DeclarationNode) {
        return;
    }

    data = &node->data.declaration;

    if (data->isEnum) {
        return;
    }

    isTypedef = data->storageClass == KeywordTypedef;
    if (isTypedef) {
        write("typedef ");
    }

    isStructUnionOrEnum = data->isStruct || data->isUnion || data->isEnum;

    // prettyPrintNode(node);
    if (isStructUnionOrEnum) {
        AlessaSyntaxTreeNode* current = node + 1;
        AlessaSyntaxTreeNode* mother;

        if (data->isStruct) {
            write("struct ");
        } else if (data->isUnion) {
            write("union ");
        } else if (data->isEnum) {
            write("enum ");
        }

        write(data->tagName);
        write(" {\n");

        while ((mother = getNodeMother(current))) {
            // prettyPrintOneNode(current, "\t\t\t----");
            writeNodeAsC(file, current);
            current++;
        }


        write("}");
                
        if (data->attributeIdentifierName) {
            writeFormat(" __attribute__((%s(%s)))", data->attributeIdentifierName, data->attributeParameters);
        }

        if (data->typeSpecifierName) {
            write(data->typeSpecifierName);
        } else if (isTypedef) {
            write(" ");
            write(data->tagName); // @todo: fix typedefs
        }

        write(";\n");
    } else {
        AlessaSyntaxTreeNode* mother = getNodeMother(node);
        
        if (mother || isTypedef) {
            int position = ftell(file);

            if ((isTypedef && (data->typeFlags & (1 << KeywordUnsigned))) || data->typeFlags == (1 << KeywordUnsigned)) {
                write("unsigned ");
            } else if ((isTypedef && (data->typeFlags & (1 << KeywordSigned))) || (data->typeFlags == (1 << KeywordSigned))) {
                write("signed ");
            }
            if (!isTypedef && (data->typeFlags & (1 << KeywordUnsigned))) {
                write("u_");
            }
            if (data->typeFlags & (1 << KeywordLong)) write("long ");
            if (data->typeFlags & (1 << KeywordInt)) write("int ");
            if (data->typeFlags & (1 << KeywordShort)) write("short ");
            if (data->typeFlags & (1 << KeywordFloat)) write("float ");
            if (data->typeFlags & (1 << KeywordChar)) write("char ");

            if (data->typeSpecifierName) {
                write(data->typeSpecifierName);
                write(" ");
            }

            if (data->declaratorString) {
                write(data->declaratorString);
            }

            if (data->repeatCount) {
                writeFormat("[%d]", data->repeatCount); // @todo: better array handling
            }

            if (data->bitfieldSize) {
                writeFormat(" : %d", data->bitfieldSize);
            } else if (data->attributeIdentifierName) {
                writeFormat(" __attribute__((%s(%s)))", data->attributeIdentifierName, data->attributeParameters);
            }

            if (position != ftell(file)) {
                write(";");
                write("\n");
            }
        }
    }

    #undef write
}

void writeNodeAsYaml(FILE* file, AlessaSyntaxTreeNode* node) {
    #define writeFormat(...) fprintf(file, __VA_ARGS__)
    #define write(...) writeFormat("%s", __VA_ARGS__)
    DeclarationNodeData* data;
    bool isStructUnionOrEnum;
    bool isTypedef;

    if (!node || node->kind != DeclarationNode) {
        return;
    }

    data = &node->data.declaration;

    if (data->isEnum || data->isUnion) {
        return;
    }

    isStructUnionOrEnum = data->isStruct || data->isUnion || data->isEnum;

    // prettyPrintNode(node);
    if (isStructUnionOrEnum) {
        AlessaSyntaxTreeNode* current = node + 1;
        AlessaSyntaxTreeNode* mother;

        // write("meta:\n");
        // write("\tid: ");
        write("    ");
        write(data->tagName);
        write(":\n");
        // write("\tendian: le\n\n");
                
        // if (data->attributeIdentifierName) {
        //     write("\t\tdoc: attribute: ((%s(%s)))\n", data->attributeIdentifierName, data->attributeParameters);
        // }
        // write("seq:\n");
        write("        seq:\n");
        
    
        while ((mother = getNodeMother(current))) {
            // prettyPrintOneNode(current, "\t\t\t----");
            writeNodeAsYaml(file, current);
            current++;
        }
    } else {
        AlessaSyntaxTreeNode* mother = getNodeMother(node);
        
        if (mother) {
            if (!data->declaratorString && !data->typeFlags && !data->bitfieldSize) {
                return;
            }

            write("         - ");

            if (data->declaratorString) {
                write("id: ");
                write(data->declaratorString);
                write("\n");
                write("           ");
            }


            write("type: ");


            if (data->bitfieldSize) {
                writeFormat("b%d", data->bitfieldSize);
            } else if (data->typeFlags > 0) {
                if (data->typeFlags & (1 << KeywordUnsigned)) {
                    write("u");
                } else if (!(data->typeFlags & (1 << KeywordFloat))) {
                    write("s");
                }
                if (data->typeFlags & (1 << KeywordLong)) write("8");
                else if (data->typeFlags & (1 << KeywordInt)) write("4");
                else if (data->typeFlags & (1 << KeywordShort)) write("2");
                else if (data->typeFlags & (1 << KeywordFloat)) write("f4");
                else if (data->typeFlags & (1 << KeywordChar)) write("1");
                else if (data->typeFlags & (1 << KeywordVoid)) write("4");
            } else if (data->typeSpecifierName) {
                if (strcmp(data->typeSpecifierName, "u_long") == 0) write("u8");
                else if (strcmp(data->typeSpecifierName, "u_int") == 0) write("u4");
                else if (strcmp(data->typeSpecifierName, "u_short") == 0) write("u2");
                else if (strcmp(data->typeSpecifierName, "u_char") == 0) write("u1");
                else write(data->typeSpecifierName);
            }
            write("\n");

            if (data->repeatCount) {
                write("           repeat: expr\n");
                writeFormat("           repeat-expr: %d\n", data->repeatCount);
            }
        
            if (data->incomplete) {
                write("           doc: this field had incomplete information at compile time\n");
            }
            // if (data->attributeIdentifierName) {
            //     write("# __attribute__((%s(%s)))", data->attributeIdentifierName, data->attributeParameters);
            // }
        }
    }

    #undef write
    #undef writeFormat
}


void alessaPrintKeywords(void) {
    ReadResult result;
    char buffer[MAX_TOKEN_READ_SIZE];
    int i;

    for (i = 0; i < ALESSA_KEYWORD_COUNT; i++) {
        const char* keyword = alessaKeywordStringTable[i];
        readWhile(&result, buffer, (char*) keyword, isIdentifierCharacter);
        printf("{ .name = \"%s\", .hash = %luul, .length = %d },\n", keyword, result.hash, result.length);
    }
}

