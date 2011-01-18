/*
**
** Prefix: punt
** $ Herond Robaina Salles
*/

#ifndef _PRD_UNIT_IMP
#define _PRD_UNIT_IMP

#include "punit.h"

#include <stdio.h>

/* ========================================================================== */

int puntRunTestCase (const char* description, int (*testCase) (void)) {
    if (testCase) {
        puts("");
        puts(description);
        testCase();

        return 1;
    } else return 0;
}

/* ========================================================================== */

#endif

