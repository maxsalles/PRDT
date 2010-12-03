/*
** Buffer de tokens
** Prefix: ptb
** $ Herond Robaina Salles
*/

/* ========================================================================== */

#ifndef PRD_TOKEN_BUFFER_IMP
#define PRD_TOKEN_BUFFER_IMP

#include <stdio.h>
#include <stdlib.h>

#include "ptkbuffer.h"
#include "ptoken.h"
#include "pscan.h"

/* ========================================================================== */

static PTBNode_ST* allocNode (PTKToken_ST token, PTBNode_ST* previous) {
    PTBNode_ST* node_p_return  = (PTBNode_ST*) malloc(sizeof(PTBNode_ST));

    if (node_p_return) {
        node_p_return->token = ptkCopyToken(token);
        node_p_return->next = NULL;
        node_p_return->previous = previous;

        return node_p_return;
    } exit(1); /* trocar por um erro apropriado */
}

static PTBBuffer_ST insertNode (PTBBuffer_ST* buffer) {
    if (buffer) {
        PTBNode_ST* new_node = allocNode(
            pscGetTokenIgnoring(PTK_NONE, buffer->source_code), buffer->last
        );

        if (!buffer->size) buffer->first = new_node;
        if (buffer->last) buffer->last->next = new_node;
        buffer->last = new_node;
        buffer->current = new_node;
        buffer->size ++;
    } else exit(1); /* trocar por um erro apropriado */

    return *buffer;
}

/* ========================================================================== */

PTBBuffer_ST ptbDef (FILE* source_code) {
    if (source_code) {
        PTBBuffer_ST buffer_return = { 0, NULL, NULL, NULL, source_code };

        return insertNode(&buffer_return);
    } exit(1); /* trocar por um erro apropriado */
}

PTKToken_ST ptbGetToken (PTBBuffer_ST* buffer) {
    if (buffer) {
        PTKToken_ST token_return = buffer->current->token;

        if (!buffer->current->next) insertNode(buffer);
        else buffer->current = buffer->current->next;

        return token_return;
    } exit(1); /* trocar por um erro apropriado */
}

PTKToken_ST ptbGoBack (PTBBuffer_ST* buffer) {
    if (buffer) {
        PTKToken_ST token_return = buffer->current->token;

        if (buffer->current->previous)
            buffer->current = buffer->current->previous;

        return token_return;
    } exit(1); /* trocar por um erro apropriado */
}

PTKToken_ST ptbLookNextToken (PTBBuffer_ST *buffer) {
    if (buffer) {
        if (buffer->current->next) return buffer->current->next->token;
        else {
            PTBNode_ST* new_node = allocNode(
                pscGetTokenIgnoring(PTK_NONE, buffer->source_code), buffer->last
            );

            if (new_node) {
                buffer->last->next = new_node;
                buffer->last = new_node;
            } else exit(1); /* trocar por um erro apropriado */

            return new_node->token;
        }
    } exit(1); /* trocar por um erro apropriado */
}

PTKToken_ST ptbLookPreviousToken (PTBBuffer_ST *buffer) {
    if (buffer) {
        if (buffer->current->previous) return buffer->current->previous->token;
        else return buffer->current->token;
    } exit(1); /* trocar por um erro apropriado */
}

PTKToken_ST ptbLookCurrentToken (PTBBuffer_ST *buffer) {
    if (buffer) {
        return buffer->current->token;
    } exit(1); /* trocar por um erro apropriado */
}

/* ========================================================================== */

#endif

