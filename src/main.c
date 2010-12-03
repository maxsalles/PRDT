#define PLT_TEST_CASE (pltTestCase)

#include <stdio.h>

#include "punit.h"
#include "plist.h"

int main (void) {
    puntRunTestCase(
        "Unit test from plist.c",
        PLT_TEST_CASE
    );

	return 0;
}

