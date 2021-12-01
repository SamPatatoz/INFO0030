#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "LFSR.h"
#include "pnm.h"
#include "basic_cipher_mod.h"
#include "advanced_cipher_mod.h"


#define MAX_BIN 6

static int check_position (char var)
{
    //char model
    char * base64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    for(int i=0; i<63; i++)
    {
       if(var == base64[i])
       {
           return i;
       } 
    }
    return -1;

}

static char *pos_to_binary (int x)
{
    int d = 0;
    int t = 0;

    char *bin = malloc(MAX_BIN+1);
    if (bin == NULL)
    {
      printf("Not enough memory\n");
      exit (EXIT_FAILURE);
    }
    

    for (int i=MAX_BIN-1; i>=0 ;i--)
    {
      d = x>>i;

      if (d & 1)
        bin[t] = '1';

      else
        bin[t] = '0';

      t++;
    }

    return  bin;
}

char *binary_to_seed (char *word)
{
  int i;
  char *password = malloc(61);
  if(password == NULL)
  {
    printf("Not enough memory\n");
    exit (EXIT_FAILURE);
  }
  password[0] = '\0';

  char* bin;
  int N = strlengt(word);
  for(i=0; i<N; i++)
  {
    bin = pos_to_binary((check_position(word[i])));
    strcat(password,bin);
    free(bin);
  }
  
  printf("%s \n", password);
  return password;
}
