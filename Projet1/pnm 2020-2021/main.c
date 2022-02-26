/**
 * main.c
 *
 * Ce fichier contient la fonction main() du programme de manipulation
 * de fichiers pnm.
 *
 * @author: El Masri Sam s190377
 * @date: 24/06/2021
 * @projet: INFO0030 Projet 1
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <ctype.h>
#include <getopt.h>

#include "pnm.h"


int main(int argc, char *argv[])
{

  PNM *image = NULL;
  char *filename;
  char *copyfile;
  char *format;
  char *optstring = ":f:i:o:";
  int val;

  printf("\n");

  while((val=getopt(argc, argv, optstring))!=EOF)
  {
    switch(val)
    {
      case 'f':
        printf("Format : %s\n",optarg);
        format = optarg;
        break;
      case 'i':
        printf("Input : %s\n",optarg);
        filename = optarg;
        break;
      case 'o':
        printf("Output : %s\n",optarg );
        copyfile = optarg;
        break;
      case '?':
        printf("Unknown option : %c\n",optopt);
        return 0;
        break;
      case ':':
        printf("Missing argument : %c\n",optopt);
        return 0;
        break;
      default:
        break;
    }
  }

  printf("\n");

  if(format_compare(filename, format)==-1)
  {
    printf("Wrong format passed in argument\n");
    return 0;
  }

  if(return_error_load(load_pnm(&image,filename))==-1)
  {
    return 0;
  }

  if(write_pnm(image,copyfile)==-1)
  {
    printf("The name of the output file passed in argument is not valid\n");
    return 0;
  }

  printf("Input file successfully copied to output file !\n");
  return 0;
}
