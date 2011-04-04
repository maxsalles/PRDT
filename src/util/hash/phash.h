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

typedef struct PHSHash_ST* PHSHash;

/* ========================================================================== */

PHSHash phsNew (void); /* OK */

PHSHash phsCopy (const PHSHash hash);

void phsClear (PHSHash hash);

void phsDestroy (PHSHash* hash_p);

void phsAdd (PHSHash hash, const void* key, const void* element_p); /* OK */

void phsRemoveElement (PHSHash hash, const void* element_p);

void phsRemoveKey (PHSHash hash, const void* key);

int phsHasElement (const PHSHash hash, const void* elemento_p);

int phsHasKey (const PHSHash hash, const void* key);

unsigned phsLength (const PHSHash hash);

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

void phsPrint (const PHSHash hash); /* OK */

/* ========================================================================== */

#endif

