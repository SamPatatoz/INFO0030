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
#include <string.h>
#include <sys/stat.h>

#include "pnm.h"
#include "codebarre.h"
#include "codebarreCorrection.h"

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

int main(int argc, char *argv[]) {
  PNM *image = NULL;
  char *directory;
  char *file;
  char *optstring = ":f:o:";
  int val;

  printf("----------------------------------------------------------\n");
  //thank you for this piece of code Mr Donnet !
  unsigned int check = 0;

  while((val=getopt(argc, argv, optstring))!=EOF) {

    switch(val) {
      case 'f':
        printf("File : %s\n",optarg);
        check++;
        file = optarg;
        break;
      case 'o':
        printf("Output directory : %s\n",optarg );
        check++;
        directory = optarg;
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
printf("----------------------------------------------------------\n");

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

  char *codebarre = "codebarre";
  if(!(strcmp(directory, codebarre))) {
    printf("----------------------------------------------------------\n");
    printf("/!\\EXE.ERROR : Prohibited directory (codebarre) /!\\\n");
    printf("----------------------------------------------------------\n");
    exit(EXIT_FAILURE);   
  }
  //check if all arguments has been read
  const unsigned int NUMBER_OPTIONS = 2;
  if(check != NUMBER_OPTIONS) {
    printf("----------------------------------------------------------\n");
    printf("/!\\EXE.ERROR : Missing arguments /!\\\n");
    printf("----------------------------------------------------------\n");
    exit(EXIT_FAILURE);
  }

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

  CODE *barCode = NULL;
  if(create_bar_code(&barCode) == NULL) {
    printf("----------------------------------------------------------\n");
    printf("/!\\ BC.ERROR : Memory problem(s) /!\\\n");
    printf("----------------------------------------------------------\n");    
    exit(EXIT_FAILURE);
  }

  FILE *fpR = fopen(file, "r");
  if (fpR == NULL) {
    printf("----------------------------------------------------------\n");
    printf("/!\\ EXE.ERROR : Input file not found /!\\\n");
    printf("----------------------------------------------------------\n");
    destroy_bar_code(barCode);
    exit(EXIT_FAILURE);
  }
  
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

  const unsigned int MAX_REGISTRATION = 9;
  //max for linux
  const unsigned int MAX_LENGTH = 255;
  
  char outputFile[MAX_LENGTH];
  unsigned checkEnter = 0;
  char tempRegistration[MAX_REGISTRATION];
  
  //loop while there is something in the input file
  while(fscanf(fpR, "%s", tempRegistration) == 1) {
    checkEnter = 1;

    //set the registration number of the bar code
    set_registration_number(barCode, atoi(tempRegistration));
    //load the pnm image from the data of the bar code
    switch (complete_pnm(barCode, &image, tempRegistration)) {
      case memoryProblem:
        printf("----------------------------------------------------------\n");
        printf("/!\\ BC.ERROR : Memory problem(s) /!\\\n");
        printf("----------------------------------------------------------\n");
        fclose(fpR);
        destroy_bar_code(barCode);
        exit(EXIT_FAILURE);
        break;
      case error:
        printf("----------------------------------------------------------\n");
        printf("/!\\ BC.ERROR : Input problem(s) /!\\\n");
        printf("----------------------------------------------------------\n");
        fclose(fpR);
        destroy_bar_code(barCode);
        exit(EXIT_FAILURE);
        break;
      default:
        break;
    }

    //make de outPut file for the writting
    strcpy(outputFile, directory);
    strcat(outputFile, "/");
    strcat(outputFile, tempRegistration);

    //write the pbm image
    switch (write_pnm(image, outputFile)) {
      case -1:
        printf("----------------------------------------------------------\n");
        printf("/!\\ W.ERROR : Output filename forbidden /!\\\n");
        printf("----------------------------------------------------------\n");
        destroy_matrix(get_matrix(image), get_nbr_rows(image));
        destroy_pnm(image);
        fclose(fpR);
        exit(EXIT_FAILURE);
        break;
      case -2:
        //make directory
        mkdir(directory, S_IRWXU);
        destroy_pnm(image);
        printf("----------------------------------------------------------\n");
        printf("/!\\ W.WARNING : Directory has been created/!\\\n");
        printf("----------------------------------------------------------\n");
        //rewind the fp to the start of the file
        rewind(fpR);
        break;
      default:
        //free all
        destroy_matrix(get_matrix(image), get_nbr_rows(image));
        destroy_pnm(image);
        printf("W.MESSAGE : File %s written succefully !\n", tempRegistration);
        break;
    }

  }

  printf("----------------------------------------------------------\n");
  //check if it has read the input file
  if(!checkEnter) {
    printf("----------------------------------------------------------\n");
    printf("/!\\ EXE.WARNING : Input file empty /!\\\n");
    printf("----------------------------------------------------------\n");
  }
  
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

  fclose(fpR);
  destroy_bar_code(barCode);

  exit (EXIT_SUCCESS);
}

