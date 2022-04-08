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
  //thank you for this piece of code Mr Donnet !
  unsigned int check = 0;

  while((val=getopt(argc, argv, optstring))!=EOF) {

    switch(val) {
      case 'f':
        printf("Format : %s\n",optarg);
        check++;
        format = optarg;
        break;
      case 'i':
        printf("Input : %s\n",optarg);
        check++;
        filename = optarg;
        break;
      case 'o':
        printf("Output : %s\n",optarg );
        check++;
        copyfile = optarg;
        break;
      case '?':
        printf("----------------------------------------------------------\n");
        printf("/!\\ Unknown option : %c /!\\\n",optopt);
        printf("----------------------------------------------------------\n");
        exit(EXIT_FAILURE);
        break;
      case ':':
        printf("----------------------------------------------------------\n");
        printf("/!\\ Missing argument : %c /!\\\n",optopt);
        printf("----------------------------------------------------------\n");
        exit(EXIT_FAILURE);
        break;
      default:
        break;
    }
    
  }


  //check if all arguments has been read
  const unsigned int NUMBER_OPTIONS = 3;
  if(check != NUMBER_OPTIONS) {
    printf("----------------------------------------------------------\n");
    printf("/!\\ Missing arguments /!\\\n");
    printf("----------------------------------------------------------\n");
    exit(EXIT_FAILURE);
  }


  //check all format
  switch(compare_format(format, filename, copyfile)) {
  case -1:
    printf("----------------------------------------------------------\n");
    printf("/!\\ F.ERROR : Wrong output format /!\\\n");
    printf("----------------------------------------------------------\n");
    exit(EXIT_FAILURE);
    break;
  case -2:
    printf("----------------------------------------------------------\n");
    printf("/!\\ F.ERROR : Wrong input format /!\\\n");
    printf("----------------------------------------------------------\n");
    exit(EXIT_FAILURE);
    break;
  default:
    break;
  }  


  //load the pnm image
  switch (load_pnm(&image, filename)) {
  case -1:
    printf("----------------------------------------------------------\n");
    printf("/!\\ L.ERROR : Memory problem(s) /!\\\n");
    printf("----------------------------------------------------------\n");
    exit(EXIT_FAILURE);
    break;
  case -2:
    printf("----------------------------------------------------------\n");
    printf("/!\\ L.ERROR : Input filename malformed /!\\\n");
    printf("----------------------------------------------------------\n");
    exit(EXIT_FAILURE);
    break;
  case -3:
    printf("----------------------------------------------------------\n");
    printf("/!\\ L.ERROR : Input file malformed /!\\\n");
    printf("----------------------------------------------------------\n");
    exit(EXIT_FAILURE);
    break;  
  default:
    printf("----------------------------------------------------------\n");
    printf("L.MESSAGE : File loaded succefully !\n");
    break;
  }

  //check the extension and the magic number
  if(check_magic_and_extension(image, filename)) {
    printf("----------------------------------------------------------\n");
    printf("/!\\ E/M.ERROR : Wrong extension or magic number /!\\\n");
    printf("----------------------------------------------------------\n");
    exit(EXIT_FAILURE);
  }

  //write the pnm image
  switch (write_pnm(image, copyfile)) {
  case -1:
    printf("----------------------------------------------------------\n");
    printf("/!\\ W.ERROR : Output filename forbidden /!\\\n");
    printf("----------------------------------------------------------\n");
    destroy_pnm(image);
    exit(EXIT_FAILURE);
    break;
  case -2:
    printf("----------------------------------------------------------\n");
    printf("/!\\ W.ERROR : The image could not be saved in a file /!\\\n");
    printf("----------------------------------------------------------\n");
    destroy_pnm(image);
    exit(EXIT_FAILURE);
    break;
  default:
    printf("W.MESSAGE : File written succefully !\n");
    break;
  }

  printf("----------------------------------------------------------\n");

  destroy_matrix(get_matrix(image), get_nbr_rows(image));
  destroy_pnm(image);

  return 0;
}

