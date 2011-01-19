/*
**
** Prefix: phs
** $ Herond Robaina Salles
*/

/* ========================================================================== */

#ifndef _PRD_HASH_LIB_IMP
#define _PRD_HASH_LIB_IMP

#include "../list/plist.h"
#include "phash.h"

/* ========================================================================== */

struct PHSNode_ST {
    const void* key;
    PLTList elements;
};

struct PHSHash_ST {
    unsigned length;
    PLTList keys;
};

/* ========================================================================== */

extern int phs_current_error;

/* ========================================================================== */

#endif

