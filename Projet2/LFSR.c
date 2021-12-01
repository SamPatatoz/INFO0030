#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "LFSR.h"
#include "pnm.h"

struct LFSR_t
{

    int N;
    char *seed;
    unsigned short tap;
    
};

// ----------------ACCESSOR
LFSR *create_lfsr(char *seed, unsigned short tap)
{
    
    LFSR *lfsr = malloc(sizeof(LFSR));
    if(lfsr==NULL)
        return NULL;

    lfsr->N = strlengt(seed);
    lfsr->seed = seed;
    lfsr->tap = tap;
    return lfsr;
}

void destroy_lfsr(LFSR *lfsr)
{
    if(lfsr != NULL)
    free(lfsr);
}

int get_N(LFSR *lfsr)
{
    assert(lfsr!=NULL);

    return lfsr->N;
}

char *get_seed(LFSR *lfsr)
{
    assert(lfsr!=NULL);

    return lfsr->seed;
}

unsigned short get_tap(LFSR *lfsr)
{
    assert(lfsr!=NULL);

    return lfsr->tap;
}

LFSR *set_N(LFSR *lfsr, int N)
{
    assert(lfsr!=NULL);

    lfsr->N = N;
    return lfsr;
}

LFSR *set_tap(LFSR *lfsr, unsigned short tap)
{
    assert(lfsr!=NULL);

    lfsr->tap = tap;
    return lfsr;
}

LFSR *set_seed(LFSR *lfsr, char *seed)
{
    assert(lfsr!=NULL);

    lfsr->seed = seed;
    return lfsr;
}
// ----------------END ACCESSOR


LFSR* initialisation (char* seed, unsigned short tap)
{
    assert(seed!=NULL && tap >0);

    LFSR *lfsr = create_lfsr(seed, tap);

    return lfsr;
}


char *string(LFSR *lfsr, char *r)
{
    assert(lfsr != NULL);
 
    for(int i=0; i<get_N(lfsr)-1; i++)
    {
        r[i] = r[i+1];
    }

    return r;
}


int operation(LFSR *lfsr)
{
    assert(lfsr != NULL);

    int bit;
    char *r = get_seed(lfsr);
    int N = get_N(lfsr);
    unsigned int tap = N - get_tap(lfsr) - 1;

    char topbit = r[0];
    char tapR = r[tap];

    r = string(lfsr, get_seed(lfsr));

    if(topbit == tapR)
    {
        r[N-1] = '0';
        bit = 0;
    }
    else
    {
        r[N-1] = '1';
        bit = 1;
    }
    return bit;
}


int generation(LFSR *lfsr, int x)
{
   assert(lfsr != NULL && x > 0);
   int result = 0;
   int i;

   for(i=0; i<x; i++)
   {
       if(operation(lfsr) == 1)
       {
           result = (result * 2) + 1;
       }
       else
       {
           result = result *2;
       }
    }
   return result;
}
