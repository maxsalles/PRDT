/*
**
** Prefix: phs
** $ Herond Robaina Salles
*/

/* ========================================================================== */

#ifndef _PRD_HASH_LIB
#define _PRD_HASH_LIB

#include <errno.h>

#include "../list/plist.h"

/* ========================================================================== */

enum PHSErros_EN {
    PHS_NO_ERROR = 0,
    PHS_NOT_ENOUGH_SPACE = ENOMEM,
    PHS_INVALID_ARGUMENT = EINVAL
};

struct PHSRash_ST;

typedef struct PHSRash_ST* PHSRash;

/* ========================================================================== */

PHSRash phsNew (void);

PHSRash phsCopy (const PHSRash rash);

void phsClear (PHSRash rash);

void phsDestroy (PHSRash* rash_p);

void phsAdd (PHSRash rash, const void* key, const void* element_p);

void phsRemoveElement (PHSRash rash, const void* element_p);

void phsRemoveKey (PHSRash rash, const void* key);

int phsHasElement (const PHSRash rash, const void* elemento_p);

int phsHasKey (const PHSRash rash, const void* key);

unsigned phsLength (const PHSRash rash);

PLTList phsSearch (
    const PHSHash hash,
    int (*comparator) (const void*, void*),
    void* element_of_comparison_p
);

void* phsSearchElement (
    const PHSHash hash,
    int (*comparator) (const void*, void*),
    void* element_of_comparison_p
);

int phsGetError (void);

void phsPrint (const PHSHash list);

/* ========================================================================== */

#endif

