/*
** Buffer de tokens
** Prefixo: ptb
** $ Herond Robaina Salles
** 26 Mai 2010
*/

/* ========================================================================== */

#ifndef PRD_TOKEN_BUFFER_LIB
#define PRD_TOKEN_BUFFER_LIB

#include <stdio.h>

#include "ptoken.h"

/* ========================================================================== */

typedef struct PTBNode_ST {
    PTYToken_ST token;
    struct PTBNode_ST* next;
    struct PTBNode_ST* previous;
} PTBNode_ST;

typedef struct {
    unsigned size;
    PTBNode_ST* first;
    PTBNode_ST* last;
    PTBNode_ST* current;
    FILE* source_code;
} PTBBuffer_ST;

/* ========================================================================== */

PTBBuffer_ST ptbDefBuffer (FILE* source_code);

PTYToken_ST ptbGetToken (PTBBuffer_ST* buffer);

PTYToken_ST ptbGoBack (PTBBuffer_ST* buffer);

PTYToken_ST ptbLookNextToken (PTBBuffer_ST* buffer);

PTYToken_ST ptbLookPreviousToken (PTBBuffer_ST* buffer);

PTYToken_ST ptbLookCurrentToken (PTBBuffer_ST* buffer);

/* ========================================================================== */

#endif

