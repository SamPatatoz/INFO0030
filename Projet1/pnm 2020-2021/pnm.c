/**
 * pnm.c
 * 
 * Ce fichier contient les définitions de types et 
 * les fonctions de manipulation d'images PNM.
 * 
 * @author: EL MASRI Sam s190377
 * @date: 24/02/2022
 * @projet: INFO0030 Projet 1
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "pnm.h"


#define MAJ 32
#define PPM_COLUMNS 3
#define PBM_MAX_VALUE 1 
#define PGM_PPM_MAX_VALUE 255



//all typedef------------------------------------------------------------------

typedef enum{pbm = 1, pgm = 2, ppm = 3}MagicNumber;

//use for return value
typedef enum{perfecto, memoryProblem = -1, wrongInput = -2, malformedInput = -3
            }LoadErrors;
typedef enum{perfect, wrongOutput = -1, failedSave = -2}WriteErrors;


struct PNM_t {
   MagicNumber magicNumber;
   unsigned int nbrColumns;
   unsigned int nbrRows;
   unsigned int maxValue;
   unsigned int **matrix;
};




/*definition of constructor/destructor/getters/setters-------------------------
 *the will be static for this project
 */

static PNM **create_pnm (PNM **pnm) {
   assert(pnm != NULL);

   *pnm = malloc(sizeof(PNM));
   if(pnm == NULL)
      return NULL;

   return pnm;
}


static void destroy_pnm (PNM *pnm) {
   assert(pnm != NULL);

   free(pnm);
}


static MagicNumber get_magic_number (PNM *pnm) {
   assert(pnm != NULL);

   return pnm->magicNumber;
}


static unsigned int get_nbr_columns (PNM *pnm) {
   assert(pnm != NULL);

   return pnm->nbrColumns;
}


static unsigned int get_nbr_rows (PNM *pnm) {
   assert(pnm != NULL);

   return pnm->nbrRows;
}


static unsigned int get_max_value(PNM *pnm) {
   assert(pnm != NULL);

   return pnm->maxValue;
}


static unsigned int **get_matrix (PNM *pnm) {
   assert(pnm != NULL);

   return pnm->matrix;
}


static PNM *set_magic_number (PNM *pnm, int magicNumber) {
   assert(pnm != NULL);

   pnm->magicNumber = magicNumber;

   return pnm;
}


static PNM *set_nbr_columns (PNM *pnm, unsigned int c) {
   assert(pnm != NULL);

   pnm->nbrColumns = c;

   return pnm;
}


static PNM *set_nbr_rows (PNM *pnm, unsigned int r) {
   assert(pnm != NULL);

   pnm->nbrRows = r;

   return pnm;
}


static PNM *set_max_value (PNM *pnm, unsigned int m) {
   assert(pnm != NULL);

   pnm->maxValue = m;

   return pnm;
}




//other functions--------------------------------------------------------------

static void checkif_commentary (FILE *fp) {
   assert(fp != NULL);

   fseek(fp, +1, SEEK_CUR);
   int check = fgetc(fp);

   if(check == 10)//Line feed format
      check = fgetc(fp);

   if(check == '#')
      fscanf(fp, "%*[^\n]\n");//Skip line
      //Place the value(s)
   else {
      fseek(fp, -1, SEEK_CUR);//Go back
      //Place the value(s)
   }

}


static unsigned int **create_matrix (PNM *pnm) {
   assert(pnm != NULL);

   unsigned int r = get_nbr_rows(pnm);
   unsigned int c = get_nbr_columns(pnm);
   MagicNumber magic = get_magic_number(pnm);

   unsigned int **matrix = malloc(sizeof(unsigned int*) * r);
   if(matrix == NULL)
      return NULL;

   if(magic == ppm)
      c = c * PPM_COLUMNS;

   for(unsigned int i = 0; i < r; i++) {

      matrix[i] = malloc(sizeof(unsigned int) * c);

      if(matrix[i] == NULL) {
         for(unsigned int j = 0; j < i; j++) {
            free(matrix[j]);
         }

      free(matrix);
      return NULL;
      }
   }

   return matrix;
}


static void destroy_matrix (unsigned int **matrix ,unsigned int r) {
   assert(matrix != NULL);

   for(unsigned int i = 0; i < r; i++) {
      free(matrix[i]);
    }
    free(matrix);
}


int compare_format (char *format, char *inputFilename, char *outputFilename) {
   assert(format != NULL && inputFilename != NULL && outputFilename != NULL);

   const unsigned int MAX_LENGTH = 4;
   char copyInputFilename[MAX_LENGTH];
   char copyOutputFilename[MAX_LENGTH];    
   unsigned int inputLength = strlen(inputFilename);
   unsigned int outputLength = strlen(outputFilename);

   //Convert letters to uppercase
   copyInputFilename[0] = inputFilename[inputLength-3] - MAJ;
   copyInputFilename[1] = inputFilename[inputLength-2] - MAJ;
   copyInputFilename[2] = inputFilename[inputLength-1] - MAJ;

   copyOutputFilename[0] = outputFilename[outputLength-3] - MAJ;
   copyOutputFilename[1] = outputFilename[outputLength-2] - MAJ;
   copyOutputFilename[2] = outputFilename[outputLength-1] - MAJ;

   //check input filename extension
   if(copyInputFilename[0] != format[0]) {
      return wrongInput;
   }
   if(copyInputFilename[1] != format[1]) {
      return wrongInput;
   }
   if(copyInputFilename[2] != format[2]) {
      return wrongInput;
   }

   //check output filename extension
   if(copyOutputFilename[0] != format[0]) {
      return wrongOutput;
   }
   if(copyOutputFilename[1] != format[1]) {
      return wrongOutput;
   }
   if(copyOutputFilename[2] != format[2]) {
      return wrongOutput;
   }   

   return perfecto;
}




//functions to read in the pnm file--------------------------------------------

static int read_magic_number (FILE *fp, PNM *pnm) {
   assert(fp != NULL && pnm != NULL);

   char *str = malloc(sizeof(char) * PPM_COLUMNS);
   if(str == NULL)
      return memoryProblem;

   fscanf(fp, "%s", str);
   
   if(str[0] != 'P')
      return malformedInput;
   //take the second symbol and typecast to int
   unsigned int p = str[1] - '0';

   //check for malformed magic number
   if(p != 1 && p != 2 && p!= 3) {
      return malformedInput;
   }

   else {
      set_magic_number(pnm, p);
   }

   free(str);

   return perfecto;
}


static void read_columns_rows (FILE *fp, PNM *pnm) {
   assert(fp != NULL && pnm != NULL);

   unsigned int c = 1, r = 1;
   fscanf(fp, "%u %u", &c, &r);

   set_nbr_columns(pnm, c);
   set_nbr_rows(pnm, r);
}


static int read_max_value (FILE* fp, PNM *pnm) {
   assert(fp != NULL && pnm != NULL);

   unsigned int maxValue = 0;
   fscanf(fp, "%u", &maxValue);

   if(maxValue > 255)
      return malformedInput;

   set_max_value(pnm, maxValue);

   return perfecto;
}


static int read_matrix (FILE *fp, PNM *pnm) {
   assert(fp != NULL && pnm != NULL);

   unsigned rows = get_nbr_rows(pnm);
   unsigned columns = get_nbr_columns(pnm);
   MagicNumber magic = get_magic_number(pnm);
   unsigned int **matrix = get_matrix(pnm);

   if(magic == ppm)
      columns = columns * PPM_COLUMNS;

   for(unsigned int i = 0; i < rows; i++) {
         for(unsigned int j = 0; j < columns; j++) {
            fscanf(fp,"%u ",&matrix[i][j]);

            //check for malformed matrix
            if(magic == ppm || magic == pgm) {
               if(matrix[i][j] > PGM_PPM_MAX_VALUE)
                  return malformedInput;
            }
            else {
               if(matrix[i][j] > PBM_MAX_VALUE)
                  return malformedInput;
            }
         }

   }

   return perfecto;
}



//load the initial pnm image---------------------------------------------------
//-----------------------------------------------------------------------------

int load_pnm(PNM **image, char* filename) {
   assert(image != NULL && filename != NULL);

   FILE *fp = fopen(filename, "r");
   if(fp == NULL)
      return wrongInput;

   if(create_pnm(image) == NULL)
      return memoryProblem;


   //read everything

   //check for error return
   int checkMagicNumber = read_magic_number(fp, (*image));
   if(checkMagicNumber == malformedInput) {
      return malformedInput;
   }

   else if(checkMagicNumber == memoryProblem) {
      return memoryProblem;
   }


   checkif_commentary(fp);

   read_columns_rows(fp, (*image));

   checkif_commentary(fp);


   //check if pbm, if not => read the max value
   if(get_magic_number(*image) != pbm) {
      read_max_value(fp, (*image));

      if(get_max_value(*image) > PGM_PPM_MAX_VALUE) {
         return malformedInput;
      }
   }
      
   checkif_commentary(fp);

   (*image)->matrix = create_matrix((*image));
   if(get_matrix(*image) == NULL) {
      return memoryProblem;
   }
      
   if(read_matrix(fp, (*image)) == malformedInput) {
      return malformedInput;
   }


   fclose(fp);

   return perfecto;
}




//functions to write in the pnm file-------------------------------------------

static void write_magic_number (FILE *fp, PNM *pnm) {
   assert(fp != NULL && pnm != NULL);

   fprintf(fp, "P%d\n", get_magic_number(pnm));
}


static void write_columns_rows (FILE *fp, PNM *pnm) {
   assert(fp != NULL && pnm != NULL);

   fprintf(fp, "%u %u\n", get_nbr_columns(pnm), get_nbr_rows(pnm));
}


static void write_max_value (FILE *fp, PNM *pnm) {
   assert(fp != NULL && pnm != NULL);

   fprintf(fp, "%u\n", get_max_value(pnm));
}


static void write_matrix (FILE *fp, PNM *pnm) {
   assert(fp != NULL && pnm != NULL);

   unsigned rows = get_nbr_rows(pnm);
   unsigned columns = get_nbr_columns(pnm);
   MagicNumber magic = get_magic_number(pnm);
   unsigned int **matrix = get_matrix(pnm);

   if(magic == ppm)
         columns = columns * PPM_COLUMNS;

   for(unsigned int i = 0; i < rows; i++) {

      for(unsigned int j = 0; j < columns; j++) {
         fprintf(fp,"%u ", matrix[i][j]);
      }

      fprintf(fp, "\n");
   }
}


static int check_output_filename (char *filename) {
   assert(filename != NULL);

   unsigned int lenght = strlen(filename);
   for(unsigned int i = 0; i < lenght; i++) {
      //if forbidden character for outputFileName => return wrongOutput
      switch (filename[i]) {
      case ':':
         return wrongOutput;
         break;
      case '*':
         return wrongOutput;
         break;
      case '?':
         return wrongOutput;
         break;
      case '"':
         return wrongOutput;
         break;
      case '<':
         return wrongOutput;
         break;
      case '>':
         return wrongOutput;
         break;
      case '|':
         return wrongOutput;
         break;
      default:
         break;
      }
   }

   return perfect;
}




//write the new pnm image------------------------------------------------------
//-----------------------------------------------------------------------------

int write_pnm(PNM *image, char* filename) {
   assert(image != NULL && filename != NULL);

   if(check_output_filename(filename) == wrongOutput)
      return wrongOutput;

   FILE *fp = fopen(filename, "w");
   if(fp == NULL)
      return failedSave;


   //write everything
   write_magic_number(fp, image);

   write_columns_rows(fp, image);

   if(get_magic_number(image) != pbm)
      write_max_value(fp, image);

   write_matrix(fp, image);


   //free all memory
   destroy_matrix(get_matrix(image), get_nbr_rows(image));
   destroy_pnm(image);
   fclose(fp);

   return perfect;
}

