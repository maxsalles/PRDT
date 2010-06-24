/*
** Parser
** Prefixo: prs
** $ Herond Robaina Salles
** 27 Mai 2010
*/

/* ========================================================================== */

#ifndef PRS_LIB
#define PRS_LIB

#include <stdio.h>

#include "ptypes.h"
#include "ptkbuffer.h"

/* ========================================================================== */

/*
** O parse no futuro deve retornar a arvore sintática e a tabela de simbolos
** com as inserções apropriadas
*/
/*PtrTree*/ void prsParse (FILE* source_code /*, PstSinTab* sin_tab*/) {
    if (source_code) {
        PtbBuffer token_buffer = ptbNew(source_code);



    } exit(1); /* trocar por um erro apropriado */
}

/* ========================================================================== */

#endif

