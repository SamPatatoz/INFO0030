#ifndef __LFSR__
#define __LFSR__


/**
 * LFSR.h
 *
 * Ce fichier contient les déclarations de types et les prototypes
 * des fonctions pour la manipulation de chiffrement.
 *
 * @author: El Masri Sam s190377
 * @date: 16/07/2021
 * @projet: INFO0030 Projet 2
 */

#include "pnm.h"

/**
 * Déclaration du type opaque LFSR
 *
 */
typedef struct LFSR_t LFSR;

/**
 * create_lfsr
 *
 * Crée un lfsr de type LFSR
 *
 * @param seed la graine
 * @param tap le tap pour les opérations XOR
 *
 * @pre: seed!=NULL
 * @post: Return un lfsr de type LFSR.
 *
 * @return:
 *     lfsr
 *
 */
LFSR *create_lfsr (char *seed, unsigned short tap);

/**
 * destroy_lfsr
 *
 * détruit un lfsr de type LFSR
 *
 * @param lfsr variable de type LFSR
 *
 * @pre: lfsr!=NULL
 * @post: Free lfsr de type LFSR.
 *
 * @return:
 *     /
 *
 */
void destroy_lfsr(LFSR *lfsr);

/**
 * get_N
 *
 * Obtenir la valeur de N
 *
 * @param lfsr variable de type LFSR
 *
 * @pre: lfsr!=NULL
 * @post: Return valeur de N.
 *
 * @return:
 *     N
 *
 */
int get_N(LFSR *lfsr);

/**
 * get_seed
 *
 * Obtenir la seed
 *
 * @param lfsr variable de type LFSR
 *
 * @pre: lfsr!=NULL
 * @post: Return la seed.
 *
 * @return:
 *     seed
 *
 */
char *get_seed(LFSR *lfsr);

/**
 * get_tap
 *
 * Obtenir la valeur de tap
 *
 * @param lfsr variable de type LFSR
 *
 * @pre: lfsr!=NULL
 * @post: Return valeur de tap.
 *
 * @return:
 *     tap
 *
 */
unsigned short get_tap(LFSR *lfsr);

/**
 * set_N
 *
 * Modifier la valeur de N
 *
 * @param lfsr variable de type LFSR
 * @param N la valeur modèle
 *
 * @pre: lfsr!=NULL
 * @post: La taille de la seed est modifié par N.
 *
 * @return:
 *     lfsr
 *
 */
LFSR *set_N(LFSR *lfsr, int N);

/**
 * set_tap
 *
 * Modifier la valeur de N
 *
 * @param lfsr variable de type LFSR
 * @param tap la valeur modèle
 *
 * @pre: lfsr!=NULL
 * @post: La valeur de tap LFSR est modifié par tap.
 *
 * @return:
 *     lfsr
 *
 */
LFSR *set_tap(LFSR *lfsr, unsigned short tap);

/**
 * set_seed
 *
 * Modifier la seed par la graine modèle
 *
 * @param lfsr variable de type LFSR
 * @param seed la graine modèle
 *
 * @pre: lfsr!=NULL && seed!=NULL
 * @post: La seed est modifié par la graine modèle.
 *
 * @return:
 *     lfsr
 *
 */
LFSR *set_seed(LFSR *lfsr, char *seed);

/**
 * string
 *
 * Cette fonctionnalité retourne
 * une chaîne de caractères représentant l’état actuel du registre après traitement.
 *
 * @param lfsr variable de type LFSR
 * @param r le registre actuel
 *
 * @pre: lfsr!=NULL && r!=NULL
 * @post: L'état du registre après modification
 *
 * @return:
 *     r
 *
 */
char *string(LFSR *lfsr, char *r);

/**
 * operation
 *
 * Il s’agit de simuler une opération sur le registre
 *
 * @param lfsr variable de type LFSR
 *
 * @pre: lfsr!=NULL
 * @post: le résultat de l'operation est renvoyé
 *
 * @return:
 *     bit
 *
 */
int operation(LFSR *lfsr);

/**
 * generation
 *
 * Il s’agit de simuler k opérations sur le registre et retourner une valeur entière
 *
 * @param lfsr variable de type LFSR
 * @param x nombre d'opération à faire
 *
 * @pre: lfsr!=NULL && x>0
 * @post: le résultat de la génération est renvoyé
 *
 * @return:
 *     resultat
 *
 */
int generation(LFSR *lfsr, int x);

/**
 * initialisation
 *
 *  L’initialisation a pour but de créer un Lfsr avec la graine et le tap initiaux
 *
 * @param seed la graine à donner au LFSR
 * @param tap tap à donner au LFSR
 *
 * @pre: seed!=NULL && tap>0
 * @post: une variable LFSR est renvoyé avec seed et tap inclus
 *
 * @return:
 *     lfsr
 *
 */
LFSR* initialisation (char* seed, unsigned short tap);
#endif // __LFSR__