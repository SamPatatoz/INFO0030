/**
 * codebarre.c
 * 
 * This file contains type declarations and prototypes
 * functions for creating ULg barcodes.
 * 
 * @author: EL MASRI Sam s190377
 * @date: 23/03/2022
 * @projet: INFO0030 Projet 2
 */

//-------------------------Headers/Macros--------------------------------------
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <sys/dir.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include "codebarre.h"
#include "pnm.h"

#define ROWS 70
#define COLUMNS 70
#define TEN 10
#define ONE 1
#define LAST 60

//------------------------------Struct-----------------------------------------
//-----------------------------------------------------------------------------

//structure of the bar code
struct CODE_t {
    int registrationNumber;
    unsigned int *binary;
    unsigned int lengthBinary;
};

//--------basic definition of constructor/destructor/getters/setters-----------
//-----------------------------------------------------------------------------

CODE **create_bar_code (CODE **barCode) {
    assert(barCode != NULL);

    *barCode = malloc(sizeof(CODE));
    if(barCode == NULL)
        return NULL;

    return barCode;
}

void destroy_bar_code (CODE *barCode) {
    assert(barCode != NULL);

    free(barCode);
}

void destroy_binary (CODE *barCode) {
    assert(barCode->binary != NULL);

    free(barCode->binary);
}

int get_registration_number (CODE *barCode) {
    assert(barCode != NULL);

    return barCode->registrationNumber;
}

unsigned int *get_binary (CODE *barCode) {
    assert(barCode != NULL);
    
    return barCode->binary;
}

unsigned int get_length_binary (CODE *barCode) {
    assert(barCode != NULL);

    return barCode->lengthBinary;
}

CODE *set_registration_number (CODE *barCode, int registrationNumber) {
    assert(barCode != NULL);

    barCode->registrationNumber = registrationNumber;

    return barCode;
}


//----------------------------Make bar code------------------------------------
//-----------------------------------------------------------------------------

/**
 * @brief check if the registration number is good
 * 
 * @param barCode 
 * @param registration
 * @pre barCode != NULL, registration != NULL
 * 
 * @return int 
 */
static int check_registration_number (CODE *barCode, char *registration) {
    assert(barCode != NULL);
    //check of under 0
    if(get_registration_number(barCode) < 0) {
        return error;
    }

    //check the length
    if(strlen(registration) != 8) {
        return error;
    }

    //check if alpha case
    else {
        for(unsigned int i = 0; i < strlen(registration); i++) {
            if(isalpha(registration[i])) {
                return error;
            }
        }
    }

    return good;
}


/**
 * @brief Function to reverse a tab
 * 
 * @param tab 
 * @param length 
 * @pre tab != NULL
 */
static void reverse_tab (unsigned int *tab, unsigned int length) {
    assert(tab != NULL);

    unsigned int end = length - 1;
    char temp;

    for(unsigned int start = 0; start != end; start++) {
        temp = tab[start];
        tab[start] = tab[end];
        tab[end] = temp;

        end--;
    }
}


/**
 * @brief Function to fill the length/binary of the bar code
 *        and to convert a decimal (registration number) to reverse binary
 * 
 * @param barCode 
 * @pre barcode != NULL
 * 
 * @return int 
 */
static int dec_to_binary (CODE *barCode) {
    assert(barCode != NULL);

    int registrationNumber = barCode->registrationNumber;
    const unsigned int MAX_LENGTH = 30; 

    //calloc to set all values to zero
    barCode->binary = calloc(MAX_LENGTH, sizeof(int));
    if(barCode->binary == NULL)
        return memoryProblem;

    //to count the length of the binary number
    barCode->lengthBinary = 0;
    //set the binary number
    for(int i = 0; registrationNumber; i++) {
        barCode->lengthBinary++;
        if(registrationNumber % 2) {
            barCode->binary[i] = 1;
        }
        registrationNumber /= 2;

    }

    reverse_tab(barCode->binary, barCode->lengthBinary);

    return good;
}


/**
 * @brief fucntion to make the binary version of the registration number
 * 
 * @param barCode
 * @pre barCode != NULL
 * 
 * @return int 
 */
static int fill_bar_code (CODE *barCode) {
    assert(barCode != NULL);

    if(dec_to_binary(barCode) == memoryProblem) {
        destroy_bar_code(barCode);
        return memoryProblem;
    }

    return good;
}


/**
 * @brief make a 10x10 fill with 1 matrix
 * 
 * @param i 
 * @param j 
 * @param matrix 
 * @pre matrix != NULL, i >= 0, j >= 0
 */
void make_ten_by_ten_matrix (int i, int j, unsigned int **matrix) {
    assert(matrix != NULL && i >= 0 && j >= 0);

    //variables to set "i" and "j" to the their initial value
    unsigned int initialI = i;
    unsigned int initialJ = j;

    //fill 10x10 of 1
    for(unsigned int n = 0; n < TEN && i < ROWS; n++) {
        for(unsigned int m = 0; m < TEN && j < COLUMNS; m++) {
            matrix[i][j] = ONE;
            j++;
        }//end of "m" loop
        j = initialJ;
        i++;
    }//end of "n" loop
    i = initialI;
}


/**
 * @brief function to make the matrix (number/parity zone) of the pnm image
 * 
 * @param barCode 
 * @param matrix 
 * @pre barcode != NULL, matrix != NULL
 */
static int make_number_parity_zone (CODE *barCode, unsigned int **matrix) {
    assert(barCode != NULL && matrix != NULL);

    const unsigned int MAX_LENGTH = 6;
    unsigned int *binary = get_binary(barCode);
    int length = get_length_binary(barCode) - 1;
    //number of 1 in a row
    unsigned int countJ = 0;
    unsigned int countParity = 0;
    //tab for check the parity of the bottom side
    unsigned int *countI = calloc(MAX_LENGTH, sizeof(unsigned int));
    if(countI == NULL)
        return memoryProblem;
    unsigned int indexI = 0;
    
    //run through the 70x70 matrix whit jump of 10 by 10
    for(unsigned int i = 0; i < ROWS; i += TEN) {
        for(unsigned int j = 0; j < COLUMNS; j += TEN) {

            //if last "i" case => make bottom side parity
            if(i == LAST) {
                //if last columns make parity
                if(j == LAST) {
                    if(countParity % 2) {
                        make_ten_by_ten_matrix(i, j, matrix);
                    }
                }

                else if (j != LAST) {
                    if(countI[indexI] % 2) {
                        make_ten_by_ten_matrix(i, j, matrix);
                    }
                }
            }//end of condition

            //if last "j" case => make right side parity
            else if(j == LAST) {
                if((countJ % 2)) {
                    countParity++;
                    countJ = 0;
                    make_ten_by_ten_matrix(i, j, matrix);
                }
            }//end of condition

            //if 1 in the binary number => 10x10 of 1
            else if(binary[length] == ONE) {
                countI[indexI]++;
                countJ++;
                make_ten_by_ten_matrix(i, j, matrix);
                length--;
            }//end of condition

            else {
                if(length > 0)
                    length--;
            }
            indexI++;
        }//end of "j" loop

        indexI = 0;
    }//end of "i" loop

    free(countI);
    return good;
}


/**
 * @brief Create a calloc matrix object
 * 
 * @param matrix 
 * @return unsigned int** 
 */
static unsigned int **create_calloc_matrix (unsigned int **matrix) {
    //can be NULL

    matrix = calloc(ROWS, sizeof(unsigned int*));
    if(matrix == NULL) {
        return NULL;
    }

    for(unsigned int i = 0; i < ROWS; i++) {

        matrix[i] = calloc(COLUMNS, sizeof(unsigned int));
        //free all if error
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

//--------------------------------Main function--------------------------------
//-----------------------------------------------------------------------------

int complete_pnm (CODE *barCode, PNM **image, char *registration) {
    assert(barCode != NULL && image != NULL && registration != NULL);

    if(check_registration_number(barCode, registration) == error)
        return error;

    if(fill_bar_code(barCode) == memoryProblem)
        return memoryProblem;

    if(create_pnm(image) == NULL)
        return memoryProblem;

    //set all the data of the pnm image
    set_magic_number(*image, pbm);
    set_nbr_columns(*image, COLUMNS);
    set_nbr_rows(*image, ROWS);

    //create a matrix fill with 0
    unsigned int **matrix = NULL;
    matrix = create_calloc_matrix(matrix);
    if(matrix == NULL)
        return memoryProblem;

    //make the number zone of the bar code
    if(make_number_parity_zone(barCode, matrix) == memoryProblem) {
        destroy_binary(barCode);
        return memoryProblem;
    }

    set_matrix(*image, matrix);

    destroy_binary(barCode);
    return good;

}


//----------------------------------END----------------------------------------
//-----------------------------------------------------------------------------