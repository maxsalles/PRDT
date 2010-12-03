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

#include "punit.h"
#include "plist.h"

/* ========================================================================== */

struct Node {
    void* element_p;
    struct Node* next;
    struct Node* previous;
};

struct PLTList_ST {
    unsigned size;
    struct Node* first;
    struct Node* last;
};

/* ========================================================================== */

static int current_error = PLT_NO_ERROR;

/* ========================================================================== */

static struct Node* getNode (PLTList list, unsigned position) {
    struct Node* node_p = NULL;

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
    } else current_error = PLT_NOT_ENOUGH_SPACE;

    return list_return;
}

void pltClear (PLTList list) {
    if (list)
        while (list->size) pltGetFirstElement(list);
    else current_error = PLT_INVALID_ARGUMENT;
}


void pltDestroy (PLTList* list_p) {
    if (list_p) {
        pltClear(*list_p);
        *list_p = NULL;
    } else current_error = PLT_INVALID_ARGUMENT;
}

void pltAppend (PLTList list, void* element_p) {
    if (list && element_p) {
        struct Node* node_p = (struct Node*) malloc(sizeof(struct Node));

        if (node_p) {
            node_p->next = NULL;
            node_p->previous = list->last;
            node_p->element_p = element_p;

            if (list->last) list->last->next = node_p;
            list->last = node_p;
            if (!list->size) list->first = node_p;
            list->size ++;

        } else current_error = PLT_NOT_ENOUGH_SPACE;
    } else current_error = PLT_INVALID_ARGUMENT;
}

void pltInject (PLTList list, void *element_p) {
    if (list && element_p) {
        struct Node* node_p = (struct Node*) malloc(sizeof(struct Node*));

        if (node_p) {
            node_p->next = list->first;
            node_p->previous = NULL;
            node_p->element_p = element_p;

            if (list->first) list->first->previous = node_p;
            list->first = node_p;
            list->size ++;
        } else current_error = PLT_NOT_ENOUGH_SPACE;
    } else current_error = PLT_INVALID_ARGUMENT;
}

void pltInsert (PLTList list, unsigned position, void* element_p) {
    struct Node* node_p = NULL;

    if (list && element_p && (position < list->size)) {
        if (position == list->size - 1) pltAppend(list, element_p);
        else if (position == 0) pltInject(list, element_p);
        else {
            node_p = (struct Node*) malloc(sizeof(struct Node*));
            struct Node* current_node_p = getNode(list, position);

            if (node_p) {
                node_p->next = current_node_p;
                node_p->previous = current_node_p->previous;
                node_p->element_p = element_p;

                current_node_p->previous->next = node_p;
                current_node_p->previous = node_p;

                list->size ++;
            } else current_error = PLT_NOT_ENOUGH_SPACE;
        }
    } else current_error = PLT_INVALID_ARGUMENT;
}

void* pltLookElement (const PLTList list, unsigned position) {
    if (list && (position < list->size))
        return getNode(list, position)->element_p;
    else current_error = PLT_INVALID_ARGUMENT;

    return NULL;
}

void* pltLookLastElement (const PLTList list) {
    if (list && list->size) return list->last->element_p;
    current_error = PLT_INVALID_ARGUMENT;

    return NULL;
}

void* pltLookFirstElement (const PLTList list) {
    if (list && list->size) return list->first->element_p;
    current_error = PLT_INVALID_ARGUMENT;

    return NULL;
}

void* pltGetElement (PLTList list, unsigned position) {
    if (list && list->size) {
        if (! position) return pltGetFirstElement(list);
        else if (position == list->size - 1) return pltGetLastElement(list);
        else {
            struct Node* node = getNode(list, position);
            void* element_p = node->element_p;

            node->previous->next = node->next;
            node->next->previous = node->previous;
            list->size --;
            free(node);

            return element_p;
        }
    }

    current_error = PLT_INVALID_ARGUMENT;

    return NULL;
}

void* pltGetLastElement (PLTList list) {
    if (list && list->size) {
        struct Node* last_node = list->last;
        void* element_p = list->last->element_p;

        if (list->last->previous) list->last->previous->next = NULL;
        else list->first = NULL;
        list->last = list->last->previous;
        list->size --;
        free(last_node);

        return element_p;
    }

    current_error = PLT_INVALID_ARGUMENT;

    return NULL;
}

void* pltGetFirstElement (PLTList list) {
    if (list && list->size) {
        struct Node* first_node = list->first;
        void* element_p = list->first->element_p;

        if (list->first->next) list->first->next->previous = NULL;
        else list->last = NULL;
        list->first = list->first->next;
        list->size --;
        free(first_node);

        return element_p;
    }

    current_error = PLT_INVALID_ARGUMENT;

    return NULL;
}

unsigned pltLength (const PLTList list) {
    if (list) return list->size;
    else current_error = PLT_INVALID_ARGUMENT;

    return 0;
}

PLTList pltSearch (
    const PLTList list,
    int (*comparator) (const void*, void*),
    void* element_of_comparison_p
) {
    if (list && element_of_comparison_p) {
        int i;
        struct Node* node_p = NULL;
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
    } else current_error = PLT_INVALID_ARGUMENT;

    return NULL;
}

void* pltSearchElement (
    const PLTList list,
    int (*comparator) (const void*, void*),
    void* element_of_comparison_p
) {
    if (list && element_of_comparison_p) {
        int i;
        struct Node* node_p = NULL;

        comparator = comparator ? comparator : PLT_DEFAULT_COMPARATOR;

        for (
            i = 0, node_p = list->first;
            i < list->size;
            i ++, node_p = node_p->next
        ) if (comparator(node_p->element_p, element_of_comparison_p))
            return node_p->element_p;

    } else current_error = PLT_INVALID_ARGUMENT;

    return NULL;
}

int pltGetError (void) {
    int error_return = current_error;

    current_error = PLT_NO_ERROR;

    return error_return;
}

void pltPrint (const PLTList list) {
    if (list) {
        int i = 0;
        struct Node* node_p = NULL;

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

int pltTestCase (void) {
    void *aux1_p = NULL, *aux2_p = NULL;
    int i, vector1[] = { 1, 2, 3, 4, 5 }, vector2[] = { 6, 7 };
    int vector3[] = { 1, 2, 2, 2, 5, 6 };
    PLTList list_aux = NULL;

    /* pltNew() */
    PLTList list = pltNew();
    PUNT_ASSERT(list != NULL);
    PUNT_ASSERT(list->size == 0);
    PUNT_ASSERT(list->first == NULL);
    PUNT_ASSERT(list->last == NULL);

    /* pltAppend(), pltLookLastElement(), pltLength() */
    for (i = 0; i < 5; i ++) {
        pltAppend(list, vector1 + i);
        PUNT_ASSERT(pltLookLastElement(list) == vector1 + i);
    }
    PUNT_ASSERT(pltLength(list) == 5);

    /* pltInject(), pltLookFirstElement() */
    for (i = 0; i < 2; i ++) {
        pltInject(list, vector2 + i);
        PUNT_ASSERT(pltLookFirstElement(list) == vector2 + i);
    }
    PUNT_ASSERT(pltLength(list) == 7);

    /* pltInsert(), pltLookElement() */
    pltInsert(list, 4, vector1 + 3);
    PUNT_ASSERT(pltLookElement(list, 4) == vector1 + 3);
    PUNT_ASSERT(pltLength(list) == 8);

    /* pltGetFirstElement() */
    aux1_p = pltLookFirstElement(list);
    aux2_p = pltGetFirstElement(list);
    PUNT_ASSERT(aux1_p == aux2_p);
    PUNT_ASSERT(pltLookFirstElement(list) != aux2_p && aux2_p != NULL);
    PUNT_ASSERT(pltLength(list) == 7);

    /* pltGetLastElement() */
    aux1_p = pltLookLastElement(list);
    aux2_p = pltGetLastElement(list);
    PUNT_ASSERT(aux1_p == aux2_p);
    PUNT_ASSERT(pltLookLastElement(list) != aux2_p && aux2_p != NULL);
    PUNT_ASSERT(pltLength(list) == 6);

    /* pltGetElement() */
    aux1_p = pltLookElement(list, 2);
    aux2_p = pltGetElement(list, 2);
    PUNT_ASSERT(aux1_p == aux2_p);
    PUNT_ASSERT(pltLookElement(list, 2) != aux2_p && aux2_p != NULL);
    PUNT_ASSERT(pltLength(list) == 5);

    /* pltClear() */
    pltClear(list);
    PUNT_ASSERT(pltLength(list) == 0);
    PUNT_ASSERT(list->first == NULL);
    PUNT_ASSERT(list->last == NULL);

    /* pltDestroy() */
    pltDestroy(&list);
    PUNT_ASSERT(list == NULL);

    /* pltGetError() */
    current_error = PLT_INVALID_ARGUMENT;
    PUNT_ASSERT(pltGetError() == PLT_INVALID_ARGUMENT);
    PUNT_ASSERT(pltGetError() == PLT_NO_ERROR);

    /* pltSearchElement() */
    list = pltNew();
    for (i = 0; i < 5; i ++) pltAppend(list, vector1 + i);
    aux1_p = pltSearchElement(list, PLT_DEFAULT_COMPARATOR, vector1 + 3);
    PUNT_ASSERT(aux1_p == vector1 + 3);

    /* pltSearch() */
    pltClear(list);
    for (i = 0; i < 6; i ++) pltAppend(list, vector3 + i);
    list_aux = pltSearch(list, PLT_DEFAULT_COMPARATOR, vector3 + 1);
    for (i = 0; i < pltLength(list_aux); i ++)
        PUNT_ASSERT(pltLookElement(list_aux, i) == vector3 + 1);
    PUNT_ASSERT(pltLength(list_aux) == 1);

    return 1;
}

/* ========================================================================== */

#endif

