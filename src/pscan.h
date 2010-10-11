/*
** Analisador léxico
** Prefixo: psc
** $ Herond Robaina Salles
** 07 Mai 2010
*/

/* ========================================================================== */

#ifndef _PRD_SCAN_LIB
#define _PRD_SCAN_LIB

#include <stdio.h>

#include "ptoken.h"

/* ========================================================================== */

PTYToken_ST pscGetToken (FILE* source_code);

PTYToken_ST pscGetTokenIgnoring (int token, FILE* source_code);

/* ========================================================================== */

#endif

