/*
** Analisador léxico
** Prefixo: psc
** $ Herond Robaina Salles
** 07 Mai 2010
*/

/* ========================================================================== */

#ifndef _PRD_SCAN_IMP
#define _PRD_SCAN_IMP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "pstring.h"
#include "ptoken.h"

/* ========================================================================== */

static int isHexadecimalDigit (char character) {
    return isdigit(character)                     ||
           (character >= 'a' && character <= 'f') ||
           (character >= 'A' && character <= 'F');
}

static int isBinaryDigit (char character) {
    return character == '0' || character == '1';
}

static int isOctalDigit (char character) {
    return character >= '0' && character < '8';
}

static int isCharacterForId (char character) {
    return isalnum(character) || character == '_';
}

/* ========================================================================== */

static PTYToken_ST isIdentifierOrKeyword (
	FILE* source_code,
	const PTYToken_ST reserved_words[],
	unsigned line
) {
    if (source_code && reserved_words) {
        char word_return[51] = "\0";
        char character = getc(source_code);
        int i = 0;
        PTYToken_ST token_return = PTY_NULL_TOKEN;

        while (isCharacterForId(character)) {
            pstAddChar(word_return, i++, character);

            character = getc(source_code);
        }

        fseek(source_code, -1, SEEK_CUR);

        token_return = ptyGetToken(word_return, reserved_words);
        if (!ptyIsNullToken(token_return))
             return ptyDefToken(token_return.id, NULL, line);
        else return ptyDefToken(PTY_ID, word_return, line);
    } else exit(1); /* trocar por um erro apropriado */
}

/* ========================================================================== */

static PTYToken_ST isStringConstant (FILE* source_code, unsigned line) {
    if (source_code) {
        char* string_return = pstCopy("\0");
        char character = getc(source_code);
        int flag_aux = 0;

        for(;;) {
            if      (character == '\\' ) flag_aux = 1;
            else if (character == '/'  ) flag_aux = 2;
            else if (character == '\"' && flag_aux != 2   )
                return ptyDefToken(PTY_STRING_VAL, string_return, line);
            else if
                ((character == '\n' || character == EOF ) && flag_aux != 1) {
                fseek(source_code, -1, SEEK_CUR);

                return
                    ptyDefToken(PTY_ERROR_STRING_CONSTANT, string_return, line);
            }
            pstCharApend(&string_return, character);

            character = getc(source_code);
        }
    } else exit(1);
}

/* ========================================================================== */

static PTYToken_ST isDecimalOrFloatConstant (
	FILE* source_code,
	unsigned line
) {
    if (source_code) {
        char constant_return[51] = "\0";
        char character = getc(source_code);
        int i = 0, flag_float = 0;

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
                while (isCharacterForId(character)) {
                    pstAddChar(constant_return, i++, character);

                    character = getc(source_code);
                }
                fseek(source_code, -1, SEEK_CUR);

                return ptyDefToken(
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
                    while (isCharacterForId(character)) {
                        pstAddChar(constant_return, i++, character);

                        character = getc(source_code);
                    }
                    fseek(source_code, -1, SEEK_CUR);

                    return ptyDefToken(
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
        if (isCharacterForId(character)) {
            while (isCharacterForId(character)) {
                pstAddChar(constant_return, i++, character);

                character = getc(source_code);
            }
            fseek(source_code, -1, SEEK_CUR);

            return
                ptyDefToken(PTY_ERROR_DECIMAL_CONSTANT, constant_return, line);
        } else {
            fseek(source_code, -1, SEEK_CUR);

            return flag_float ?
                ptyDefToken(PTY_FLOAT_VAL, constant_return, line) :
                ptyDefToken(PTY_DECIMAL_INT_VAL, constant_return, line);
        }
    } else exit(1); /* trocar por um erro apropriado */
}

static PTYToken_ST isOctalConstant (FILE* source_code, unsigned line) {
    if (source_code) {
        char constant_return[51] = "\0";
        char character = getc(source_code);
        int flag_error = 0, i = 0;

        while ((isalnum(character) || character == '_') && i < 50) {
            pstAddChar(constant_return, i++, character);

            if (!flag_error && !isOctalDigit(character)) flag_error = 1;
            character = getc(source_code);
        }

        fseek(source_code, -1, SEEK_CUR);

        if (flag_error)
             return
                ptyDefToken(PTY_ERROR_OCTAL_CONSTANT, constant_return, line);
        else return ptyDefToken(PTY_OCTAL_INT_VAL, constant_return, line);
    } else exit(1); /* trocar por um erro apropriado */
}

static PTYToken_ST isBinaryConstant (FILE* source_code, unsigned line) {
    if (source_code) {
        char constant_return[51] = "\0";
        char character = getc(source_code);
        int flag_error = 0, i = 0;

        while ((isalnum(character) || character == '_') && i < 50) {
            pstAddChar(constant_return, i++, character);

            if (!flag_error && !isBinaryDigit(character)) flag_error = 1;
            character = getc(source_code);
        }

        fseek(source_code, -1, SEEK_CUR);

        if (flag_error)
             return
                ptyDefToken(PTY_ERROR_BINARY_CONSTANT, constant_return, line);
        else return ptyDefToken(PTY_BIN_INT_VAL, constant_return, line);
    } else exit(1); /* trocar por um erro apropriado */
}

static PTYToken_ST isHexadecimalConstant (FILE* source_code, unsigned line) {
    if (source_code) {
        char constant_return[51] = "\0";
        char character = getc(source_code);
        int flag_error = 0, i = 0;

        while ((isalnum(character) || character == '_') && i < 50) {
            pstAddChar(constant_return, i++, character);

            if (!flag_error && !isHexadecimalDigit(character))
                flag_error = 1;
            character = getc(source_code);
        }

        fseek(source_code, -1, SEEK_CUR);

        if (flag_error)
            return ptyDefToken(
                PTY_ERROR_HEXADECIMAL_CONSTANT, constant_return, line
            );
        else
            return ptyDefToken(PTY_HEXADECIMAL_INT_VAL, constant_return, line);
    } exit(1); /* trocar por um erro apropriado */
}

static PTYToken_ST isNumericConstant (FILE* source_code, unsigned line) {
    if (source_code) {
        switch (getc(source_code)) {
        case '0':
            switch (getc(source_code)) {
            case 'x': case 'X':
                return isHexadecimalConstant(source_code, line);

            case 'b': case 'B':
                return isBinaryConstant(source_code, line);

            default :
                fseek(source_code, -1, SEEK_CUR);

                return isOctalConstant(source_code, line);
            }
        default :
            fseek(source_code, -1, SEEK_CUR);

            return isDecimalOrFloatConstant(source_code, line);
        }
    } else exit(1); /* trocar por um erro apropriado */

}

/* ========================================================================== */

PTYToken_ST pscIdentifyComment (FILE* source_code, unsigned line) {
    if (source_code) {
        char* comment_return = pstCopy("/*");
        char character = getc(source_code);
        int flag_end = 0;

        while(character != EOF) {
            if (character == '/' && flag_end) {
                pstCharApend(&comment_return, character);

                return ptyDefToken(PTY_COMMENT, comment_return, line);
            }

            flag_end  = character == '*';
            pstCharApend(&comment_return, character);
            character = getc(source_code);
        }

        return ptyDefToken(PTY_ERROR_COMMENT, comment_return, line);
    } else exit(1); /* trocar por um erro apropriado */
}

/* ========================================================================== */

PTYToken_ST pscGetToken (FILE* source_code) {
    static unsigned line = 1;

    if (source_code) {
        char character = getc(source_code);

        switch (character) {
        case EOF: return ptyDefToken(PTY_END_OF_FILE, NULL, line);

        case '!':
            switch (getc(source_code)) {
            case '=':
                switch (getc(source_code)) {
                case '=': return ptyDefToken(PTY_OP_NQL, NULL, line);
                default :
                    fseek(source_code, -1, SEEK_CUR);

                    return ptyDefToken(PTY_OP_DIF, NULL, line);
                }
            default :
                fseek(source_code, -1,SEEK_CUR);

                return ptyDefToken(PTY_OP_NOT, NULL, line);
            }

        case '+':
            switch (getc(source_code)) {
            case '+': return ptyDefToken(PTY_OP_INC, NULL, line);
            case '=': return ptyDefToken(PTY_OP_AAD, NULL, line);
            case ':': return ptyDefToken(PTY_OP_ADF, NULL, line);
            default :
                fseek(source_code, -1, SEEK_CUR);

                return ptyDefToken(PTY_OP_ADD, NULL, line);
            }

        case '-':
            switch (getc(source_code)) {
            case '-': return ptyDefToken(PTY_OP_DEC, NULL, line);
            case '=': return ptyDefToken(PTY_OP_AMN, NULL, line);
            default :
                fseek(source_code, -1, SEEK_CUR);

                return ptyDefToken(PTY_OP_SUB, NULL, line);
            }

        case '*':
            switch (getc(source_code)) {
            case '=': return ptyDefToken(PTY_OP_AML, NULL, line);
            default :
                fseek(source_code, -1, SEEK_CUR);

                return ptyDefToken(PTY_OP_MUL, NULL, line);
            }

        case '/':
            switch (getc(source_code)) {
            case '=': return ptyDefToken(PTY_OP_ADV, NULL, line);
            case '*': return pscIdentifyComment(source_code, line);
            default :
                fseek(source_code, -1, SEEK_CUR);

                return ptyDefToken(PTY_OP_DIV, NULL, line);
            }

        case '%':
            switch (getc(source_code)) {
            case '=': return ptyDefToken(PTY_OP_AMD, NULL, line);
            default :
                fseek(source_code, -1, SEEK_CUR);

                return ptyDefToken(PTY_OP_MOD, NULL, line);
            }

        case '.':
            switch (getc(source_code)) {
            case '.':
                switch (getc(source_code)) {
                case '.': return ptyDefToken(PTY_RETICENCE, NULL, line);
                default :
                    fseek(source_code, -1, SEEK_CUR);

                    return ptyDefToken(PTY_OP_TO, NULL, line);
                }
            default :
                fseek(source_code, -1, SEEK_CUR);

                return ptyDefToken(PTY_DOT, NULL, line);
            }

        case '<':
            switch (getc(source_code)) {
            case '=': return ptyDefToken(PTY_OP_SEQ, NULL, line);
            default :
                fseek(source_code, -1, SEEK_CUR);

                return ptyDefToken(PTY_OP_SML, NULL, line);
            }

        case '>':
            switch (getc(source_code)) {
            case '=': return ptyDefToken(PTY_OP_BEG, NULL, line);
            default :
                fseek(source_code, -1, SEEK_CUR);

                return ptyDefToken(PTY_OP_BIG, NULL, line);
            }

        case '=':
            switch (getc(source_code)) {
            case '=':
                switch (getc(source_code)) {
                case '=': return ptyDefToken(PTY_OP_EQL, NULL, line);
                default :
                    fseek(source_code, -1, SEEK_CUR);

                    return ptyDefToken(PTY_OP_EQV, NULL, line);
                }
            default :
                fseek(source_code, -1, SEEK_CUR);

                return ptyDefToken(PTY_OP_IST, NULL, line);
            }

        case '&': return ptyDefToken(PTY_OP_AND, NULL, line);

        case '|': return ptyDefToken(PTY_OP_OR, NULL, line);

        case ':':
            switch (getc(source_code)) {
            case ':': return ptyDefToken(PTY_ESCOPE_RESOLUTION, NULL, line);
            case '=': return ptyDefToken(PTY_OP_ASG, NULL, line);
            default :
                fseek(source_code, -1, SEEK_CUR);

                return ptyDefToken(PTY_OP_DEF, NULL, line);
            }

        case '$': return ptyDefToken(PTY_POINTER, NULL, line);

        case ';': return ptyDefToken(PTY_END_COMMAND, NULL, line);

        case '[': return ptyDefToken(PTY_LEFT_BRACKET, NULL, line);

        case ']': return ptyDefToken(PTY_RIGHT_BRACKET, NULL, line);

        case '(': return ptyDefToken(PTY_LEFT_PARENTHESIS, NULL, line);

        case ')': return ptyDefToken(PTY_RIGHT_PARENTHESIS, NULL, line);

        case '{': return ptyDefToken(PTY_LEFT_BRACE, NULL, line);

        case '}': return ptyDefToken(PTY_RIGHT_BRACE, NULL, line);

        case '\"':return isStringConstant(source_code, line);

        case '\n':
            line++;

            return PTY_NULL_TOKEN;

        default  :
            if (isdigit(character)) {
                fseek(source_code, -1, SEEK_CUR);

                return isNumericConstant(source_code, line);
            } else if (isalpha(character) || character == '_') {
                fseek(source_code, -1, SEEK_CUR);

                return isIdentifierOrKeyword(
					source_code, PTY_RESERVED_WORDS, line
				);
            } else return PTY_NULL_TOKEN;
        }

    } exit(1); /* trocar por um erro apropriado */
}

PTYToken_ST pscGetTokenIgnoring (int token, FILE* source_code) {
    if (source_code) {
        PTYToken_ST current_token = pscGetToken(source_code);

        while (current_token.id == token && current_token.id != PTY_END_OF_FILE)
            current_token = pscGetToken(source_code);

        return current_token;
    } exit(1); /* trocar por um erro apropriado */
}

/* ========================================================================== */

#endif

