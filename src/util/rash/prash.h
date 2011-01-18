/*
**
** Prefix: prs
** $ Herond Robaina Salles
*/

/* ========================================================================== */

#ifndef _PRD_RASH_LIB
#define _PRD_RASH_LIB

#include <errno.h>

/* ========================================================================== */

enum PRSErros_EN {
    PRS_NO_ERROR = 0,
    PRS_NOT_ENOUGH_SPACE = ENOMEM,
    PRS_INVALID_ARGUMENT = EINVAL
};

struct PRSRash_ST;

typedef struct PRSRash_ST* PRSRash;

/* ========================================================================== */

PRSRash prsNew (void);

PRSRash prsCopy (const PRSRash rash);

void prsClear (PRSRash rash);

void prsDestroy (PRSRash* rash_p);

void prsAdd (PRSRash rash, const void* key, const void* element_p);

/* ========================================================================== */

#endif

