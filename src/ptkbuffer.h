/*
** Buffer de tokens
** Prefix: ptb
** $ Herond Robaina Salles
*/

/* ========================================================================== */

#ifndef PRD_TOKEN_BUFFER_LIB
#define PRD_TOKEN_BUFFER_LIB

#include <stdio.h>

#include "ptoken.h"

/* ========================================================================== */

typedef struct PTBNode_ST {
    PTKToken_ST token;
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

PTKToken_ST ptbGetToken (PTBBuffer_ST* buffer);

PTKToken_ST ptbGoBack (PTBBuffer_ST* buffer);

PTKToken_ST ptbLookNextToken (PTBBuffer_ST* buffer);

PTKToken_ST ptbLookPreviousToken (PTBBuffer_ST* buffer);

PTKToken_ST ptbLookCurrentToken (PTBBuffer_ST* buffer);

/* ========================================================================== */

#endif

