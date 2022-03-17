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
#include <ctype.h>

#include "pnm.h"


#define PPM_COLUMNS 3
#define PBM_MAX_VALUE 1 
#define PGM_MAX_VALUE 255
#define PPM_MAX_VALUE 65536




//all typedef------------------------------------------------------------------

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




//basic definition of constructor/destructor/getters/setters-------------------


PNM **create_pnm (PNM **pnm) {
   assert(pnm != NULL);

   *pnm = malloc(sizeof(PNM));
   if(pnm == NULL)
      return NULL;

   return pnm;
}


void destroy_pnm (PNM *pnm) {
   assert(pnm != NULL);

   free(pnm);
}


MagicNumber get_magic_number (PNM *pnm) {
   assert(pnm != NULL);

   return pnm->magicNumber;
}


unsigned int get_nbr_columns (PNM *pnm) {
   assert(pnm != NULL);

   return pnm->nbrColumns;
}


unsigned int get_nbr_rows (PNM *pnm) {
   assert(pnm != NULL);

   return pnm->nbrRows;
}


unsigned int get_max_value(PNM *pnm) {
   assert(pnm != NULL);

   return pnm->maxValue;
}


unsigned int **get_matrix (PNM *pnm) {
   assert(pnm != NULL);

   return pnm->matrix;
}


PNM *set_magic_number (PNM *pnm, int magicNumber) {
   assert(pnm != NULL);

   pnm->magicNumber = magicNumber;

   return pnm;
}


PNM *set_nbr_columns (PNM *pnm, unsigned int c) {
   assert(pnm != NULL);

   pnm->nbrColumns = c;

   return pnm;
}


PNM *set_nbr_rows (PNM *pnm, unsigned int r) {
   assert(pnm != NULL);

   pnm->nbrRows = r;

   return pnm;
}


PNM *set_max_value (PNM *pnm, unsigned int m) {
   assert(pnm != NULL);

   pnm->maxValue = m;

   return pnm;
}

PNM *set_matrix (PNM *pnm, unsigned int **matrix) {
   assert(pnm != NULL);

   pnm->matrix = matrix;

   return pnm;
}




//other functions--------------------------------------------------------------


//check a line to pass a line if there is a commentary 
static void checkif_commentary (FILE *fp) {
   assert(fp != NULL);

   const unsigned int LF = 10;

   fseek(fp, +1, SEEK_CUR);
   unsigned int check = fgetc(fp);

   if(check == LF)//Line feed format
      check = fgetc(fp);

   if(check == '#')
      fscanf(fp, "%*[^\n]\n");//Skip line
      //Place the value(s)
   else {
      fseek(fp, -1, SEEK_CUR);//Go back
      //Place the value(s)
   }

}

//create a matrix for the pnm image
static unsigned int **create_matrix (PNM *pnm) {
   assert(pnm != NULL);

   unsigned int rows = get_nbr_rows(pnm);
   unsigned int columns = get_nbr_columns(pnm);
   MagicNumber magic = get_magic_number(pnm);

   unsigned int **matrix = malloc(sizeof(unsigned int*) * rows);
   if(matrix == NULL)
      return NULL;

   if(magic == ppm)
      columns = columns * PPM_COLUMNS;

   for(unsigned int i = 0; i < rows; i++) {

      matrix[i] = malloc(sizeof(unsigned int) * columns);

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

//destroy the matrix of the pnm structure
static void destroy_matrix (unsigned int **matrix ,unsigned int r) {
   assert(matrix != NULL);

   for(unsigned int i = 0; i < r; i++) {
      free(matrix[i]);
    }
    free(matrix);
}

//check the input format. If problem => return an error
static int check_format (char *format) {
   assert(format != NULL);

   const unsigned int FORMAT_LENGTH = 3;
   //check format length
   if(strlen(format) != FORMAT_LENGTH)
      return wrongInput;

   const unsigned int FIRST = 0;
   const unsigned int SECOND = 1;
   const unsigned int THIRD = 2;

   //check first letter
   if(format[FIRST] != 'P')
      return wrongInput;
   
   //check second letter
   switch (format[SECOND])
   {
   case 'B':
      break;
   case 'G':
      break;
   case 'P':
      break;
   default:
      return wrongInput;
      break;
   }

   //check third letter
   if(format[THIRD] != 'M')
      return wrongInput;

   return perfect;
}
//compare the format between all the input file's extension
int compare_format (char *format, char *inputFilename, char *outputFilename) {
   assert(format != NULL && inputFilename != NULL && outputFilename != NULL);

   //check the format length and composition
   if(check_format(format) == wrongInput)
      return wrongInput;

   const unsigned int MAX_LENGTH = 4;

   char copyInputFilename[MAX_LENGTH];
   char copyOutputFilename[MAX_LENGTH];  

   unsigned int inputLength = strlen(inputFilename);
   unsigned int outputLength = strlen(outputFilename);

   unsigned int x = 3;
   for(unsigned int i = 0; i < MAX_LENGTH - 1; i++) {

      //check input filename extension
      copyInputFilename[i] = toupper(inputFilename[inputLength - x]);
      if(copyInputFilename[i] != format[i]) {
         return wrongInput;
      }

      //check output filename extension      
      copyOutputFilename[i] = toupper(outputFilename[outputLength - x]);
      if(copyOutputFilename[i] != format[i]) {
         return wrongOutput;
      }

      x--;
   }

   return perfecto;
}

//a check between the magic number and the extension of the input filename
int check_magic_and_extension (PNM *pnm, char *filename) {
   assert(pnm != NULL && filename != NULL);

   const int mismatch = -1;
   const int noProblem = 0;
   const unsigned int TWO = 2;

   unsigned int strlength = strlen(filename);
   //take the second letter of the extension => b || g || p
   unsigned int letter = filename[strlength - TWO];

   switch (pnm->magicNumber) {
   case 1:
      if(letter != 'b') {
         destroy_matrix(pnm->matrix, pnm->nbrRows);
         destroy_pnm(pnm);
         return mismatch;
      }
      break;
   case 2:
      if(letter != 'g') {
         destroy_matrix(pnm->matrix, pnm->nbrRows);
         destroy_pnm(pnm);
         return mismatch;
      }
      break;
   case 3:
      if(letter != 'p') {
         destroy_matrix(pnm->matrix, pnm->nbrRows);
         destroy_pnm(pnm);
         return mismatch;
      }
      break;
   default:
      return noProblem;
      break;
   }
   return noProblem;
}




//functions to read in the pnm file--------------------------------------------

//read the magic number and save the data in the pnm structure
static int read_magic_number (FILE *fp, PNM *pnm) {
   assert(fp != NULL && pnm != NULL);

   const unsigned int MAX_LENGTH = 3;
   char *str = malloc(sizeof(char) * MAX_LENGTH);
   if(str == NULL)
      return memoryProblem;

   if(fscanf(fp, "%s", str) == EOF) {
      free(str);
      return malformedInput;
   }
   
   if(str[0] != 'P') {
      free(str);
      return malformedInput;
   }   
   //take the second symbol and typecast to int
   unsigned int p = str[1] - '0';

   //check for malformed magic number
   if(p != 1 && p != 2 && p!= 3) {
      free(str);
      return malformedInput;
   }

   else {
      set_magic_number(pnm, p);
   }

   free(str);

   return perfecto;
}

//read the columns and the rows and save them in the pnm structure
static int read_columns_rows (FILE *fp, PNM *pnm) {
   assert(fp != NULL && pnm != NULL);

   unsigned int c = 1, r = 1;
   if(fscanf(fp, "%u %u", &c, &r) == EOF) {
      return malformedInput;
   }

   set_nbr_columns(pnm, c);
   if(get_nbr_columns(pnm) == 0)
      return malformedInput;

   set_nbr_rows(pnm, r);
   if(get_nbr_rows(pnm) == 0)
      return malformedInput;

   return perfecto;
}

//read the max value and save it in the pnm structure
static int read_max_value (FILE* fp, PNM *pnm) {
   assert(fp != NULL && pnm != NULL);

   unsigned int maxValue = 0;
   if(fscanf(fp, "%u", &maxValue) == EOF) {
      return malformedInput;
   }

   if(get_magic_number(pnm) == pgm) {
      if(maxValue > PGM_MAX_VALUE)
         return malformedInput;
   }
   else {
      if(maxValue > PPM_MAX_VALUE)
         return malformedInput;
   }

   set_max_value(pnm, maxValue);

   return perfecto;
}

//read the matrix and save it in the pnm structure
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
            if(fscanf(fp,"%u ",&matrix[i][j]) == EOF) {
               destroy_matrix(matrix, rows);
               return malformedInput;
            }

            //check for malformed matrix
            if(magic == ppm || magic == pgm) {
               if(matrix[i][j] > PGM_MAX_VALUE) {
                  destroy_matrix(matrix, rows);
                  return malformedInput;
               }   
            }
            else {
               if(matrix[i][j] > PBM_MAX_VALUE) {
                  destroy_matrix(matrix, rows);
                  return malformedInput;
               }   
            }
         }

   }

   return perfecto;
}




//load the initial pnm image---------------------------------------------------
//-----------------------------------------------------------------------------

int load_pnm (PNM **image, char* filename) {
   assert(image != NULL && filename != NULL);

   FILE *fp = fopen(filename, "r");
   if(fp == NULL)
      return wrongInput;

   if(create_pnm(image) == NULL) {
      fclose(fp);
      return memoryProblem;
   }

   //read everything

   //check for error return
   int checkMagicNumber = read_magic_number(fp, (*image));
   if(checkMagicNumber == malformedInput) {
      destroy_pnm(*image);
      fclose(fp);
      return malformedInput;
   }

   else if(checkMagicNumber == memoryProblem) {
      destroy_pnm(*image);
      fclose(fp);
      return memoryProblem;
   }


   checkif_commentary(fp);

   if(read_columns_rows(fp, (*image)) == malformedInput) {
      destroy_pnm(*image);
      fclose(fp);
      return malformedInput;
   }

   checkif_commentary(fp);


   //check if pbm, if not => read the max value
   if(get_magic_number(*image) != pbm) {
      if(read_max_value(fp, (*image)) == malformedInput) {
         destroy_pnm(*image);
         fclose(fp);
         return malformedInput;
      }
   }
   

   set_matrix(*image, create_matrix(*image));
   if(get_matrix(*image) == NULL) {
      destroy_pnm(*image);
      fclose(fp);
      return memoryProblem;
   }
      
   if(read_matrix(fp, (*image)) == malformedInput) {
      destroy_pnm(*image);
      fclose(fp);
      return malformedInput;
   }


   fclose(fp);

   return perfecto;
}




//functions to write in the pnm file-------------------------------------------

//write the magic number in the output file
static void write_magic_number (FILE *fp, PNM *pnm) {
   assert(fp != NULL && pnm != NULL);

   fprintf(fp, "P%d\n", get_magic_number(pnm));
}

//write the number of coumns and rows in the output file
static void write_columns_rows (FILE *fp, PNM *pnm) {
   assert(fp != NULL && pnm != NULL);

   fprintf(fp, "%u %u\n", get_nbr_columns(pnm), get_nbr_rows(pnm));
}

//write the max value in the output file
static void write_max_value (FILE *fp, PNM *pnm) {
   assert(fp != NULL && pnm != NULL);

   fprintf(fp, "%u\n", get_max_value(pnm));
}

//write the matrix in the output file
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

//take the output filename to check if forbidden character
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

int write_pnm (PNM *image, char* filename) {
   assert(image != NULL && filename != NULL);

   if(check_output_filename(filename) == wrongOutput) {
      destroy_matrix(get_matrix(image), get_nbr_rows(image));
      return wrongOutput;
   }

   FILE *fp = fopen(filename, "w");
   if(fp == NULL) {
      destroy_matrix(get_matrix(image), get_nbr_rows(image));
      return failedSave;
   }

   //write everything
   write_magic_number(fp, image);

   write_columns_rows(fp, image);

   if(get_magic_number(image) != pbm)
      write_max_value(fp, image);

   write_matrix(fp, image);


   //free all memory
   destroy_matrix(get_matrix(image), get_nbr_rows(image));
   fclose(fp);

   return perfect;
}