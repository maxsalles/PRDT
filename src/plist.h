/*
**
** Prefix: plt
** $ Herond Robaina Salles
*/

/* ========================================================================== */

#ifndef _PRD_LIST_LIB
#define _PRD_LIST_LIB

#include <errno.h>

/* ========================================================================== */

#define PLT_DEFAULT_COMPARATOR (pltDefaultComparator)

/* ========================================================================== */

enum PLTErros_EN {
    PLT_NO_ERROR = 0,
    PLT_NOT_ENOUGH_SPACE = ENOMEM,
    PLT_INVALID_ARGUMENT = EINVAL
};

struct PLTList_ST;

typedef struct PLTList_ST* PLTList;

/* ========================================================================== */

PLTList pltNew (void); /* OK */

PLTList pltCopy (PLTList list);

void pltClear (PLTList list); /* OK */

void pltDestroy (PLTList* list_p); /* OK */

void pltAppend (PLTList list, void* element_p); /* OK */

void pltInject (PLTList list, void* element_p); /* OK */

void pltInsert (PLTList list, unsigned position, void* element_p); /* OK */

void pltSetElement (PLTList list, unsigned position, void* element_p);

void* pltLookElement (const PLTList list, unsigned position); /* OK */

void* pltLookLastElement (const PLTList list); /* OK */

void* pltLookFirstElement (const PLTList list); /* OK */

void* pltGetElement (PLTList list, unsigned position); /* OK */

void* pltGetLastElement (PLTList list); /* OK */

void* pltGetFirstElement (PLTList list); /* OK */

void pltReverse (PLTList list);

unsigned pltLength (const PLTList list); /* OK */

PLTList pltSearch (
    const PLTList list,
    int (*comparator) (const void*, void*),
    void* element_of_comparison_p
); /* OK */

void* pltSearchElement (
    const PLTList list,
    int (*comparator) (const void*, void*),
    void* element_of_comparison_p
); /* OK */

int pltGetError (void); /* OK */

void pltPrint (const PLTList list); /* OK */

/* ========================================================================== */

int pltDefaultComparator (
    const void* element_p,
    void* element_of_comparison_p
);

/* ========================================================================== */

#ifdef PLT_TEST_CASE

int pltTestCase (void);

#endif

/* ========================================================================== */

#endif

