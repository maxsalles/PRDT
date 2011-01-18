/*
**
** Prefix: plt
** $ Herond Robaina Salles
*/

/* ========================================================================== */

#ifndef _PRD_LIST_IMP
#define _PRD_LIST_IMP

#include <stdio.h>
#include <stdlib.h>

#include "plist.h"
#include "plist_imp.h"

/* ========================================================================== */

int plt_current_error = PLT_NO_ERROR;

/* ========================================================================== */

struct PLTNode* pltGetNode (PLTList list, unsigned position) {
    struct PLTNode* node_p = NULL;

    if (list && (position < list->size)) {
        int i;

        for (
            i = 0, node_p = list->first;
            (i < position) || (node_p == NULL);
            i ++, node_p = node_p->next
        );
    }

    return node_p;
}

/* ========================================================================== */

PLTList pltNew (void) {
    PLTList list_return = (PLTList) malloc(sizeof(struct PLTList_ST));

    if (list_return) {
        list_return->size = 0;
        list_return->first = NULL;
        list_return->last = NULL;
    } else plt_current_error = PLT_NOT_ENOUGH_SPACE;

    return list_return;
}

PLTList pltCopy (PLTList list) {
    if (list) {
        int i;
        PLTList list_return = pltNew();

        if (list_return) {
            for (i = 0; i < list->size; i ++)
                pltAppend(list_return, pltLookElement(list, i));

            return list_return;
        }

        return NULL;
    } plt_current_error = PLT_INVALID_ARGUMENT;

    return NULL;
}

void pltClear (PLTList list) {
    if (list)
        while (list->size) pltGetFirstElement(list);
    else plt_current_error = PLT_INVALID_ARGUMENT;
}


void pltDestroy (PLTList* list_p) {
    if (list_p) {
        pltClear(*list_p);
        free(*list_p);
        *list_p = NULL;
    } else plt_current_error = PLT_INVALID_ARGUMENT;
}

void pltAppend (PLTList list, void* element_p) {
    if (list && element_p) {
        struct PLTNode* node_p = (struct PLTNode*) malloc(
            sizeof(struct PLTNode)
        );

        if (node_p) {
            node_p->next = NULL;
            node_p->previous = list->last;
            node_p->element_p = element_p;

            if (list->last) list->last->next = node_p;
            list->last = node_p;
            if (!list->size) list->first = node_p;
            list->size ++;

        } else plt_current_error = PLT_NOT_ENOUGH_SPACE;
    } else plt_current_error = PLT_INVALID_ARGUMENT;
}

void pltInject (PLTList list, void *element_p) {
    if (list && element_p) {
        struct PLTNode* node_p = (struct PLTNode*) malloc(
            sizeof(struct PLTNode*)
        );

        if (node_p) {
            node_p->next = list->first;
            node_p->previous = NULL;
            node_p->element_p = element_p;

            if (list->first) list->first->previous = node_p;
            list->first = node_p;
            list->size ++;
        } else plt_current_error = PLT_NOT_ENOUGH_SPACE;
    } else plt_current_error = PLT_INVALID_ARGUMENT;
}

void pltInsert (PLTList list, unsigned position, void* element_p) {
    struct PLTNode* node_p = NULL;

    if (list && element_p && (position < list->size)) {
        if (position == list->size - 1) pltAppend(list, element_p);
        else if (position == 0) pltInject(list, element_p);
        else {
            node_p = (struct PLTNode*) malloc(sizeof(struct PLTNode*));
            struct PLTNode* current_node_p = pltGetNode(list, position);

            if (node_p) {
                node_p->next = current_node_p;
                node_p->previous = current_node_p->previous;
                node_p->element_p = element_p;

                current_node_p->previous->next = node_p;
                current_node_p->previous = node_p;

                list->size ++;
            } else plt_current_error = PLT_NOT_ENOUGH_SPACE;
        }
    } else plt_current_error = PLT_INVALID_ARGUMENT;
}

void pltSetElement (PLTList list, unsigned position, void* element_p) {
    struct PLTNode* node_p = pltGetNode(list, position);

    if (node_p) node_p->element_p = element_p;
}

void* pltLookElement (const PLTList list, unsigned position) {
    if (list && (position < list->size))
        return pltGetNode(list, position)->element_p;
    else plt_current_error = PLT_INVALID_ARGUMENT;

    return NULL;
}

void* pltLookLastElement (const PLTList list) {
    if (list && list->size) return list->last->element_p;
    plt_current_error = PLT_INVALID_ARGUMENT;

    return NULL;
}

void* pltLookFirstElement (const PLTList list) {
    if (list && list->size) return list->first->element_p;
    plt_current_error = PLT_INVALID_ARGUMENT;

    return NULL;
}

void* pltGetElement (PLTList list, unsigned position) {
    if (list && list->size) {
        if (! position) return pltGetFirstElement(list);
        else if (position == list->size - 1) return pltGetLastElement(list);
        else {
            struct PLTNode* node = pltGetNode(list, position);
            void* element_p = node->element_p;

            node->previous->next = node->next;
            node->next->previous = node->previous;
            list->size --;
            free(node);

            return element_p;
        }
    }

    plt_current_error = PLT_INVALID_ARGUMENT;

    return NULL;
}

void* pltGetLastElement (PLTList list) {
    if (list && list->size) {
        struct PLTNode* last_node = list->last;
        void* element_p = list->last->element_p;

        if (list->last->previous) list->last->previous->next = NULL;
        else list->first = NULL;
        list->last = list->last->previous;
        list->size --;
        free(last_node);

        return element_p;
    }

    plt_current_error = PLT_INVALID_ARGUMENT;

    return NULL;
}

void* pltGetFirstElement (PLTList list) {
    if (list && list->size) {
        struct PLTNode* first_node = list->first;
        void* element_p = list->first->element_p;

        if (list->first->next) list->first->next->previous = NULL;
        else list->last = NULL;
        list->first = list->first->next;
        list->size --;
        free(first_node);

        return element_p;
    }

    plt_current_error = PLT_INVALID_ARGUMENT;

    return NULL;
}

void pltReverse (PLTList list) {
    int i;
    void* element_p = NULL;

    for (i = 0; i < list->size / 2; i ++) {
        element_p = pltLookElement(list, i);
        pltSetElement(list, i, pltLookElement(list, list->size - 1 - i));
        pltSetElement(list, list->size - 1 - i, element_p);
    }
}

unsigned pltLength (const PLTList list) {
    if (list) return list->size;
    else plt_current_error = PLT_INVALID_ARGUMENT;

    return 0;
}

PLTList pltSearch (
    const PLTList list,
    int (*comparator) (const void*, void*),
    void* element_of_comparison_p
) {
    if (list && element_of_comparison_p) {
        int i;
        struct PLTNode* node_p = NULL;
        PLTList list_return = pltNew();

        comparator = comparator ? comparator : PLT_DEFAULT_COMPARATOR;

        if (list_return) {
            for (
                i = 0, node_p = list->first;
                i < list->size;
                i ++, node_p = node_p->next
            ) if (comparator(node_p->element_p, element_of_comparison_p))
                pltAppend(list_return, node_p->element_p);

            return list_return;
        }
    } else plt_current_error = PLT_INVALID_ARGUMENT;

    return NULL;
}

void* pltSearchElement (
    const PLTList list,
    int (*comparator) (const void*, void*),
    void* element_of_comparison_p
) {
    if (list && element_of_comparison_p) {
        int i;
        struct PLTNode* node_p = NULL;

        comparator = comparator ? comparator : PLT_DEFAULT_COMPARATOR;

        for (
            i = 0, node_p = list->first;
            i < list->size;
            i ++, node_p = node_p->next
        ) if (comparator(node_p->element_p, element_of_comparison_p))
            return node_p->element_p;

    } else plt_current_error = PLT_INVALID_ARGUMENT;

    return NULL;
}

int pltGetError (void) {
    int error_return = plt_current_error;

    plt_current_error = PLT_NO_ERROR;

    return error_return;
}

void pltPrint (const PLTList list) {
    if (list) {
        int i = 0;
        struct PLTNode* node_p = NULL;

        for (node_p = list->first; i < list->size; node_p = node_p->next, i ++)
            printf("%i:%p ", i, node_p->element_p);

        puts("");
    }
}

/* ========================================================================== */

int pltDefaultComparator (
    const void* element_p,
    void* element_of_comparison_p
) {
    return element_p == element_of_comparison_p;
}

/* ========================================================================== */

#endif

