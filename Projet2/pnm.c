/**
 * pnm.c
 *
 * Ce fichier contient les définitions de types et
 * les fonctions de manipulation d'images PNM.
 *
 * @author: El Masri Sam s190377
 * @date: 24/06/2021
 * @projet: INFO0030 Projet 1
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "pnm.h"

#define MAX_PIX 255
#define MAX_PIXC 65535
#define MAJ 32
#define MAX_PERFECTNBR 3

/**
 * Définition du type opaque PNM
 *
 */

struct PNM_t {

  char perfectNbr[MAX_PERFECTNBR];
  unsigned short nbrColumns;
  unsigned short nbrLines;
  unsigned short **matrix;
  unsigned short nbrMax;

};

int return_error_load (int x)
{
  switch (x)
  {
    case -1:
      printf("Cannot allocate enough memory\n");
      return -1;
      break;
    case -2:
      printf("The name of the input file is malformed\n");
      return -1;
      break;
    case -3:
      printf("The content of the input file is malformed\n");
      return -1;
      break;
    default:
    break;

  }
  return 0;
}

int strlengt(char* s)
{
  int l = 0;
  int i;
  for(i=0;s[i]!='\0';i++)
  {
    l++;
  }
  return l;
}

int format_compare(char *filename, char* format)
{
  char copyFilename[4];
  int l = strlengt(filename);
  //Convert letters to uppercase
  copyFilename[0] = filename[l-3]-MAJ;
  copyFilename[1] = filename[l-2]-MAJ;
  copyFilename[2] = filename[l-1]-MAJ;

  if(copyFilename[0] != format[0])
  {
    return -1;
  }
  if(copyFilename[1] != format[1])
  {
    return -1;
  }
  if(copyFilename[2] != format[2])
  {
    return -1;
  }
  return 0;

}

static void checkif_commentary (FILE *fp)
{
  assert(fp!=NULL);

  fseek(fp,+1,SEEK_CUR);
  int check = fgetc(fp);

  if(check == 10)//Line feed format
  {
    check = fgetc(fp);
  }

  if(check == '#')
  {
    fscanf(fp,"%*[^\n]\n");//Skip line
    //Place the value(s)
  }
  else
  {
    fseek(fp,-1,SEEK_CUR);//Go back
    //Place the value(s)
  }

}

static int fill_typePnm (char c[], FILE *fp)
{
  assert(c!=NULL && fp!=NULL);
  fscanf(fp,"%s",c);
  if(c[0] == '#')
  {
    return -3;
  }
  return 0;
}

static int check_typePnm (char c[])
{
  assert(c!=NULL);
  if(c[0]=='P')
  {
    switch (c[1])
    {
      case '1':
        return 0;
        break;
      case '2':
        return 0;
        break;
      case '3':
        return 0;
        break;
      default:
        return -3;
        break;
    }

  }
  else{
    return -3;
  }


}

static void fill_nbrColumnsLines(unsigned short *c, unsigned short *l, FILE *fp)
{
  assert(fp!=NULL);

  checkif_commentary(fp);
  fscanf(fp, "%hu %hu", &(*c),&(*l));

}

static int fill_nbrMax(FILE* fp)
{
  assert(fp!=NULL);
  unsigned short nbrMax;
  checkif_commentary(fp);
  fscanf(fp,"%hu",&nbrMax);

  return nbrMax;
}

static unsigned short **create_matrix(unsigned short lines, unsigned columns,char perfectNbr[])
{
  assert(lines>0 && columns>0 && perfectNbr!=NULL);
  unsigned short **matrix = malloc(sizeof(unsigned short*)*lines);
  if(matrix==NULL)
  return NULL;

  int i;
  for(i=0;i<lines;i++)
  {
    if(perfectNbr[1]=='3')
    {
      matrix[i] = malloc(sizeof(unsigned short)*(columns*3));
      if (matrix[i]==NULL)
      {
        int j;
        for(j=0;j<i;j++)
        {
          free(matrix[j]);
        }
        free(matrix);
        return NULL;
      }

    }
    else
    {
      matrix[i] = malloc(sizeof(unsigned short)*columns);
      if (matrix[i]==NULL)
      {
        int j;
        for(j=0;j<i;j++)
        {
          free(matrix[j]);
        }
        free(matrix);
        return NULL;
      }
    }
  }
  return matrix;

}

static void fill_matrix(unsigned short **matrix,unsigned short lines, unsigned short columns, FILE *fp, char* perfectNbr)
{
  assert(matrix!=NULL && lines >0 && columns>0 && fp!=NULL && perfectNbr!=NULL);
  int i,j;
  checkif_commentary(fp);
  for(i=0;i<lines;i++)
  {
    if(perfectNbr[1]=='3')
    {
      for(j=0;j<(columns*3);j++)
      {
        fscanf(fp,"%hu ",&matrix[i][j]);
      }

    }
    else
    {
      for(j=0;j<columns;j++)
      {
        fscanf(fp,"%hu ",&matrix[i][j]);
      }
    }
  }
}

static int check_matrix(unsigned short **matrix,int lines, int columns,char c[])
{
  assert(matrix!=NULL && lines >0 && columns>0 && c!=NULL);
  int i,j;
  for(i=0;i<lines;i++)
  {

    if(c[1] == '1')
    {
      for(j=0;j<columns;j++)
      {
        if((matrix[i][j] > 1))
        {
          return -3;
        }
      }
    }
  }
  return 0;
}

static void free_pnm(PNM *image) {
  if(image!=NULL)
  free(image);
}

static void free_matrix(unsigned short **matrix, int lines)
{
  assert(lines>0);
  
  if(matrix==NULL)
  return;

  int i;
  for(i=0;i<lines;i++)
  {
    if(matrix[i]!=NULL)
    free(matrix[i]);
  }
  free(matrix);

}

static void copy_file1(unsigned short **matrix, unsigned short l, unsigned short c, char *p, FILE* fp)
{
  assert(matrix!=NULL && l>0 && c>0 && p!=NULL && fp!=NULL);
  fprintf(fp,"%s\n",p);
  fprintf(fp,"%hu %hu\n",c,l);
  int i,j;
  for(i=0;i<l;i++)
  {
    for(j=0;j<c;j++)
    {
      fprintf(fp,"%hu ",matrix[i][j]);
    }
      fprintf(fp,"\n");
  }
}
static void copy_file2(unsigned short **matrix, unsigned short l, unsigned short c, char *p, int max, FILE* fp)
{
  assert(matrix!=NULL && l>0 && c>0 && p!=NULL && fp!=NULL);
  fprintf(fp,"%s\n",p);
  fprintf(fp,"%hu %hu\n",c,l);
  fprintf(fp,"%d\n",max);
  int i,j;
  for(i=0;i<l;i++)
  {
    for(j=0;j<c;j++)
    {
      fprintf(fp,"%hu ",matrix[i][j]);
    }
      fprintf(fp,"\n");
  }
}
static void copy_file3(unsigned short **matrix, unsigned short l, unsigned short c, char *p, int max, FILE* fp)
{
  assert(matrix!=NULL && l>0 && c>0 && p!=NULL && fp!=NULL);
  fprintf(fp,"%s\n",p);
  fprintf(fp,"%hu %hu\n",c,l);
  fprintf(fp,"%hu\n",max);
  int i,j;
  for(i=0;i<l;i++)
  {
    for(j=0;j<c*3;j++)
    {
      fprintf(fp,"%hu ",matrix[i][j]);
    }
      fprintf(fp,"\n");
  }
}

int load_pnm(PNM **image, char* filename)
{
  assert(image!=NULL && filename!=NULL);

//Create the PNM image
  (*image) = malloc(sizeof(PNM));
  if ((*image) == NULL)
  return -1;

//Open the file in "read" mode
  FILE *fp = fopen(filename,"r");
  if (fp == NULL)
    return -2;

//Read the perfect number from the file and put it in perfectNbr
  if(fill_typePnm((*image)->perfectNbr, fp)==-3)
    return -3;
  if(check_typePnm((*image)->perfectNbr)==-3){
    return -3;
  }
  char* perfectNbr = (*image)->perfectNbr;

//Read columns and lines from the file and put them in the fields
  fill_nbrColumnsLines(&(*image)->nbrColumns, &(*image)->nbrLines,fp);
  unsigned short nbrLines = (*image)->nbrLines;
  unsigned short nbrColumns = (*image)->nbrColumns;

//Read from the file the max number and put it in nbrMax
  if(perfectNbr[1]=='2' || perfectNbr[1] =='3')
  {
    (*image)->nbrMax = fill_nbrMax(fp);
    //int nbrMax = (*image)->nbrMax;

  }


//Create the matrix of the image variable
  (*image)->matrix =create_matrix(nbrLines, nbrColumns, perfectNbr);
  if((*image)->matrix == NULL)
  return -1;
  unsigned short** matrix = (*image)->matrix;

//Read from the file the data linked to the matrix, place them and check them
  fill_matrix(matrix, nbrLines, nbrColumns,fp, perfectNbr);
  if(check_matrix(matrix, nbrLines, nbrColumns,perfectNbr)==-3)
  return -3;

  fclose(fp);
  return 0;
}

PNM *create_image (void) {
  PNM *image = NULL;

  return image;
}

int get_lines (PNM *image){
  assert(image!=NULL);

  return image->nbrLines;
}

int get_columns (PNM *image){
  assert(image!=NULL);

  return image->nbrColumns;
}

unsigned short **get_matrix (PNM *image){
  assert(image!=NULL);

  return image->matrix;
}

PNM *set_matrix(PNM *image, unsigned short **matrix)
{
  assert(image!=NULL && matrix!=NULL);

  image->matrix = matrix;

  return image;
}

char *get_perfectNbr (PNM *image)
{
  assert(image!=NULL);

  return image->perfectNbr;
}


int write_pnm(PNM *image, char* filename)
{
  assert(image!=NULL && filename!=NULL);
  //Optimize variables
  unsigned short **matrix = image->matrix;
  unsigned short nbrLines = image->nbrLines;
  unsigned short nbrColumns = image->nbrColumns;
  char *perfectNbr = image->perfectNbr;
  unsigned short nbrMax = image->nbrMax;

  //Light check for basic_cipher
  if(nbrMax == MAX_PIX)
  {
    nbrMax = MAX_PIXC;
  }
  else
  {
    nbrMax = MAX_PIX;
  }
  //Open and write in the output file
  FILE* fp = fopen(filename,"w");
  if (fp==NULL)
  {
    free_matrix(matrix, nbrLines);
    free_pnm(image);
    return -1;
  }

  //Check what kind of PNM image we have and write in.
  switch(perfectNbr[1])
  {
    case '1':
      copy_file1(matrix,nbrLines,nbrColumns,perfectNbr,fp);
      break;
    case '2':
      copy_file2(matrix,nbrLines,nbrColumns,perfectNbr,nbrMax,fp);
      break;
    case '3':
      copy_file3(matrix,nbrLines,nbrColumns,perfectNbr,nbrMax,fp);
      break;
    default:
      break;
  }

  //Free all we done 
  free_matrix(matrix, nbrLines);
  free_pnm(image);

  fclose(fp);
  return 0;
}
