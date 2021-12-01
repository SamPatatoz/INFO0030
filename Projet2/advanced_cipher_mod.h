#ifndef __ADVANCEDCIPHER__
#define __ADVANCEDCIPHER__

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
 * binary_to_seed
 *
 * Donne la graine à partir des caractères du mot de passe
 *
 * @param word le mot de passe
 *
 * @pre: word!=NULL
 * @post: Le mot de passe est converti en binaire
 *
 * @return:
 *     password la graine trouvée
 *
 */

char * binary_to_seed (char *word);

#endif // __ADVANCEDCIPHER__
