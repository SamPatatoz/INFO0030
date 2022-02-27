/**
 * pnm.h
 * 
 * Ce fichier contient les déclarations de types et les prototypes
 * des fonctions pour la manipulation d'images PNM.
 * 
 * @author: EL MASRI Sam s190377
 * @date: 24/02/2022
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
 * compare_format
 *
 * Compare the format between de -f argument and -i argument
 *
 * @param format the format given in the input.
 * @param inputFilename the path to the input file.
 * @param outputFilename the path to the output file.
 *
 * @pre: format != NULL, inputFilename != NULL, outputFilename != NULL
 * @post: the format and the two input and output extension are compared with a specific return.
 *
 * @return:
 *      0 All format are good
 *     -1 Output extension not the same that the format
 *     -2 Input extension not the same that the format
 *
 */
int compare_format (char *format, char *inputFilename, char *outputFilename);

#endif // __PNM__

