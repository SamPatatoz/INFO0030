/**
 * codebarreCorrection.h
 * 
 * This file contains the function prototypes for handling barcode correction.
 * 
 * 
 * @author: EL MASRI Sam s190377
 * @date: 02/04/2022, le ramadan
 * @projet: INFO0030 Projet 2
 */


#ifndef __CODEBARRECORRECTION__
#define __CODEBARRECORRECTION__

typedef enum{numberError = - 1, parityError = - 2, cornerErrror = -3
}CorrectionError;



/**
 * correct_bar_code
 *
 * Correct bar code if there is an error
 *
 * @param barCodePNM a pointer to char.
 *
 * @pre: barCodePNM != NULL
 * @post: The bar code in the file is corrected
 *
 * @return: int
 * 
 */
int correct_bar_code (char *barCodePNM);


#endif