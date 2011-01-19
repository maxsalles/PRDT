#include <stdio.h>
#include <stdlib.h>

#include "punit.h"
#include "list/plist.h"
#include "list/plist_imp.h"
#include "hash/phash.h"
#include "hash/phash_imp.h"

/* ========================================================================== */

int listTestCase () {
    void *aux1_p = NULL, *aux2_p = NULL;
    int i, j, vector1[] = { 1, 2, 3, 4, 5 }, vector2[] = { 6, 7 };
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

    /* pltSetElement() */
    pltSetElement(list, 5, vector3 + 4);
    PUNT_ASSERT(pltLookElement(list, 5) == vector3 + 4);

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
    plt_current_error = PLT_INVALID_ARGUMENT;
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

    /* pltCopy() */
    pltClear(list);
    for (i = 0; i < 6; i ++) pltAppend(list, vector1 + i);
    list_aux = pltCopy(list);
    for (i = 0; i < pltLength(list); i ++)
        PUNT_ASSERT(pltLookElement(list_aux, i) == vector1 + i);
    PUNT_ASSERT(pltLength(list_aux) == pltLength(list));

    /* pltReverse() */
    pltReverse(list);
    for (i = 0, j = list->size - 1; i < list->size; i ++, j --)
        PUNT_ASSERT(pltLookElement(list, i) == vector1 + j);

    return 1;
}

/* ========================================================================== */

int hashTestcase () {
    int keys[] = { 1, 2, 3, 4, 5 };
    int i;

    PHSHash hash = phsNew();

    for (i = 0; i < 5; i ++)
        phsAdd(hash, keys + i, "Herond");

    phsPrint(hash);

    return 1;
}

/* ========================================================================== */

int main (void) {

    hashTestcase();

    /*listTestCase();*/

    return 0;
}

