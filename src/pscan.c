/*
** Analisador léxico
** Prefixo: psc
** $ Herond Robaina Salles
** 07 Mai 2010
*/

/* ========================================================================== */

#ifndef PRD_SCAN
#define PRD_SCAN

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "pstring.h"
#include "ptypes.h"

/* ========================================================================== */

extern const PtyToken PTY_RESERVED_WORDS[];
extern const PtyToken PTY_DIRECTIVES[];

/* ========================================================================== */

int pscIsHexadecimalDigit (char character) {
    return isdigit(character)                     ||
           (character >= 'a' && character <= 'f') ||
           (character >= 'A' && character <= 'F');
}

int pscIsBinaryDigit (char character) {
    return character == '0' || character == '1';
}

int pscIsOctalDigit (char character) {
    return character >= '0' && character < '8';
}

int pscIsCharacterForId (char character) {
    return isalnum(character) || character == '_';
}

/* ========================================================================== */

PtyToken pscIdOrKeyword
    (FILE* source_code, const PtyToken reserved_words[], unsigned line) {
    if (source_code && reserved_words) {
        char word_return[51]  = "\0";
        char character        = getc(source_code);
        int i                 = 0;
        PtyToken token_return = PTY_NULL_TOKEN;

        while (pscIsCharacterForId(character)) {
            pstAddChar(word_return, i++, character);

            character = getc(source_code);
        }

        fseek(source_code, -1, SEEK_CUR);

        token_return = ptyGetToken(word_return, reserved_words);
        if (!ptyIsNullToken(token_return))
             return ptySetToken(token_return.id, NULL, line);
        else return ptySetToken(PTY_ID, word_return, line);
    } else exit(1); /* trocar por um erro apropriado */
}

/* ========================================================================== */

PtyToken pscStringConstant (FILE* source_code, unsigned line) {
    if (source_code) {
        char* string_return = pstPersist("\0");
        char character      = getc(source_code);
        int flag_aux        = 0;

        for(;;) {
            if      (character == '\\' ) flag_aux = 1;
            else if (character == '/'  ) flag_aux = 2;
            else if (character == '\"' && flag_aux != 2   )
                return ptySetToken(PTY_STRING_VAL, string_return, line);
            else if
                ((character == '\n' || character == EOF ) && flag_aux != 1) {
                fseek(source_code, -1, SEEK_CUR);

                return
                    ptySetToken(PTY_ERROR_STRING_CONSTANT, string_return, line);
            }
            pstCharApend(&string_return, character);

            character = getc(source_code);
        }
    } else exit(1);
}

/* ========================================================================== */

PtyToken pscDirective
    (FILE* source_code, const PtyToken directives[], unsigned line) {
    if (source_code && directives) {
        char directive_return[51] = "@";
        char character            = getc(source_code);
        int i                     = 1;
        PtyToken token_return     = PTY_NULL_TOKEN;

        while(pscIsCharacterForId(character)) {
            pstAddChar(directive_return, i++, character);

            character = getc(source_code);
        }

        fseek(source_code, -1, SEEK_CUR);

        token_return = ptyGetToken(directive_return, directives);
        if (!ptyIsNullToken(token_return))
             return ptySetToken(token_return.id, NULL, line);
        else return ptySetToken(PTY_ERROR_DIRECTIVE, directive_return, line);
    } else exit(1); /* trocar por um erro apropriado */
}

/* ========================================================================== */

PtyToken pscDecimalOrFloatConstant (FILE* source_code, unsigned line) {
    if (source_code) {
        char constant_return[51] = "\0";
        char character           = getc(source_code);
        int i = 0, flag_float    = 0;

        /* pega a parte inteira */
        while (isdigit(character) && i < 50) {
            pstAddChar(constant_return, i++, character);

            character = getc(source_code);
        }

        /* pega o ponto */
        if (character == '.') {
            pstAddChar(constant_return, i++, character);

            /* emite um erro caso não exista a parte fracionária */
            character = getc(source_code);
            if (!isdigit(character)) {
                while (pscIsCharacterForId(character)) {
                    pstAddChar(constant_return, i++, character);

                    character = getc(source_code);
                }
                fseek(source_code, -1, SEEK_CUR);

                return ptySetToken(
                    PTY_ERROR_DECIMAL_CONSTANT, constant_return, line
                );
            }

            /* pega a parte fracionária */
            while (isdigit(character) && i < 50) {
                pstAddChar(constant_return, i++, character);

                character = getc(source_code);
            }

            /* pega o 'e' ou o 'E' */
            if (character == 'e' || character == 'E') {
                pstAddChar(constant_return, i++, character);

                /* paga o sinal '-' ou '+' */
                character = getc(source_code);
                if (character == '-' || character == '+') {
                    pstAddChar(constant_return, i++, character);

                    character = getc(source_code);
                }

                /* emite um erro caso não haja expoente */
                if (!isdigit(character)) {
                    while (pscIsCharacterForId(character)) {
                        pstAddChar(constant_return, i++, character);

                        character = getc(source_code);
                    }
                    fseek(source_code, -1, SEEK_CUR);

                    return ptySetToken(
                        PTY_ERROR_DECIMAL_CONSTANT, constant_return, line
                    );
                }

                /* pega o expoente */
                while (isdigit(character)) {
                    pstAddChar(constant_return, i++, character);

                    character = getc(source_code);
                }
            }

            flag_float = 1;
        }

        /* emite erro caso não haja um delimitador */
        if (pscIsCharacterForId(character)) {
            while (pscIsCharacterForId(character)) {
                pstAddChar(constant_return, i++, character);

                character = getc(source_code);
            }
            fseek(source_code, -1, SEEK_CUR);

            return
                ptySetToken(PTY_ERROR_DECIMAL_CONSTANT, constant_return, line);
        } else {
            fseek(source_code, -1, SEEK_CUR);

            return flag_float ?
                ptySetToken(PTY_FLOAT_VAL, constant_return, line) :
                ptySetToken(PTY_DECIMAL_INT_VAL, constant_return, line);
        }
    } else exit(1); /* trocar por um erro apropriado */
}

PtyToken pscOctalConstant (FILE* source_code, unsigned line) {
    if (source_code) {
        char constant_return[51] = "\0";
        char character           = getc(source_code);
        int flag_error = 0, i    = 0;

        while ((isalnum(character) || character == '_') && i < 50) {
            pstAddChar(constant_return, i++, character);

            if (!flag_error && !pscIsOctalDigit(character)) flag_error = 1;
            character = getc(source_code);
        }

        fseek(source_code, -1, SEEK_CUR);

        if (flag_error)
             return
                ptySetToken(PTY_ERROR_OCTAL_CONSTANT, constant_return, line);
        else return ptySetToken(PTY_OCTAL_INT_VAL, constant_return, line);
    } else exit(1); /* trocar por um erro apropriado */
}

PtyToken pscBinaryConstant (FILE* source_code, unsigned line) {
    if (source_code) {
        char constant_return[51] = "\0";
        char character           = getc(source_code);
        int flag_error = 0, i    = 0;

        while ((isalnum(character) || character == '_') && i < 50) {
            pstAddChar(constant_return, i++, character);

            if (!flag_error && !pscIsBinaryDigit(character)) flag_error = 1;
            character = getc(source_code);
        }

        fseek(source_code, -1, SEEK_CUR);

        if (flag_error)
             return
                ptySetToken(PTY_ERROR_BINARY_CONSTANT, constant_return, line);
        else return ptySetToken(PTY_BIN_INT_VAL, constant_return, line);
    } else exit(1); /* trocar por um erro apropriado */
}

PtyToken pscHexadecimalConstant (FILE* source_code, unsigned line) {
    if (source_code) {
        char constant_return[51] = "\0";
        char character           = getc(source_code);
        int flag_error = 0, i    = 0;

        while ((isalnum(character) || character == '_') && i < 50) {
            pstAddChar(constant_return, i++, character);

            if (!flag_error && !pscIsHexadecimalDigit(character))
                flag_error = 1;
            character = getc(source_code);
        }

        fseek(source_code, -1, SEEK_CUR);

        if (flag_error)
            return ptySetToken(
                PTY_ERROR_HEXADECIMAL_CONSTANT, constant_return, line
            );
        else
            return ptySetToken(PTY_HEXADECIMAL_INT_VAL, constant_return, line);
    } exit(1); /* trocar por um erro apropriado */
}

PtyToken pscNumericConstant (FILE* source_code, unsigned line) {
    if (source_code) {
        switch (getc(source_code)) {
        case '0':
            switch (getc(source_code)) {
            case 'x': case 'X':
                return pscHexadecimalConstant(source_code, line);

            case 'b': case 'B':
                return pscBinaryConstant(source_code, line);

            default :
                fseek(source_code, -1, SEEK_CUR);

                return pscOctalConstant(source_code, line);
            }
        default :
            fseek(source_code, -1, SEEK_CUR);

            return pscDecimalOrFloatConstant(source_code, line);
        }
    } else exit(1); /* trocar por um erro apropriado */

}

/* ========================================================================== */

PtyToken pscIdentifyComment (FILE* source_code, unsigned line) {
    if (source_code) {
        char* comment_return = pstPersist("/*");
        char character       = getc(source_code);
        int flag_end         = 0;

        while(character != EOF) {
           /* printf("< %c - %i >\n", character, flag_end);*/
            if (character == '/' && flag_end) {
                pstCharApend(&comment_return, character);

                return ptySetToken(PTY_COMMENT, comment_return, line);
            }

            flag_end  = character == '*' ? 1 : 0;
            pstCharApend(&comment_return, character);
            character = getc(source_code);
            /*printf("< %c - %i >", character, flag_end); getchar();*/
        }

        return ptySetToken(PTY_ERROR_COMMENT, comment_return, line);
    } else exit(1); /* trocar por um erro apropriado */
}

/* ========================================================================== */

PtyToken pscGetToken (FILE* source_code) {
    static unsigned line = 1;

    if (source_code) {
        char character = getc(source_code);

        switch (character) {
        case EOF: return ptySetToken(PTY_END_OF_FILE, NULL, line);

        case '!':
            switch (getc(source_code)) {
            case '=':
                switch (getc(source_code)) {
                case '=': return ptySetToken(PTY_OP_NQL, NULL, line);
                default :
                    fseek(source_code, -1, SEEK_CUR);

                    return ptySetToken(PTY_OP_DIF, NULL, line);
                }
            default :
                fseek(source_code, -1,SEEK_CUR);

                return ptySetToken(PTY_OP_NOT, NULL, line);
            }

        case '+':
            switch (getc(source_code)) {
            case '+': return ptySetToken(PTY_OP_INC, NULL, line);
            case '=': return ptySetToken(PTY_OP_AAD, NULL, line);
            case ':': return ptySetToken(PTY_OP_ADF, NULL, line);
            default :
                fseek(source_code, -1, SEEK_CUR);

                return ptySetToken(PTY_OP_ADD, NULL, line);
            }

        case '-':
            switch (getc(source_code)) {
            case '-': return ptySetToken(PTY_OP_DEC, NULL, line);
            case '=': return ptySetToken(PTY_OP_AMN, NULL, line);
            default :
                fseek(source_code, -1, SEEK_CUR);

                return ptySetToken(PTY_OP_SUB, NULL, line);
            }

        case '*':
            switch (getc(source_code)) {
            case '=': return ptySetToken(PTY_OP_AML, NULL, line);
            default :
                fseek(source_code, -1, SEEK_CUR);

                return ptySetToken(PTY_OP_MUL, NULL, line);
            }

        case '/':
            switch (getc(source_code)) {
            case '=': return ptySetToken(PTY_OP_ADV, NULL, line);
            case '*': return pscIdentifyComment(source_code, line);
            default :
                fseek(source_code, -1, SEEK_CUR);

                return ptySetToken(PTY_OP_DIV, NULL, line);
            }

        case '%':
            switch (getc(source_code)) {
            case '=': return ptySetToken(PTY_OP_AMD, NULL, line);
            default :
                fseek(source_code, -1, SEEK_CUR);

                return ptySetToken(PTY_OP_MOD, NULL, line);
            }

        case '.':
            switch (getc(source_code)) {
            case '.':
                switch (getc(source_code)) {
                case '.': return ptySetToken(PTY_RETICENCE, NULL, line);
                default :
                    fseek(source_code, -1, SEEK_CUR);

                    return ptySetToken(PTY_OP_TO, NULL, line);
                }
            default :
                fseek(source_code, -1, SEEK_CUR);

                return ptySetToken(PTY_DOT, NULL, line);
            }

        case '<':
            switch (getc(source_code)) {
            case '=': return ptySetToken(PTY_OP_SEQ, NULL, line);
            default :
                fseek(source_code, -1, SEEK_CUR);

                return ptySetToken(PTY_OP_SML, NULL, line);
            }

        case '>':
            switch (getc(source_code)) {
            case '=': return ptySetToken(PTY_OP_BEG, NULL, line);
            default :
                fseek(source_code, -1, SEEK_CUR);

                return ptySetToken(PTY_OP_BIG, NULL, line);
            }

        case '=':
            switch (getc(source_code)) {
            case '=':
                switch (getc(source_code)) {
                case '=': return ptySetToken(PTY_OP_EQL, NULL, line);
                default :
                    fseek(source_code, -1, SEEK_CUR);

                    return ptySetToken(PTY_OP_EQV, NULL, line);
                }
            default :
                fseek(source_code, -1, SEEK_CUR);

                return ptySetToken(PTY_OP_IST, NULL, line);
            }

        case '&': return ptySetToken(PTY_OP_AND, NULL, line);

        case '|': return ptySetToken(PTY_OP_OR, NULL, line);

        case ':':
            switch (getc(source_code)) {
            case ':': return ptySetToken(PTY_ESCOPE_RESOLUTION, NULL, line);
            case '=': return ptySetToken(PTY_OP_ASG, NULL, line);
            default :
                fseek(source_code, -1, SEEK_CUR);

                return ptySetToken(PTY_OP_DEF, NULL, line);
            }

        case '$': return ptySetToken(PTY_POINTER, NULL, line);

        case ';': return ptySetToken(PTY_END_COMMAND, NULL, line);

        case '[': return ptySetToken(PTY_LEFT_BRACKET, NULL, line);

        case ']': return ptySetToken(PTY_RIGHT_BRACKET, NULL, line);

        case '(': return ptySetToken(PTY_LEFT_PARENTHESIS, NULL, line);

        case ')': return ptySetToken(PTY_RIGHT_PARENTHESIS, NULL, line);

        case '{': return ptySetToken(PTY_LEFT_BRACE, NULL, line);

        case '}': return ptySetToken(PTY_RIGHT_BRACE, NULL, line);

        case '@': return pscDirective(source_code, PTY_DIRECTIVES, line);

        case '\"':return pscStringConstant(source_code, line);

        case '\n':
            line++;

            return PTY_NULL_TOKEN;

        default  :
            if (isdigit(character)) {
                fseek(source_code, -1, SEEK_CUR);

                return pscNumericConstant(source_code, line);
            } else if (isalpha(character) || character == '_') {
                fseek(source_code, -1, SEEK_CUR);

                return pscIdOrKeyword(source_code, PTY_RESERVED_WORDS, line);
            } else return PTY_NULL_TOKEN;
        }

    } exit(1); /* trocar por um erro apropriado */
}

PtyToken pscGetTokenIgnoring (int token, FILE* source_code) {
    if (source_code) {
        PtyToken current_token = pscGetToken(source_code);

        while (current_token.id == token && current_token.id != PTY_END_OF_FILE)
            current_token = pscGetToken(source_code);

        return current_token;
    } exit(1); /* trocar por um erro apropriado */
}

/* ========================================================================== */

/*
int main(void) {
    FILE* source_code      = fopen("aux/ex_02.prd", "r");
    PtyToken current_token = pscGetToken(source_code);

    while (!ptyIsLastToken(current_token)) {
        if (!ptyIsNullToken(current_token))
            printf("\nline %3i: (%3i) [%s]", current_token.line, current_token.id, current_token.lexeme ? current_token.lexeme : "\0");

        current_token = pscGetToken(source_code);
    }

    return 0;
}
*/

#endif

