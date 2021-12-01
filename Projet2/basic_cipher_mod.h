#ifndef __BASICCIPHER__
#define __BASICCIPHER__

/**
 * basic_cipher_mod.h
 *
 * Ce fichier contient le prototype
 * de la fonction pour la manipulation de chiffrement basique.
 *
 * @author: El Masri Sam s190377
 * @date: 16/07/2021
 * @projet: INFO0030 Projet 2
 */

/**
 * set_N
 *
 * Modifier la valeur de N
 *
 * @param seed la graine LFSR
 * @param tap le tap LFSR
 * @param l le nombre de lignes de la matrice
 * @param c le nombre de colonnes de la matrice
 * @param m la matrice à modifier
 * @param perfectNbr le nombre parfait de l'image PNM
 *
 * @pre: seed!=NULL && m!=NULL
 * @post: L'image PNM est chiffrée/déchiffrée.
 *
 * @return:
 *     /
 *
 */

void transformation (char *seed, unsigned short tap, unsigned short l, unsigned short c, unsigned short **m, char *perfectNbr);



#endif // __BASICCIPHER__