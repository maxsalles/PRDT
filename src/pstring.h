/*
** Manipula strings
** Prefix: pst
** $ Herond Robaina Salles
*/

/* ========================================================================== */

#ifndef _PRD_STRING_LIB
#define _PRD_STRING_LIB

#define PST_NOT_PRESENT (-1)

/* ========================================================================== */

char* pstCopy (const char* string);

int pstLocationOf (const char* string, const char** array);

char* pstCharToString (char character);

char* pstAddChar (char* string, unsigned position, char character);

char* pstCharApend (char** string, char character);

/* ========================================================================== */

#endif

