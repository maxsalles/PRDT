/*
**
** Prefix: plt
** $ Herond Robaina Salles
*/

/* ========================================================================== */

#ifndef _PRD_LIST_LIB_IMP
#define _PRD_LIST_LIB_IMP

#include "plist.h"

/* ========================================================================== */

struct PLTNode {
    void* element_p;
    struct PLTNode* next;
    struct PLTNode* previous;
};

struct PLTList_ST {
    unsigned size;
    struct PLTNode* first;
    struct PLTNode* last;
};

/* ========================================================================== */

extern int plt_current_error;

/* ========================================================================== */

struct PLTNode* pltGetNode (PLTList list, unsigned position);

/* ========================================================================== */

#endif

