#include <stdio.h>
#include <stdlib.h>
#include <sys/dir.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include "codebarre.h"
#include "pnm.h"
#include "codebarreCorrection.h"

#define ROWS 70
#define COLUMNS 70
#define TEN 10
#define ONE 1
#define LAST 60


/**
 * @brief Create a matrix object
 * 
 * @param matrix 
 * @param rows 
 * @param columns 
 * @pre rows > 0, columns > 0
 * 
 * @return int 
 */
static int create_matrix (unsigned int **matrix, int rows, int columns) {
    assert(rows > 0 && columns > 0);

    matrix = malloc(sizeof(unsigned int*) * ROWS);
    if(matrix == NULL) {
        return memoryProblem;
    }

    for(unsigned int i = 0; i < ROWS; i++) {

        matrix[i] = malloc(sizeof(unsigned int) * COLUMNS);
        //free all if error
        if(matrix[i] == NULL) {

            for(unsigned int j = 0; j < i; j++) {
                free(matrix[j]);
            }

            free(matrix);
            return memoryProblem;
        }
    }

    return good;
}


/**
 * @brief make a 10x10 fill with 0 matrix
 * 
 * @param i 
 * @param j 
 * @param matrix 
 * @pre matrix != NULL, i >= 0, j >= 0
 */
static void make_ten_by_ten_matrix_zero (int i, int j, unsigned int **matrix) {
    assert(matrix != NULL && i >= 0 && j >= 0);

    //variables to set "i" and "j" to the their initial value
    unsigned int initialI = i;
    unsigned int initialJ = j;

    //fill 10x10 of 1
    for(unsigned int n = 0; n < TEN && i < ROWS; n++) {
        for(unsigned int m = 0; m < TEN && j < COLUMNS; m++) {
            matrix[i][j] = 0;
            j++;
        }//end of "m" loop
        j = initialJ;
        i++;
    }//end of "n" loop
    i = initialI;
}



/**
 * @brief First family of error :
 *        correct the number zone if there is an error
 * 
 * @param matrix 
 * @pre matrix != NULL
 * 
 * @return int 
 */
static int correct_number_zone (unsigned int **matrix) {
    assert(matrix != NULL);

    unsigned int countJ = 0;
    unsigned int errorCheck0 = 0;
    unsigned int errorCheck1 = 0;
    unsigned int errorPositionI = 0;
    unsigned int errorPositionJ = 0;
    const unsigned int MAX_LENGTH = 6;

    unsigned int *countI = calloc(MAX_LENGTH, sizeof(unsigned int));
    if(countI == NULL)
        return memoryProblem;
    unsigned int indexI = 0;

    //read the matrix and check if there is an error and correct it
    for(unsigned int i = 0; i < ROWS; i += TEN) {
        for(unsigned int j = 0; j < COLUMNS; j += TEN) {

            if(i == LAST) {
                if(countI[indexI] % 2) {
                    if(!(matrix[i][j])) {
                        errorCheck1 = 1;
                        errorPositionJ = j;
                    }
                }
                else {
                    if(matrix[i][j]) {
                        errorCheck0 = 1;
                        errorPositionJ = j;
                    }
                }
            }

            else if(j == LAST) {
                if(countJ % 2) {
                    if(!(matrix[i][j])) {
                        errorCheck1 = 1;
                        errorPositionI = i;
                    }
                }
                else {
                    if(matrix[i][j]) {
                        errorCheck0 = 1;
                        errorPositionI = i;
                    }
                }
            }

            else if(matrix[i][j] == 1) {
                countI[indexI]++;
                countJ++;
            }
            indexI++;
        }
        indexI = 0;
    }

    //check the type of error
    if(errorCheck1) {
        unsigned int i = errorPositionI;
        unsigned int j = errorPositionJ;
        make_ten_by_ten_matrix(i, j, matrix);
        free(countI);
        return numberError;
    }
    else if(errorCheck0) {
        unsigned int i = errorPositionI;
        unsigned int j = errorPositionJ;
        make_ten_by_ten_matrix_zero(i, j, matrix);
        free(countI);
        return numberError;
    }

    free(countI);
    return good;
}


/**
 * @brief Second family of error :
 *        function to check the right side parity
 * 
 * @param matrix 
 * @pre matrix != NULL
 * 
 * @return int 
 */
static int correct_right_columns (unsigned int **matrix) {
    assert(matrix != NULL);

    const unsigned int J = LAST;
    unsigned int countJ = 0;

    for(unsigned int i = 0; i < ROWS - TEN; i += TEN) {
            if(matrix[i][J] == 1) {
                countJ++;
            }
    }

    unsigned int cornerValue = matrix[LAST][LAST];


    if(cornerValue)  {
        if(!(countJ % 2)) {
            return cornerErrror;
        }
    }
    else {
        if(countJ % 2) {
            return cornerErrror;
        }
    }

    return good;
}

/**
 * @brief Third family of error :
 *        check and correct the right bottom corner of the bar code
 * 
 * @param barCodePNM 
 * @pre matrix != NULL
 * 
 * @return int 
 */
static int correct_corner (unsigned int **matrix) {
    assert(matrix != NULL);

    const unsigned int J = LAST;
    unsigned int countJ = 0;

    for(unsigned int i = 0; i < ROWS - TEN; i += TEN) {
            if(matrix[i][J] == 1) {
                countJ++;
            }
    }

    unsigned int cornerValue = matrix[LAST][LAST];

    if(cornerValue)  {
        if(!(countJ % 2)) {
            make_ten_by_ten_matrix_zero(LAST, LAST, matrix);
            return cornerErrror;
        }
    }
    else {
        if(countJ % 2) {
            make_ten_by_ten_matrix(LAST, LAST, matrix);
            return cornerErrror;
        }
    }

    return good;
}



int correct_bar_code (char *barCodePNM) {
    assert(barCodePNM != NULL);

    FILE *fp = fopen(barCodePNM, "r");
    if(fp == NULL) {
        return memoryProblem;
    }

    //go to the matrix in the file
    const unsigned int TO_MATRIX = 2;
    for(unsigned int i = 0; i < TO_MATRIX; i++) {
        fscanf(fp, "%*[^\n]\n");//Skip line;
    }

    //create a matrix
    unsigned int **matrix = NULL;

    if(create_matrix(matrix, ROWS, COLUMNS) == memoryProblem) {
        fclose(fp);
        return memoryProblem;
    }

    //read in the pnm matrix
    for(unsigned int i = 0; i < ROWS; i++) {
        for(unsigned int j = 0; j < COLUMNS; j++) {
            if(fscanf(fp,"%u ",&matrix[i][j]) == EOF) {
                destroy_matrix(matrix, ROWS);
                fclose(fp);
                return error;
            }
        }
    }

    //check/correct the number zone of the matrix
    switch (correct_number_zone(matrix)) {
    case memoryProblem:
        destroy_matrix(matrix, ROWS);
        return memoryProblem;
        break;
    case numberError:
        destroy_matrix(matrix, ROWS);
        return numberError;
        break;
    default:
        break;
    }

    //check/correct the right side column of the matrix
    if(correct_right_columns(matrix) == parityError) {
        return parityError;
    }

    //check/correct the right bottom corner of the matrix
    if(correct_corner(matrix) == cornerErrror) {
        return cornerErrror;
    }

    return good;
}