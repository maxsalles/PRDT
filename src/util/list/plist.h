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

PLTList pltNew (void);

PLTList pltCopy (PLTList list);

void pltClear (PLTList list);

void pltDestroy (PLTList* list_p);

void pltAppend (PLTList list, void* element_p);

void pltInject (PLTList list, void* element_p);

void pltInsert (PLTList list, unsigned position, void* element_p);

void pltSetElement (PLTList list, unsigned position, void* element_p);

void* pltLookElement (const PLTList list, unsigned position);

void* pltLookLastElement (const PLTList list);

void* pltLookFirstElement (const PLTList list);

void* pltGetElement (PLTList list, unsigned position);

void* pltGetLastElement (PLTList list);

void* pltGetFirstElement (PLTList list);

void pltReverse (PLTList list);

unsigned pltLength (const PLTList list);

PLTList pltSearch (
    const PLTList list,
    int (*comparator) (const void*, void*),
    void* element_of_comparison_p
);

void* pltSearchElement (
    const PLTList list,
    int (*comparator) (const void*, void*),
    void* element_of_comparison_p
);

int pltGetError (void);

void pltPrint (const PLTList list);

/* ========================================================================== */

int pltDefaultComparator (
    const void* element_p,
    void* element_of_comparison_p
);

/* ========================================================================== */

#endif

