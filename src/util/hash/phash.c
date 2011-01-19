/*
**
** Prefix: phs
** $ Herond Robaina Salles
*/

/* ========================================================================== */

#ifndef _PRD_HASH_IMP
#define _PRD_HASH_IMP

#include <stdio.h>
#include <stdlib.h>

#include "../list/plist.h"
#include "phash.h"
#include "phash_imp.h"

/* ========================================================================== */

int phs_current_error = PHS_NO_ERROR;

/* ========================================================================== */

static int keysSeach (const void* element_p, void* element_of_comparison_p) {
    return ((struct PHSNode_ST*) element_p)->key == element_of_comparison_p;
}

static struct PHSNode_ST* newNode (const void* key) {
    struct PHSNode_ST* node_return = (struct PHSNode_ST*) malloc (
        sizeof(struct PHSNode_ST)
    );

    if (node_return) {
        PLTList elements = pltNew();

        if (elements) {
            node_return->key = key;
            node_return->elements = elements;
        } else {
            free(node_return);
            node_return = NULL;
        }
    } else phs_current_error = PHS_NOT_ENOUGH_SPACE;

    return node_return;
}

/* ========================================================================== */

PHSHash phsNew () {
    PHSHash rash_return = (struct PHSHash_ST*) malloc(
        sizeof(struct PHSHash_ST)
    );

    if (rash_return) {
        PLTList keys = pltNew();

        if (keys) {
            rash_return->length = 0;
            rash_return->keys = keys;
        } else {
            free(rash_return);
            rash_return = NULL;
        }
    } else phs_current_error = PHS_NOT_ENOUGH_SPACE;

    return rash_return;
}

void phsAdd (PHSHash hash, const void* key, const void* element_p) {
    if (hash && key && element_p) {
        struct PHSNode_ST* node = pltSearchElement(
            hash->keys, keysSeach, (void*) key
        );

        if (node) {
            pltAppend(node->elements, (void*) element_p);
            hash->length ++;
        } else {
            struct PHSNode_ST* new_node = newNode(key);

            if (new_node) {
                pltAppend(new_node->elements, (void*) element_p);
                pltAppend(hash->keys, new_node);
                hash->length ++;
            }
        }
    } else phs_current_error = PHS_INVALID_ARGUMENT;
}

void phsPrint (const PHSHash hash) {
    int i;

    if (hash) {
        for (i = 0; i < hash->length; i ++) {
            printf("%i:%p => ", i,
                ((struct PHSNode_ST*) pltLookElement(hash->keys, i))->key
            );
            pltPrint(
                ((struct PHSNode_ST*) pltLookElement(hash->keys, i))->elements
            );
        }
    }
}

/* ========================================================================== */

#endif

