/*
** Define os tipos para o restante do compilador
** Prefixo: pty
** $ Herond Robaina Salles
** 24 Mai 2010
*/

/* ========================================================================== */

#ifndef _PRD_TYPES_IMP
#define _PRD_TYPES_IMP

#include <stdlib.h>
#include <string.h>

#include "ptoken.h"
#include "pstring.h"

/* ========================================================================== */

PTYToken_ST ptyDefToken (int id, const char* lexeme, unsigned line) {
    PTYToken_ST token_return = { id, pstCopy(lexeme), line };

    return token_return;
}

PTYToken_ST ptyCopyToken (PTYToken_ST token) {
    PTYToken_ST token_return = { token.id, token.lexeme, token.line };

    return token_return;
}

int ptyIsNullToken (PTYToken_ST token) {
    return token.id == PTY_NONE;
}

int ptyIsLastToken (PTYToken_ST token) {
    return token.id == PTY_END_OF_FILE;
}

PTYToken_ST ptyGetToken (const char* lexeme, const PTYToken_ST token_list[]) {
    if (lexeme) {
        int i = 0;
        PTYToken_ST current_token = token_list[0];

        while (current_token.id != PTY_NONE) {
            if (!strcmp(lexeme, current_token.lexeme))
                return current_token;

            current_token = token_list[++ i];
        }

        return PTY_NULL_TOKEN;
    } exit(1); /* trocar por um erro apropriado */
}

const PTYToken_ST* ptyReservedWords (void) {
	static const PTYToken_ST RESERVED_WORDS[] = {
		{ PTY_USES,      "@uses",       0 },
		{ PTY_LINKED,    "@linked",     0 },
		{ PTY_ONLY,      "@only",       0 },
		{ PTY_EXCEPT,    "@except",     0 },
		{ PTY_OPERATOR,  "@operator",   0 },
		{ PTY_CONST,     "@const",      0 },
		{ PTY_MAIN,      "@main",       0 },
		{ PTY_STATIC,    "@static",     0 },
		{ PTY_SHARED,    "@shared",     0 },
		{ PTY_INTERNAL,  "@internal",   0 },
		{ PTY_FIX,		 "@fix",		0 },

		{ PTY_NONE,      NULL,          0 }
	};

	return RESERVED_WORDS;
}

/* ========================================================================== */

#endif

