/**
 * codebarre.h
 * 
 * This file contains type declarations and prototypes
 * functions for creating ULg barcodes.
 * 
 * @author: EL MASRI Sam s190377
 * @date: 23/03/2022, la fatigue
 * @projet: INFO0030 Projet 2
 */


#ifndef __CODEBARRE__
#define __CODEBARRE__

#include "pnm.h"

typedef struct CODE_t CODE;

//enum for return value of the bar code fucntions
typedef enum {good, memoryProblem, malformedInput, error} state;


/**
 * create_bar_code
 *
 * allocate and create the bar code, a double pointer to CODE.
 *
 * @param barCode a double pointer to PNM.
 *
 * @pre: barCode != NULL
 * @post: The bar code, a double pointer to CODE is allocated and created
 *
 * @return:
 *      barCode the image
 * 
 */
CODE **create_bar_code (CODE **barCode);

/**
 * destroy_bar_code
 *
 * Free the memory for the bar code, a pointer to CODE.
 *
 * @param barCode a pointer to PNM.
 *
 * @pre: barCode != NULL
 * @post: The bar code, a pointer to CODE is free
 *
 * @return:
 * 
 */
void destroy_bar_code (CODE *barCode);

/**
 * destroy_binary
 *
 * Free the memory for the binary of the bar code, a pointer to CODE.
 *
 * @param barCode a pointer to CODE.
 *
 * @pre: barCode != NULL
 * @post: The binary of the bar code, a pointer to CODE is free
 *
 * @return:
 * 
 */
void destroy_binary (CODE *barCode);

/**
 * get_registration_number
 *
 * get the registration number of the bar code.
 *
 * @param barCode a pointer to CODE.
 *
 * @pre: barCode != NULL
 * @post: the registration number of the bar code is returned.
 *
 * @return:
 *      barCode->registrationNumber the registration number of the bar code
 * 
 */
int get_registration_number (CODE *barCode);

/**
 * get_binary
 *
 * get the binary of the bar code.
 *
 * @param barCode a pointer to CODE.
 *
 * @pre: barCode != NULL
 * @post: the binary of the bar code is returned.
 *
 * @return:
 *      barCode->binary the binary of the bar code
 * 
 */
unsigned int *get_binary (CODE *barCode);

/**
 * get_length_binary
 *
 * get the length of the binary of the bar code.
 *
 * @param barCode a pointer to CODE.
 *
 * @pre: barCode != NULL
 * @post: the length of the binary of the bar code is returned.
 *
 * @return:
 *      barCode->lengthBinary the length of the binary of the bar code
 * 
 */
unsigned int get_length_binary (CODE *barCode);

/**
 * set_registration_number
 *
 * set the registration number of the bar code.
 *
 * @param barCode a pointer to CODE.
 * @param registrationNumber int value for the registration number.
 *
 * @pre: barCode != NULL
 *
 * @return:
 *      barCode the bar code with the registration number set
 * 
 */
CODE *set_registration_number (CODE *barCode, int registrationNumber);

/**
 * complete_pnm
 *
 * complete the pnm image with the data from the bar code
 *
 * @param barCode a pointer to CODE.
 * @param image a double pointer to PNM.
 *
 * @pre: barCode != NULL, image != NULL, registration != NULL
 *
 * @return:
 *      int state of the function
 * 
 */
int complete_pnm (CODE *barCode, PNM **image, char *registration);


/**
 * make_ten_by_ten_matrix
 *
 * make ten by ten matrix fill with 1
 *
 * @param i int.
 * @param j int.
 * @param matrix double pointer to unsigned int
 *
 * @pre: i > 0, j > 0, matrix != NULL
 *
 * 
 */
void make_ten_by_ten_matrix (int i, int j, unsigned int **matrix);


#endif // __CODEBARRE__
