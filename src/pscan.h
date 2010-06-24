/*
** Analisador léxico
** Prefixo: psc
** $ Herond Robaina Salles
** 07 Mai 2010
*/

/* ========================================================================== */

#ifndef PRD_SCAN
#define PRD_SCAN

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "pstring.h"
#include "ptypes.h"

/* ========================================================================== */

PtyToken pscGetToken (FILE* source_code);

PtyToken pscGetTokenIgnoring (int token, FILE* source_code);

/* ========================================================================== */

#endif

