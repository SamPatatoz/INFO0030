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

//all typedef----------------------------------------------------------------------------------------------

typedef enum{pbm = 1, pgm = 2, ppm = 3}MagicNumber;
typedef enum{perfecto = 0, memoryProblem = -1, wrongInput = -2, malformedInput = -3}LoadErrors;
typedef enum{perfect = 0, wrongOutput = -1, failedSave = -2}WriteErrors;

struct PNM_t {
   MagicNumber magicNumber;
   unsigned int nbrColumns;
   unsigned int nbrRows;
   unsigned int maxValue;
   unsigned int **matrix;
};


//definition of constructor/destructor/getters/setters----------------------------------------------------

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


static PNM *set_max_value(PNM *pnm, unsigned int m) {
   assert(pnm != NULL);

   pnm->maxValue = m;

   return pnm;
}


//other functions-----------------------------------------------------------------------------------------

static void checkif_commentary (FILE *fp) {
  assert(fp != NULL);

  fseek(fp,+1,SEEK_CUR);
  int check = fgetc(fp);

  if(check == 10)//Line feed format
    check = fgetc(fp);

  if(check == '#')
    fscanf(fp,"%*[^\n]\n");//Skip line
    //Place the value(s)
  else {
    fseek(fp,-1,SEEK_CUR);//Go back
    //Place the value(s)
  }

}


static unsigned int **create_matrix (PNM *pnm) {
   assert(pnm != NULL);

   unsigned int r = get_nbr_rows(pnm);
   unsigned int c = get_nbr_columns(pnm);
   MagicNumber magic = get_magic_number(pnm);

   unsigned int **matrix = malloc(sizeof(unsigned int*)*r);
   if(matrix==NULL)
      return NULL;

   if(magic==ppm)
      c = 3*c;

   for(unsigned int i=0;i<r;i++) {

      matrix[i] = malloc(sizeof(unsigned int)*c);

      if (matrix[i]==NULL) {
         for(unsigned int j=0;j<i;j++) {
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

   for(unsigned int i=0;i<r;i++) {
      free(matrix[i]);
    }
    free(matrix);
}


int compare_format (char *format, char *filename) {
   assert(format != NULL && filename != NULL);

   const unsigned int MAX_LENGTH = 4;
   char copyFilename[MAX_LENGTH];
   int l = strlen(filename);

   //Convert letters to uppercase
   copyFilename[0] = filename[l-3]-MAJ;
   copyFilename[1] = filename[l-2]-MAJ;
   copyFilename[2] = filename[l-1]-MAJ;

   if(copyFilename[0] != format[0]) {
      return wrongInput;
   }
   if(copyFilename[1] != format[1]) {
      return wrongInput;
   }
   if(copyFilename[2] != format[2]) {
      return wrongInput;
   }

   return perfecto;
}




//functions to read in the pnm file----------------------------------------------------------------------------------

static int read_magic_number (FILE *fp, PNM *pnm) {
   assert(fp != NULL && pnm != NULL);

   char *str = malloc(sizeof(char)*3);
   if(str == NULL)
      return memoryProblem;

   fscanf(fp, "%s", str);
   unsigned int p = str[1]-'0';
   pnm = set_magic_number(pnm, p);

   free(str);

   return perfecto;
}


static void read_columns_rows (FILE *fp, PNM *pnm) {
   assert(fp != NULL && pnm != NULL);

   unsigned int c = 1, r = 1;
   fscanf(fp, "%u %u", &c, &r);
   pnm = set_nbr_columns(pnm, c), set_nbr_rows(pnm, r);
}


static void read_max_value (FILE* fp, PNM *pnm) {
   assert(fp != NULL && pnm != NULL);

   unsigned int maxValue = 0;
   fscanf(fp, "%u", &maxValue);
   pnm = set_max_value(pnm, maxValue);
}


static void read_matrix (FILE *fp, PNM *pnm) {
   assert(fp != NULL && pnm != NULL);

   unsigned r = get_nbr_rows(pnm);
   unsigned c = get_nbr_columns(pnm);
   MagicNumber magic = get_magic_number(pnm);
   unsigned int **matrix = get_matrix(pnm);

   if(magic == ppm)
      c = c*3;

   for(unsigned int i=0;i<r;i++) {
         for(unsigned int j=0;j<c;j++) {
            fscanf(fp,"%u ",&matrix[i][j]);
         }

   }
}


//load the initial pnm image------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------

int load_pnm(PNM **image, char* filename) {
   assert(image != NULL && filename != NULL);

   FILE *fp = fopen(filename, "r");
   if(fp == NULL)
      return wrongInput;

   if(create_pnm(image) == NULL)
      return memoryProblem;


   //read everything
   if(read_magic_number(fp, (*image)) == memoryProblem)
      return memoryProblem;

   checkif_commentary(fp);

   read_columns_rows(fp, (*image));

   checkif_commentary(fp);

   //check if pbm, if not => read the max value
   if(get_magic_number(*image) != pbm)
      read_max_value(fp, (*image));
      
   checkif_commentary(fp);

   (*image)->matrix = create_matrix((*image));
   read_matrix(fp, (*image));


   fclose(fp);

   return perfecto;
}




//functions to write in the pnm file----------------------------------------------------------------------

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

   unsigned r = get_nbr_rows(pnm);
   unsigned c = get_nbr_columns(pnm);
   MagicNumber magic = get_magic_number(pnm);
   unsigned int **matrix = get_matrix(pnm);

   if(magic == ppm)
         c = c * 3;

   for(unsigned int i=0;i<r;i++) {
      for(unsigned int j=0;j<c;j++) {
         fprintf(fp,"%u ", matrix[i][j]);
      }

      fprintf(fp, "\n");
   }
}


//write the new pnm image---------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------

int write_pnm(PNM *image, char* filename) {
   assert(image != NULL && filename != NULL);

   FILE *fp = fopen(filename, "w");
   if(fp == NULL)
      return failedSave;

   //write everything
   write_magic_number(fp, image);
   write_columns_rows(fp, image);

   if(get_magic_number(image) != pbm)
      write_max_value(fp, image);

   write_matrix(fp, image);

   //free all malloc
   destroy_matrix(get_matrix(image), get_nbr_rows(image));
   destroy_pnm(image);
   fclose(fp);

   return perfect;
}

