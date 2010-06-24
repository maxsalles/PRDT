/*
** Define os tipos para o restante do compilador
** Prefixo: pty
** $ Herond Robaina Salles
** 24 Mai 2010
*/

/* ========================================================================== */

#ifndef PRD_TYPES
#define PRD_TYPES

#include <string.h>

#include "pstring.h"

#define PTY_NULL_TOKEN (ptySetToken(PTY_NONE, NULL, 0))

/* ========================================================================== */

typedef enum {
    /*== para controle ===============*/
    PTY_END_OF_FILE                 = 0,
    PTY_NONE                        = 1,

    /*== erros léxicos ===============*/
    PTY_ERROR_COMMENT               = 10,
    PTY_ERROR_HEXADECIMAL_CONSTANT  = 11,
    PTY_ERROR_BINARY_CONSTANT       = 12,
    PTY_ERROR_OCTAL_CONSTANT        = 13,
    PTY_ERROR_FLOAT_CONSTANT        = 14,
    PTY_ERROR_DECIMAL_CONSTANT      = 15,
    PTY_ERROR_STRING_CONSTANT       = 16,
    PTY_ERROR_DIRECTIVE             = 17,

    /*== tipos fundamentais ===========*/
    /*
    PTY_VOID                        = 30,
    PTY_SMALLINT                    = 31,
    PTY_UNSIGNED                    = 32,
    PTY_INT                         = 33,
    PTY_BIGINT                      = 34,
    PTY_FLOAT                       = 35,
    PTY_DOUBLE                      = 36,
    PTY_STRING                      = 37,
    */

    /*== qualificadores ===============*/
    /*
    PTY_STATIC                      = 50,
    PTY_CONST                       = 51,
    PTY_SHARED                      = 52,
    PTY_MODEL                       = 53,
    PTY_LOCKED                      = 54,
    PTY_IMMUTABLE                   = 55,
    PTY_INVISIBLE                   = 56,
    PTY_INTERNAL                    = 57,
    */

    /*== funções nativas diretas ======*/
    /*
    PTY_ARGUMENT                    = 70,
    PTY_SELECT                      = 71,
    PTY_SIZEOF                      = 72,
    PTY_ALLOC                       = 73,
    PTY_FREE                        = 74,
    PTY_REPEAT                      = 75,
    PTY_SIMILAR                     = 77,
    PTY_SKIP                        = 78,
    PTY_EXIT                        = 79,
    PTY_READ                        = 80,
    PTY_WRITE                       = 81,
    PTY_SYSTEM                      = 82,
    PTY_THROW                       = 83,
    PTY_CATCH                       = 84,
    */

    /*== funções nativas operadores ===*/
    /*
    PTY_NOT                         = 90,
    PTY_INC                         = 91,
    PTY_DEC                         = 92,
    PTY_MUL                         = 93,
    PTY_DIV                         = 94,
    PTY_MOD                         = 95,
    PTY_ADD                         = 96,
    PTY_SUB                         = 97,
    PTY_TO                          = 98,
    PTY_SML                         = 99,
    PTY_SEQ                         = 100,
    PTY_BIG                         = 101,
    PTY_BEG                         = 102,
    PTY_EQV                         = 103,
    PTY_DIF                         = 104,
    PTY_EQL                         = 105,
    PTY_NQL                         = 106,
    PTY_AND                         = 107,
    PTY_OR                          = 108,
    PTY_AML                         = 109,
    PTY_ADV                         = 110,
    PTY_AMD                         = 111,
    PTY_AAD                         = 112,
    PTY_AMN                         = 113,
    PTY_IST                         = 114,
    PTY_ASG                         = 115,
    PTY_DEF                         = 116,
    PTY_ADF                         = 117,
    */

    /*== constante universal ==========*/
    PTY_NULL_VAL                    = 130,

    /*== operadores ====================*/
    PTY_OP_NOT                      = 140,
    PTY_OP_INC                      = 141,
    PTY_OP_DEC                      = 142,
    PTY_OP_MUL                      = 143,
    PTY_OP_DIV                      = 144,
    PTY_OP_MOD                      = 145,
    PTY_OP_ADD                      = 146,
    PTY_OP_SUB                      = 147,
    PTY_OP_TO                       = 148,
    PTY_OP_SML                      = 149,
    PTY_OP_SEQ                      = 150,
    PTY_OP_BIG                      = 151,
    PTY_OP_BEG                      = 152,
    PTY_OP_EQV                      = 153,
    PTY_OP_DIF                      = 154,
    PTY_OP_EQL                      = 155,
    PTY_OP_NQL                      = 156,
    PTY_OP_AND                      = 157,
    PTY_OP_OR                       = 158,
    PTY_OP_AML                      = 159,
    PTY_OP_ADV                      = 160,
    PTY_OP_AMD                      = 161,
    PTY_OP_AAD                      = 162,
    PTY_OP_AMN                      = 163,
    PTY_OP_IST                      = 164,
    PTY_OP_ASG                      = 165,
    PTY_OP_DEF                      = 166,
    PTY_OP_ADF                      = 167,

    /*== directivas ===================*/
    PTY_USES                        = 175,
    PTY_LINKED                      = 176,
    PTY_ONLY                        = 177,
    PTY_EXCEPT                      = 178,
    PTY_OPERATOR                    = 179,
    PTY_CONST                       = 180,
    PTY_MAIN                        = 181,

    /*== símbolos =====================*/
    PTY_END_COMMAND                 = 190,
    /*
    PTY_COMMA                       = 191,
    */
    PTY_RETICENCE                   = 192,
    PTY_DOT                         = 193,
    PTY_ESCOPE_RESOLUTION           = 194,
    PTY_POINTER                     = 195,

    /*== delimitadores ================*/
    PTY_LEFT_PARENTHESIS            = 200,
    PTY_RIGHT_PARENTHESIS           = 201,
    PTY_LEFT_BRACE                  = 202,
    PTY_RIGHT_BRACE                 = 203,
    PTY_LEFT_BRACKET                = 204,
    PTY_RIGHT_BRACKET               = 205,

    /*== literais ======================*/
    PTY_BIN_INT_VAL                 = 210,
    PTY_OCTAL_INT_VAL               = 211,
    PTY_DECIMAL_INT_VAL             = 212,
    PTY_HEXADECIMAL_INT_VAL         = 213,
    PTY_FLOAT_VAL                   = 214,
    PTY_STRING_VAL                  = 215,

    /*== outros ========================*/
    PTY_ID                          = 220,
    PTY_COMMENT                     = 221

} PtyTokenId;

typedef struct {
    int      id;
    char*    lexeme;
    unsigned line;
} PtyToken;


const PtyToken PTY_RESERVED_WORDS[] = {
    /*
    { PTY_VOID,      "void",        0 },
    { PTY_SMALLINT,  "smallint",    0 },
    { PTY_UNSIGNED,  "unsigned",    0 },
    { PTY_INT,       "int",         0 },
    { PTY_BIGINT,    "bigint",      0 },
    { PTY_FLOAT,     "float",       0 },
    { PTY_DOUBLE,    "double",      0 },
    { PTY_STRING,    "string",      0 },

    { PTY_STATIC,    "static",      0 },
    { PTY_CONST,     "const",       0 },
    { PTY_SHARED,    "shared",      0 },
    { PTY_MODEL,     "model",       0 },
    { PTY_LOCKED,    "locked",      0 },
    { PTY_IMMUTABLE, "immutable",   0 },
    { PTY_INVISIBLE, "invisible",   0 },
    { PTY_INTERNAL,  "internal",    0 },

    { PTY_ARGUMENT,  "argument",    0 },
    { PTY_SELECT,    "select",      0 },
    { PTY_SIZEOF,    "sizeof",      0 },
    { PTY_ALLOC,     "alloc",       0 },
    { PTY_FREE,      "free",        0 },
    { PTY_REPEAT,    "repeat",      0 },
    { PTY_SIMILAR,   "similar",     0 },
    { PTY_SKIP,      "skip",        0 },
    { PTY_EXIT,      "exit",        0 },
    { PTY_READ,      "read",        0 },
    { PTY_WRITE,     "write",       0 },
    { PTY_SYSTEM,    "system",      0 },
    { PTY_THROW,     "throw",       0 },
    { PTY_CATCH,     "catch",       0 },

    { PTY_NOT,       "_not",        0 },
    { PTY_INC,       "_inc",        0 },
    { PTY_DEC,       "_dec",        0 },
    { PTY_MUL,       "_mul",        0 },
    { PTY_DIV,       "_div",        0 },
    { PTY_MOD,       "_mod",        0 },
    { PTY_ADD,       "_add",        0 },
    { PTY_SUB,       "_sub",        0 },
    { PTY_TO,        "_to",         0 },
    { PTY_SML,       "_sml",        0 },
    { PTY_SEQ,       "_seq",        0 },
    { PTY_BIG,       "_big",        0 },
    { PTY_BEG,       "_beg",        0 },
    { PTY_EQV,       "_eqv",        0 },
    { PTY_DIF,       "_dif",        0 },
    { PTY_EQL,       "_eql",        0 },
    { PTY_NQL,       "_nql",        0 },
    { PTY_AND,       "_and",        0 },
    { PTY_OR,        "_or",         0 },
    { PTY_AML,       "_aml",        0 },
    { PTY_ADV,       "_adv",        0 },
    { PTY_AMD,       "_amd",        0 },
    { PTY_AAD,       "_aad",        0 },
    { PTY_AMN,       "_amn",        0 },
    { PTY_IST,       "_ist",        0 },
    { PTY_ASG,       "_asg",        0 },
    { PTY_DEF,       "_def",        0 },
    { PTY_ADF,       "_adf",        0 },
    { PTY_NULL_VAL,  "NULL",        0 },
    */

    { PTY_NONE,      NULL,          0 }
};

const PtyToken PTY_DIRECTIVES[] = {
    { PTY_USES,      "@uses",       0 },
    { PTY_LINKED,    "@linked",     0 },
    { PTY_ONLY,      "@only",       0 },
    { PTY_EXCEPT,    "@except",     0 },
    { PTY_OPERATOR,  "@operator",   0 },
    { PTY_CONST,     "@const",      0 },
    { PTY_STATIC,    "@static",     0 },
    { PTY_SHARED,    "@shared",     0 },
    { PTY_MODEL,     "@model",      0 },
    { PTY_LOCKED,    "@locked",     0 },
    { PTY_INVISIBLE, "@invisible",  0 },
    { PTY_INTERNAL,  "@internal",   0 },
    { PTY_MAIN,      "@main",       0 },

    { PTY_NONE,      NULL,          0 }
};

/* ========================================================================== */

PtyToken ptySetToken (int id, const char* lexeme, unsigned line) {
    PtyToken token_return = { id, pstPersist(lexeme), line };

    return token_return;
}

PtyToken ptyCopyToken (PtyToken token) {
    PtyToken token_return = { token.id, token.lexeme, token.line };

    return token_return;
}

int ptyIsNullToken (PtyToken token) {
    return token.id == PTY_NONE ? 1 : 0;
}

int ptyIsLastToken (PtyToken token) {
    return token.id == PTY_END_OF_FILE ? 1 : 0;
}

PtyToken ptyGetToken (const char* lexeme, const PtyToken token_list[]) {
    if (lexeme) {
        PtyToken current_token = token_list[0];
        int i                  = 0;

        while (current_token.id != PTY_NONE) {
            if (!strcmp(lexeme, current_token.lexeme))
                return current_token;

            current_token = token_list[++i];
        }

        return PTY_NULL_TOKEN;
    } exit(1); /* trocar por um erro apropriado */
}

/* ========================================================================== */

#endif

