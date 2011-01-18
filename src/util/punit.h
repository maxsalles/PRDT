/*
**
** Prefix: punt
** $ Herond Robaina Salles
*/

#ifndef _PRD_UNIT_LIB
#define _PRD_UNIT_LIB

/* ========================================================================== */

#define PUNT_ASSERT(A) {                                \
    printf(                                             \
        "%s - In %s:%i - Assertion %s.\n",              \
        (A) ? "OK" : "FAIL", __FILE__, __LINE__, #A     \
    );                                                  \
}

int puntRunTestCase (const char* description, int (*testCase) (void));

/* ========================================================================== */

#endif

