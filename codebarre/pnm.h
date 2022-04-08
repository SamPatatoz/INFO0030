/**
 * pnm.h
 * 
 * Ce fichier contient les déclarations de types et les prototypes
 * des fonctions pour la manipulation d'images PNM.
 * 
 * @author: EL MASRI Sam s190377
 * @date: 24/02/2022, la guerre
 * @projet: INFO0030 Projet 1
 */

/*
 * Include guard (pour éviter les problèmes d'inclusions multiplies
 * Bonne pratique: toujours encadrer un header avec un include guard
 */
#ifndef __PNM__
#define __PNM__

/**
 * Déclaration du type opaque PNM
 *
 */
typedef struct PNM_t PNM;

//Declaration of enum
typedef enum{pbm = 1, pgm = 2, ppm = 3}MagicNumber;

/**
 * load_pnm
 *
 * load an PNM image from a file.
 *
 * @param image the address of a pointer to PNM to which to write the address
 *              of the loaded image.
 * @param filename the path to the file containing the image.
 *
 * @pre: image != NULL, filename != NULL
 * @post: image points to the image loaded from file
 *
 * @return:
 *     0 Succes
 *    -1 Memory allocation error
 *    -2 Name of the file malformed
 *    -3 Content of the file malformed
 *
 */
int load_pnm(PNM **image, char* filename);

/**
 * write_pnm
 *
 * Save an PNM image in a file.
 *
 * @param image a pointer to PNM.
 * @param filename the path to the destination file.
 *
 * @pre: image != NULL, filename != NULL
 * @post: the file filename contains the image PNM image. 
 * 
 * @return:
 *     0 Succes
 *    -1 Name of the file malformed
 *    -2 Error while handling the file
 *
 */
int write_pnm(PNM *image, char* filename);

/**
 * compare_format
 *
 * Compare the format between de -f argument and -i/-o argument
 *
 * @param format the format given in the input.
 * @param inputFilename the path to the input file.
 * @param outputFilename the path to the output file.
 *
 * @pre: format != NULL, inputFilename != NULL, outputFilename != NULL
 * @post: the format and the two input and output extension are compared, with a specific return.
 *
 * @return:
 *      0 All extensions are good
 *     -1 Output extension not the same that the format
 *     -2 Input extension not the same that the format
 *
 */
int compare_format (char *format, char *inputFilename, char *outputFilename);

/**
 * check_magic_and_extension
 *
 * Compare the extension and the magic number
 *
 * @param pnm a pointer to PNM.
 * @param filename the path to the input file.
 *
 * @pre: pnm != NULL, filename != NULL
 * @post: the extension and the magic number are compared.
 *        If there is an error, the pnm image is free.
 *
 * @return:
 *      0 There is no problem
 *     -1 Mismatch between the extension and the magic number (pnm is free)
 *
 */
int check_magic_and_extension (PNM *pnm, char *filename);

/**
 * destroy_pnm
 *
 * Free the memory for the image, a pointer to PNM.
 *
 * @param pnm a pointer to PNM.
 *
 * @pre: pnm != NULL
 * @post: The image, a pointer to PNM is free
 *
 * @return:
 * 
 */
void destroy_pnm (PNM *pnm);

/**
 * create_pnm
 *
 * allocate and create the image, a double pointer to PNM.
 *
 * @param pnm a double pointer to PNM.
 *
 * @pre: pnm != NULL
 * @post: The image, a double pointer to PNM is allocated and created
 *
 * @return:
 *      pnm the image
 * 
 */
PNM **create_pnm (PNM **pnm);

/**
 * get_magic_number
 *
 * get the magic number of the pnm image.
 *
 * @param pnm a pointer to PNM.
 *
 * @pre: pnm != NULL
 * @post: the magic number of the image is returned.
 *
 * @return:
 *      pnm->magicNumber the magic number of the image
 * 
 */
MagicNumber get_magic_number (PNM *pnm);

/**
 * get_nbr_columns
 *
 * get the number of columns of the pnm image.
 *
 * @param pnm a pointer to PNM.
 *
 * @pre: pnm != NULL
 * @post: the number of columns of the image is returned.
 *
 * @return:
 *      pnm->nbrColumns the number of columns of the image
 * 
 */
unsigned int get_nbr_columns (PNM *pnm);

/**
 * get_nbr_rows
 *
 * get the number of rows of the pnm image.
 *
 * @param pnm a pointer to PNM.
 *
 * @pre: pnm != NULL
 * @post: the number of rows of the image is returned.
 *
 * @return:
 *      pnm->nbrRows the number of rows of the image
 * 
 */
unsigned int get_nbr_rows (PNM *pnm);

/**
 * get_max_value
 *
 * get the max value of the pnm image.
 *
 * @param pnm a pointer to PNM.
 *
 * @pre: pnm != NULL
 * @post: the max value of the image is returned.
 *
 * @return:
 *      pnm->maxValue the max value of the image
 * 
 */
unsigned int get_max_value(PNM *pnm);


/**
 * get_matrix
 *
 * get the matrix of the pnm image.
 *
 * @param pnm a pointer to PNM.
 *
 * @pre: pnm != NULL
 * @post: the matrix of the image is returned.
 *
 * @return:
 *      pnm->matrix the matrix of the image
 * 
 */
unsigned int **get_matrix (PNM *pnm);

/**
 * set_magic_number
 *
 * set the magic number of the pnm image.
 *
 * @param pnm a pointer to PNM.
 * @param magicNumber an int value for the magicNumber
 *
 * @pre: pnm != NULL
 * @post: the magic number of the image is set.
 *
 * @return:
 *      pnm the pnm image with the magic number set
 * 
 */
PNM *set_magic_number (PNM *pnm, int magicNumber);

/**
 * set_nbr_columns
 *
 * set the number of columns of the pnm image.
 *
 * @param pnm a pointer to PNM.
 * @param c an unsigned int value for the number of columns
 *
 * @pre: pnm != NULL
 * @post: the number of columns of the image is set.
 *
 * @return:
 *      pnm the pnm image with the number of columns set
 * 
 */
PNM *set_nbr_columns (PNM *pnm, unsigned int c);

/**
 * set_nbr_rows
 *
 * set the number of rows of the pnm image.
 *
 * @param pnm a pointer to PNM.
 * @param r an unsigned int value for the number of rows
 *
 * @pre: pnm != NULL
 * @post: the number of rows of the image is set.
 *
 * @return:
 *      pnm the pnm image with the number of rows set
 * 
 */
PNM *set_nbr_rows (PNM *pnm, unsigned int r);

/**
 * set_max_value
 *
 * set the max value of the pnm image.
 *
 * @param pnm a pointer to PNM.
 * @param m an unsigned int value for the max value
 *
 * @pre: pnm != NULL
 * @post: the max value of the image is set.
 *
 * @return:
 *      pnm the pnm image with the max value set
 * 
 */
PNM *set_max_value (PNM *pnm, unsigned int m);

/**
 * set_matrix
 *
 * set the matrix of the pnm image.
 *
 * @param pnm a pointer to PNM.
 * @param matrix an double pointer unsigned int value for the matrix
 *
 * @pre: pnm != NULL
 * @post: the matrix of the image is set.
 *
 * @return:
 *      pnm the pnm image with the matrix set
 * 
 */
PNM *set_matrix (PNM *pnm, unsigned int **matrix);

/**
 * destroy_matrix
 *
 * free the matrix of the pnm image.
 *
 * @param matrix an double pointer unsigned int value for the matrix
 * @param r unsigned int value for the number of rows
 *
 * @pre: matrix != NULL
 * @post: the matrix of the image is free.
 *
 * @return:
 *      /
 * 
 */
void destroy_matrix (unsigned int **matrix ,unsigned int r);

#endif // __PNM__

