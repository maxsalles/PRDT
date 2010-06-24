/*
** Manipula strings
** Prefixo: pst
** $ Herond Robaina Salles
** 07 Mai 2010
*/

/* ========================================================================== */

#ifndef PRD_STRING
#define PRD_STRING

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PST_NOT_PRESENT (-1)

/* ========================================================================== */

char* pstPersist (const char* string);

int pstLocationOf (const char* string, const char** array);

char* pstCharToString (char character);

char* pstAddChar (char* string, unsigned position, char character);

char* pstCharApend (char** string, char character);

/* ========================================================================== */

#endif

