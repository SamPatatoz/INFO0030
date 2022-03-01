/**
 * pnm.h
 * 
 * Ce fichier contient les déclarations de types et les prototypes
 * des fonctions pour la manipulation d'images PNM.
 * 
 * @author: EL MASRI Sam s190377
 * @date: 24/02/2022
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
 * @post: image points to the image loaded from file.
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

#endif // __PNM__

