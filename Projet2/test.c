#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "LFSR.h"

int main () {
    char seed[] = "01101000010";
    LFSR * lfsr = initialisation (seed, 8);
    for (int i = 0; i < 10; i ++)
    {
        int r = generation (lfsr , 5);
        printf ("%s %d\n", string (lfsr) , r );
    }
}