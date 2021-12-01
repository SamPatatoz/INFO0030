/**
 * pnm.h
 *
 * Ce fichier contient les déclarations de types et les prototypes
 * des fonctions pour la manipulation d'images PNM.
 *
 * @author: El Masri Sam s190377
 * @date: 24/06/2021
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
 * Charge une image PNM depuis un fichier.
 *
 * @param image l'adresse d'un pointeur sur PNM à laquelle écrire l'adresse
 *              de l'image chargée.
 * @param filename le chemin vers le fichier contenant l'image.
 *
 * @pre: image != NULL, filename != NULL
 * @post: image pointe vers l'image chargée depuis le fichier.
 *
 * @return:
 *     0 Succès
 *    -1 Erreur à l'allocation de mémoire
 *    -2 Nom du fichier malformé
 *    -3 Contenu du fichier malformé
 *
 */
int load_pnm(PNM **image, char* filename);

/**
 * write_pnm
 *
 * Sauvegarde une image PNM dans un fichier.
 *
 * @param image un pointeur sur PNM.
 * @param filename le chemin vers le fichier de destination.
 *
 * @pre: image != NULL, filename != NULL
 * @post: le fichier filename contient l'image PNM image.
 *
 * @return:
 *     0 Succès
 *    -1 Nom du fichier malformé
 *    -2 Erreur lors de la manipulation du fichier
 *
 */
int write_pnm(PNM *image, char* filename);

/**
 * return_error_load
 *
 * Prends en argument la valeur de retour de la fonction load_pnm et affiche
   l'erreur à l'écran.
 *
 * @param valeur de retour de load_pnm.
 *
 * @pre: /
 * @post: Affiche à l'écran le type d'erreur.
 *
 * @return:
 *    -1 Si erreur
 *
 */
int return_error_load (int x);

/**
 * format_compare
 *
 * Compare le format de l'option f et i.
 *
 * @param format entré dans l'option f.
 * @param filename le chemin vers le fichier de destination.
 *
 * @pre: filename != NULL, format != NULL
 * @post: Return -1 si les formats sont différents.
 *
 * @return:
 *     0 Formats similaires
 *    -1 Formats différents
 *
 */
int format_compare (char *filename, char* format);

/**
 * create_image
 *
 * Crée une image de type PNM
 *
 * @param /
 *
 * @pre: /
 * @post: Return une image de type PNM.
 *
 * @return:
 *     image
 *
 */
PNM *create_image (void);

/**
 * get_lines
 *
 * Obtenir la valeur de lignes
 *
 * @param image variable de type PNM
 *
 * @pre: image!=NULL
 * @post: Return valeur de lignes.
 *
 * @return:
 *     valeur de lignes
 *
 */
int get_lines (PNM *image);

/**
 * get_columns
 *
 * Obtenir la valeur de colonnes 
 *
 * @param image variable de type PNM
 *
 * @pre: image!=NULL
 * @post: Return valeur de colonnes.
 *
 * @return:
 *     valeur de colonnes
 *
 */
int get_columns (PNM *image);

/**
 * get_perfectNbr
 *
 * Obtenir le nombre parfait
 *
 * @param image variable de type PNM
 *
 * @pre: image!=NULL
 * @post: Return le nombre parfait en chaine de caractère.
 *
 * @return:
 *     Nombre parfait
 *
 */
char *get_perfectNbr (PNM *image);

/**
 * get_matrix
 *
 * Obtenir la matrice
 *
 * @param image variable de type PNM
 *
 * @pre: image!=NULL
 * @post: Return la matrice.
 *
 * @return:
 *     la matrice
 *
 */
unsigned short** get_matrix (PNM *image);

/**
 * set_matrix
 *
 * Modifier la matrice
 *
 * @param image variable de type PNM
 * @param matrix une matrice modèle
 * 
 * @pre: image!=NULL && matrix!=NULL
 * @post: Matrice modifié par la matrice modèle.
 *
 * @return:
 *     la variable image de type PNM
 *
 */
PNM *set_matrix(PNM *image, unsigned short **matrix);

/**
 * strlengt
 *
 * Donne la taille d'une chaine de caractère
 *
 * @param s chaine de caractère valide
 * 
 * @pre: s!=NULL
 * @post: La taille de la chaine de caractère est renvoyée
 *
 * @return:
 *     l longueur de la chaine de caractère
 *
 */
int strlengt(char* s);
#endif // __PNM__
