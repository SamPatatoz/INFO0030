#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "LFSR.h"
#include "pnm.h"
#include "basic_cipher_mod.h"

#define OCC_GEN 32

void transformation (char *seed, unsigned short tap, unsigned short l, unsigned short c, unsigned short **m, char *perfectNbr)
{
    assert(seed!=NULL && tap > 0 && l>0 && c>0);

    LFSR *lfsr = initialisation(seed, tap);
    int i,j;
    switch (perfectNbr[1])
    {
      case '1':
      for(i=0; i<l; i++)
      {
          for(j=0; j<c; j++)
          {
              m[i][j] =( m[i][j]) ^ (generation(lfsr, OCC_GEN));
          }
        
      }
        break;

      case '2':
      for(i=0; i<l; i++)
      {
          for(j=0; j<c; j++)
          {
              m[i][j] =( m[i][j]) ^ (generation(lfsr, OCC_GEN));
          }
        
      }
        break;

      case '3':
      for(i=0; i<l; i++)
      {
          for(j=0; j<c*3; j++)
          {
              m[i][j] =( m[i][j]) ^ (generation(lfsr, OCC_GEN));
          }
        
      }
        break;

      default:
        break;
    }
    
    destroy_lfsr(lfsr);
}
