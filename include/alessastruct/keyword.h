#ifndef ALESSASTRUCT_KEYWORD_H
#define ALESSASTRUCT_KEYWORD_H

#include "alessastruct/types.h"

#define ALESSA_KEYWORD_COUNT 35

typedef enum {
    StorageClassSpecifier,
    TypeSpecifier,
    TypeQualifier,
    FunctionSpecifier,
    JumpStatement,
    IterationStatement,
    SelectionStatement,
    LabeledStatement,
    StructOrUnionSpecifier,
    EnumSpecifier,
    AttributeSpecifier,
    Sizeof
} KeywordKind;

typedef enum {
    KeywordAuto,
    KeywordBreak,
    KeywordCase,
    KeywordChar,
    KeywordConst,
    KeywordContinue,
    KeywordDefault,
    KeywordDo,
    KeywordDouble,
    KeywordElse,
    KeywordEnum,
    KeywordExtern,
    KeywordFloat,
    KeywordFor,
    KeywordGoto,
    KeywordIf,
    KeywordInline,
    KeywordInt,
    KeywordLong,
    KeywordRegister,
    KeywordRestrict,
    KeywordReturn,
    KeywordShort,
    KeywordSigned,
    KeywordSizeof,
    KeywordStatic,
    KeywordStruct,
    KeywordSwitch,
    KeywordTypedef,
    KeywordUnion,
    KeywordUnsigned,
    KeywordVoid,
    KeywordVolatile,
    KeywordWhile,

    /* gnu c extension */
    KeywordAttribute
} KeywordIndex;

typedef struct {
    char name[16];
    u_long hash;
    u_long length;
    KeywordKind kind;
} KeywordInfo;

extern const char* alessaKeywordStringTable[ALESSA_KEYWORD_COUNT];
extern const KeywordInfo alessaKeywordTable[ALESSA_KEYWORD_COUNT];

int searchKeywordTable(u_long hash);

#endif // ALESSASTRUCT_KEYWORD_H
