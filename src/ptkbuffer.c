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

PtbNode* ptbAllocNode (PtyToken token, PtbNode* previous) {
    PtbNode* node_p_return  = (PtbNode*) malloc(sizeof(PtbNode));

    if (node_p_return) {
        node_p_return->token    = ptyCopyToken(token);
        node_p_return->next     = NULL;
        node_p_return->previous = previous;

        return node_p_return;
    } exit(1); /* trocar por um erro apropriado */
}

PtbBuffer ptbInsertNode (PtbBuffer* buffer) {
    if (buffer) {
        PtbNode* new_node = ptbAllocNode(
            pscGetTokenIgnoring(PTY_NONE, buffer->source_code), buffer->last
        );

        if (!buffer->size) buffer->first = new_node;
        if (buffer->last)  buffer->last->next = new_node;
        buffer->last = new_node;
        buffer->current = new_node;
        buffer->size++;
    } else exit(1); /* trocar por um erro apropriado */

    return *buffer;
}

PtbBuffer ptbNew (FILE* source_code) {
    if (source_code) {
        PtbBuffer buffer_return = { 0, NULL, NULL, NULL, source_code };

        return ptbInsertNode(&buffer_return);
    } exit(1); /* trocar por um erro apropriado */
}

PtyToken ptbGetToken (PtbBuffer *buffer) {
    if (buffer) {
        PtyToken token_return = buffer->current->token;

        if (!buffer->current->next) ptbInsertNode(buffer);
        else buffer->current = buffer->current->next;

        return token_return;
    } exit(1); /* trocar por um erro apropriado */
}

PtyToken ptbGoBack (PtbBuffer *buffer) {
    if (buffer) {
        PtyToken token_return = buffer->current->token;

        if (buffer->current->previous)
            buffer->current = buffer->current->previous;

        return token_return;
    } exit(1); /* trocar por um erro apropriado */
}

PtyToken ptbLookNextToken (PtbBuffer *buffer) {
    if (buffer) {
        if (buffer->current->next) return buffer->current->next->token;
        else {
            PtbNode* new_node = ptbAllocNode(
                pscGetTokenIgnoring(PTY_NONE, buffer->source_code), buffer->last
            );

            if (new_node) {
                buffer->last->next = new_node;
                buffer->last = new_node;
            } else exit(1); /* trocar por um erro apropriado */

            return new_node->token;
        }
    } exit(1); /* trocar por um erro apropriado */
}

PtyToken ptbLookPreviousToken (PtbBuffer *buffer) {
    if (buffer) {
        if (buffer->current->previous) return buffer->current->previous->token;
        else return buffer->current->token;
    } exit(1); /* trocar por um erro apropriado */
}

PtyToken ptbLookCurrentToken (PtbBuffer *buffer) {
    if (buffer) {
        return buffer->current->token;
    } exit(1); /* trocar por um erro apropriado */
}

/* ========================================================================== */

#endif

