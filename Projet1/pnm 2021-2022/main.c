/**
 * main.c
 * 
 * Ce fichier contient la fonction main() du programme de manipulation
 * de fichiers pnm.
 *
 * @author: EL MASRI Sam s190377
 * @date: 24/02/2022
 * @projet: INFO0030 Projet 1
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <ctype.h>
#include <getopt.h>

#include "pnm.h"


int main(int argc, char *argv[]) {
  PNM *image = NULL;
  char *filename;
  char *copyfile;
  char *format;
  char *optstring = ":f:i:o:";
  int val;

  printf("\n");
  printf("----------------------------------------------------------\n");
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

  if(compare_format(format, filename) == -2) {
    printf("----------------------------------------------------------\n");
    printf("/!\\ F.ERROR : Wrong format input /!\\\n");
    printf("----------------------------------------------------------\n");
    abort();
  }


  switch (load_pnm(&image, filename))
  {
  case -1:
    printf("----------------------------------------------------------\n");
    printf("/!\\ L.ERROR : Memory problem(s) /!\\\n");
    printf("----------------------------------------------------------\n");
    abort();
    break;
  case -2:
    printf("----------------------------------------------------------\n");
    printf("/!\\ L.ERROR : Input filename malformed /!\\\n");
    printf("----------------------------------------------------------\n");
    abort();
    break;
  case -3:
    printf("----------------------------------------------------------\n");
    printf("/!\\ L.ERROR : Input file malformed /!\\\n");
    printf("----------------------------------------------------------\n");
    abort();
    break;  
  default:
    printf("----------------------------------------------------------\n");
    printf("L.MESSAGE : File loaded succefully !\n");
    break;
  }


  switch (write_pnm(image, copyfile)) 
  {
  case -1:
    printf("----------------------------------------------------------\n");
    printf("/!\\ W.ERROR : Output filename forbidden /!\\\n");
    printf("----------------------------------------------------------\n");
    abort();
    break;
  case -2:
    printf("----------------------------------------------------------\n");
    printf("/!\\ W.ERROR : The image could not be saved in a file /!\\\n");
    printf("----------------------------------------------------------\n");
    abort();
    break;
  default:
    printf("W.MESSAGE : File written succefully !\n");
    printf("----------------------------------------------------------\n");
    break;
  }

  printf("\n");

  return 0;
}
