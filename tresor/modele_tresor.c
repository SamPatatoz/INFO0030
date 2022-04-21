/**
 * modele_tresor.c
 * This file contains the type definitions and
 * the functions linked to the Modele part.
 * 
 * @author: EL MASRI Sam s190377
 * @date: 17/04/2022
 * @projet: INFO0030 Projet 3
 */


#include "modele_tresor.h"
#include "controleur_tresor.h"
#include <gtk/gtk.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

//-----------------------------------ALL---------------------------------------
//--------------------------------STRUCTURE(S)---------------------------------

struct MODELE_t {
    unsigned int nbrVictories;
    unsigned int nbrDefeats;
    CHEST rightChest;
};


//----------------------------STATIC-------------------------------------------
//---------------------------FUNCTIONS-----------------------------------------

/**
 * @brief generate a random number from 0 to 2
 *        the number will be the right chest (full chest)
 * 
 * @return unsigned int 
 */
static unsigned int choose_random_chest () {

    srand(time(NULL));
    unsigned int chest = rand() % 3;

    return chest;
}

//-----------------------------CREATE/DESTROY/SET/GET--------------------------
//----------------------------------FUNCTIONS----------------------------------

MODELE *create_modele (MODELE *pData) {
    pData = malloc(sizeof(MODELE));
    if(pData == NULL) {
        return NULL;
    }

    return pData;
}

void destroy_modele (MODELE *pData) {
    assert(pData != NULL);

    free(pData);
}

unsigned int get_nbrVictories (MODELE *pData) {
    assert(pData != NULL);

    return pData->nbrVictories;
}

unsigned int get_nbrDefeats (MODELE *pData) {
    assert(pData != NULL);

    return pData->nbrDefeats;
}

CHEST get_rightChest (MODELE *pData) {
    assert(pData != NULL);

    return pData->rightChest;
}

MODELE *set_nbrVictories (MODELE *pData, unsigned int x) {
    assert(pData != NULL);

    pData->nbrVictories = x;

    return pData;
}

MODELE *set_nbrDefeats (MODELE *pData, unsigned int x) {
    assert(pData != NULL);

    pData->nbrDefeats = x;

    return pData;
}

MODELE *set_rightChest (MODELE *pData, unsigned int x) {
    assert(pData != NULL);

    pData->rightChest = x;

    return pData;
}

MODELE *set_random_chest (MODELE *pData) {
    assert(pData != NULL);

    pData->rightChest = choose_random_chest();

    return pData;
}


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
