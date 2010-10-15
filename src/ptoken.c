/*
** Define os tipos para o restante do compilador
** Prefixo: ptk
** $ Herond Robaina Salles
** 24 Mai 2010
*/

/* ========================================================================== */

#ifndef _PRD_TOKEN_IMP
#define _PRD_TOKEN_IMP

#include <stdlib.h>
#include <string.h>

#include "ptoken.h"
#include "pstring.h"

/* ========================================================================== */

PTKToken_ST ptkDefToken (int id, const char* lexeme, unsigned line) {
    PTKToken_ST token_return = { id, pstCopy(lexeme), line };

    return token_return;
}

PTKToken_ST ptkCopyToken (PTKToken_ST token) {
    PTKToken_ST token_return = { token.id, token.lexeme, token.line };

    return token_return;
}

int ptkIsNullToken (PTKToken_ST token) {
    return token.id == PTK_NONE;
}

int ptkIsLastToken (PTKToken_ST token) {
    return token.id == PTK_END_OF_FILE;
}

PTKToken_ST ptkGetToken (const char* lexeme, const PTKToken_ST token_list[]) {
    if (lexeme) {
        int i = 0;
        PTKToken_ST current_token = token_list[0];

        while (current_token.id != PTK_NONE) {
            if (!strcmp(lexeme, current_token.lexeme))
                return current_token;

            current_token = token_list[++ i];
        }

        return PTK_NULL_TOKEN;
    } exit(1); /* trocar por um erro apropriado */
}

const PTKToken_ST* ptkReservedWords (void) {
	static const PTKToken_ST RESERVED_WORDS[] = {
		{ PTK_USES,      "@uses",       0 },
		{ PTK_LINKED,    "@linked",     0 },
		{ PTK_ONLY,      "@only",       0 },
		{ PTK_EXCEPT,    "@except",     0 },
		{ PTK_OPERATOR,  "@operator",   0 },
		{ PTK_CONST,     "@const",      0 },
		{ PTK_MAIN,      "@main",       0 },
		{ PTK_STATIC,    "@static",     0 },
		{ PTK_SHARED,    "@shared",     0 },
		{ PTK_INTERNAL,  "@internal",   0 },
        { PTK_SELF,		 "@self",		0 },

		{ PTK_NONE,      NULL,          0 }
	};

	return RESERVED_WORDS;
}

/* ========================================================================== */

#endif

