/**
 * modele_tresor.h
 * 
 * This file contains type definitions and prototypes
 * functions related to the Modele part.
 * 
 * @author: EL MASRI Sam s190377
 * @date: 17/04/2022
 * @projet: INFO0030 Projet 3
 */


#ifndef __MODELE__
#define __MODELE__

#include <gtk/gtk.h>

/**
 * Declaration of the opaque type BUTTON
 * 
 */
typedef struct MODELE_t MODELE;


/**
 * Declaration of the enum type CHEST
 * 
 */
typedef enum {chest0, chest1, chest2}CHEST;


/**
 * create_modele
 *
 * allocate and create the modele, a pointer to MODELE.
 *
 * @param pData a pointer to MODELE.
 *
 * @pre: /
 * @post: pData, a pointer to MODELE is allocated and created
 *
 * @return:
 *      pData the modele
 * 
 */
MODELE *create_modele (MODELE *pData);


/**
 * destroy_modele
 *
 * Free the memory of the modele, a pointer to MODELE.
 *
 * @param pData a pointer to MODELE.
 *
 * @pre: pData != NULL
 * @post: pData, a pointer to MODELE is free
 *
 * @return:
 * 
 */
void destroy_modele (MODELE *pData);


/**
 * get_nbrVictories
 *
 * get the number of victories of modele.
 *
 * @param pData a pointer to MODELE.
 *
 * @pre: pData != NULL
 * @post: the number of victories of the modele is returned.
 *
 * @return:
 *      unsigned int pData->nbrVivtories
 * 
 */
unsigned int get_nbrVictories (MODELE *pData);


/**
 * get_nbrDefeats
 *
 * get the number of defeats of modele.
 *
 * @param pData a pointer to MODELE.
 *
 * @pre: pData != NULL
 * @post: the number of defeats of the modele is returned.
 *
 * @return:
 *      unsigned int pData->nbrDefeats
 * 
 */
unsigned int get_nbrDefeats (MODELE *pData);


/**
 * get_rightChest
 *
 * get the right chest of the modele.
 *
 * @param pData a pointer to MODELE.
 *
 * @pre: pData != NULL
 * @post: the right chest of the modele is returned.
 *
 * @return:
 *      CHEST (int) pData->rightChest
 * 
 */
CHEST get_rightChest (MODELE *pData);


/**
 * set_nbrVictories
 *
 * set the number of victories of the modele.
 *
 * @param pData a pointer to MODELE.
 * @param x an usnigned int value for the number of victories
 *
 * @pre: pData != NULL
 * @post: the number of victories of the mdoele is set.
 *
 * @return:
 *      pData the modele a pointer to MODELE
 * 
 */
MODELE *set_nbrVictories (MODELE *pData, unsigned int x);


/**
 * set_nbrDefeats
 *
 * set the number of defeats of the modele.
 *
 * @param pData a pointer to MODELE.
 * @param x an usnigned int value for the number of defeats
 *
 * @pre: pData != NULL
 * @post: the number of victories of the mdoele is set.
 *
 * @return:
 *      pData the modele a pointer to MODELE
 * 
 */
MODELE *set_nbrDefeats (MODELE *pData, unsigned int x);


/**
 * set_rightChest
 *
 * set the right chest of the modele.
 *
 * @param pData a pointer to MODELE.
 * @param x an usnigned int value for the right chest
 *
 * @pre: pData != NULL
 * @post: the right chest (full chest) of the mdoele is set.
 *
 * @return:
 *      pData the modele a pointer to MODELE
 * 
 */
MODELE *set_rightChest (MODELE *pData, unsigned int x);


/**
 * set_random_chest
 *
 * set the right chest with a random value.
 *
 * @param pData a pointer to MODELE.
 *
 * @pre: pData != NULL
 * @post: the right chest (full chest) of the modele 
 *        is set with a random value.
 *
 * @return:
 *      pData the modele a pointer to MODELE
 * 
 */
MODELE *set_random_chest (MODELE *pData);


#endif //__MODELE__
