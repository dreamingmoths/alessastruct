#include "alessastruct/types.h"
#include "alessastruct/keyword.h"

const char* alessaKeywordStringTable[ALESSA_KEYWORD_COUNT] = {
    "auto",
    "break",
    "case",
    "char",
    "const",
    "continue",
    "default",
    "do",
    "double",
    "else",
    "enum",
    "extern",
    "float",
    "for",
    "goto",
    "if",
    "inline",
    "int",
    "long",
    "register",
    "restrict",
    "return",
    "short",
    "signed",
    "sizeof",
    "static",
    "struct",
    "switch",
    "typedef",
    "union",
    "unsigned",
    "void",
    "volatile",
    "while",

    /* gnu c extension */
    "__attribute__"
};

const KeywordInfo alessaKeywordTable[ALESSA_KEYWORD_COUNT] = {
    { .name = "auto", .hash = 25475576049ul, .length = 4, .kind = StorageClassSpecifier },
    { .name = "break", .hash = 3267625155745ul, .length = 5, .kind = JumpStatement },
    { .name = "case", .hash = 25954880272ul, .length = 4, .kind = LabeledStatement },
    { .name = "char", .hash = 25968930282ul, .length = 4, .kind = TypeSpecifier },
    { .name = "const", .hash = 3299901818141ul, .length = 5, .kind = TypeQualifier },
    { .name = "continue", .hash = 6759462816353116409ul, .length = 8, .kind = JumpStatement },
    { .name = "default", .hash = 53714764570061055ul, .length = 7, .kind = LabeledStatement },
    { .name = "do", .hash = 1626997ul, .length = 2, .kind = IterationStatement },
    { .name = "double", .hash = 423285189892367ul, .length = 6, .kind = TypeSpecifier },
    { .name = "else", .hash = 26497701767ul, .length = 4, .kind = SelectionStatement },
    { .name = "enum", .hash = 26501831807ul, .length = 4, .kind = EnumSpecifier },
    { .name = "extern", .hash = 427778154230144ul, .length = 6, .kind = StorageClassSpecifier },
    { .name = "float", .hash = 3398238250500ul, .length = 5, .kind = TypeSpecifier },
    { .name = "for", .hash = 210739863ul, .length = 3, .kind = IterationStatement },
    { .name = "goto", .hash = 27024153597ul, .length = 4, .kind = JumpStatement },
    { .name = "if", .hash = 1706499ul, .length = 2, .kind = SelectionStatement },
    { .name = "inline", .hash = 444229189165575ul, .length = 6, .kind = FunctionSpecifier },
    { .name = "int", .hash = 216869137ul, .length = 3, .kind = TypeSpecifier },
    { .name = "long", .hash = 28324779012ul, .length = 4, .kind = TypeSpecifier },
    { .name = "register", .hash = 7769232839447758589ul, .length = 8, .kind = StorageClassSpecifier },
    { .name = "restrict", .hash = 7769283553062089476ul, .length = 8, .kind = TypeQualifier},
    { .name = "return", .hash = 481696805876496ul, .length = 6, .kind = JumpStatement },
    { .name = "short", .hash = 3826696748420ul, .length = 5, .kind = TypeSpecifier },
    { .name = "signed", .hash = 486021435838852ul, .length = 6, .kind = TypeSpecifier },
    { .name = "sizeof", .hash = 486026360313128ul, .length = 6, .kind = Sizeof },
    { .name = "static", .hash = 486383309389170ul, .length = 6, .kind = StorageClassSpecifier },
    { .name = "struct", .hash = 486387733801835ul, .length = 6, .kind = StructOrUnionSpecifier },
    { .name = "switch", .hash = 486484505558380ul, .length = 6, .kind = SelectionStatement },
    { .name = "typedef", .hash = 62325027180338325ul, .length = 7, .kind = StorageClassSpecifier },
    { .name = "union", .hash = 3894322015633ul, .length = 5, .kind = StructOrUnionSpecifier },
    { .name = "unsigned", .hash = 7977104772253253259ul, .length = 8, .kind = TypeSpecifier },
    { .name = "void", .hash = 30926144396ul, .length = 4, .kind = TypeSpecifier },
    { .name = "volatile", .hash = 8045283250308831012ul, .length = 8, .kind = TypeQualifier },
    { .name = "while", .hash = 3958837837071ul, .length = 5, .kind = IterationStatement },

    /* gnu c extension */
    { .name = "__attribute__", .hash = 11830752470807556260ul, .length = 13, .kind = AttributeSpecifier }
};

int searchKeywordTable(u_long hash) {
    int i;

    for (i = 0; i < ALESSA_KEYWORD_COUNT; i++) {
        if (alessaKeywordTable[i].hash == hash) {
            return i;
        }
    }

    return -1;
}

