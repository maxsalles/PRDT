/*
** Buffer de tokens
** Prefixo: ptb
** $ Herond Robaina Salles
** 26 Mai 2010
*/

/* ========================================================================== */

#ifndef PTB_TYPES
#define PTB_TYPES

#include <stdio.h>
#include <stdlib.h>

#include "ptypes.h"
#include "pscan.h"

/* ========================================================================== */

typedef struct PtbNode {
    PtyToken token;
    struct PtbNode* next;
    struct PtbNode* previous;
} PtbNode;

typedef struct {
    unsigned size;
    PtbNode* first;
    PtbNode* last;
    PtbNode* current;
    FILE*    source_code;
} PtbBuffer;

/* ========================================================================== */

PtbBuffer ptbNew (FILE* source_code);

PtyToken ptbGetToken (PtbBuffer *buffer)

PtyToken ptbGoBack (PtbBuffer *buffer);

PtyToken ptbLookNextToken (PtbBuffer *buffer);

PtyToken ptbLookPreviousToken (PtbBuffer *buffer);

PtyToken ptbLookCurrentToken (PtbBuffer *buffer);

/* ========================================================================== */

#endif

