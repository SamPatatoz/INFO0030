/**
 * controleur_tresor.h
 * 
 * This file contains type definitions and prototypes
 * functions related to the Controller part.
 * 
 * @author: EL MASRI Sam s190377
 * @date: 17/04/2022
 * @projet: INFO0030 Projet 3
 */


#ifndef __CONTROLEUR__
#define __CONTROLEUR__

#include <gtk/gtk.h>
#include "modele_tresor.h"

#define COFFRE_FERME "coffre_ferme.jpg"
#define COFFRE_PLEIN "coffre_plein.jpg"
#define COFFRE_VIDE "coffre_vide.jpg"

/**
 * Declaration of the opaque type BUTTON
 * 
 */
typedef struct BUTTON_t BUTTON;


/**
 * create_button
 *
 * allocate and create the buttons and the modele, a pointer to BUTTON.
 *
 * @param pButtons a pointer to BUTTON.
 *
 * @pre: pButtons != NULL
 * @post: pButtons, a pointer to BUTTON is allocated and created
 *
 * @return:
 *      pButtons the BUTTON
 * 
 */
BUTTON *create_button (BUTTON *pButtons);


/**
 * destroy_button
 *
 * Free the memory of pButtons, a pointer to BUTTON.
 *
 * @param pButtons a pointer to BUTTON.
 *
 * @pre: pButtons != NULL
 * @post: pButtons, a pointer to BUTTON is free
 *
 * @return:
 * 
 */
void destroy_button (BUTTON *pButtons);


/**
 * create_labels
 *
 * create the labels in BUTTON and put them in the window
 *
 * @param pButtons a pointer to BUTTON.
 * @param pT a pointer to GtkWidget. (table)
 * @param pW a pointer to GtkWidget. (window)
 *
 * @pre: pButtons != NULL, pT != NULL, pW != NULL
 * @post: the labels are created and displayed in the window
 *
 * @return:
 *      pButtons, a pointer to BUTTON
 * 
 */
BUTTON *create_labels (BUTTON *pButtons, GtkWidget *pT, GtkWidget *pW);


/**
 * create_buttonRetry
 *
 * create the retry button of the window
 *
 * @param pButtons a pointer to BUTTON.
 * @param pTable a pointer to GtkWidget. (table)
 *
 * @pre: pButtons != NULL, pTable ! NULL
 * @post: the button retry is created and display in the window
 *
 * @return:
 *      pButtons, a pointer to BUTTON
 * 
 */
BUTTON *create_buttonRetry (BUTTON *pButtons, GtkWidget *pTable);


/**
 * create_buttons_chest
 *
 * create the chest buttons of the window
 *
 * @param pButtons a pointer to BUTTON.
 * @param pTable a pointer to GtkWidget. (table)
 * @param pData a pointer to MODELE
 *
 * @pre: pButtons != NULL, pTable != NULL, pData != NULL
 * @post: the chest buttons are created and displayed in the window
 *
 * @return:
 *      pButtons, a pointer to BUTTON
 * 
 */
BUTTON *create_buttons_chest (BUTTON *pButtons, GtkWidget *pTable, MODELE *pData);


/**
 * destroy_window
 *
 * CALLBACK to destroy the GTK window
 *
 * @param pW a pointer to GtkWidget.
 * @param data a gpointer
 *
 * @pre: /
 * @post: the window is destroyed
 *
 * @return:
 *      /
 * 
 */
void destroy_window (GtkWidget *pW, gpointer data);


/**
 * load_image_button
 *
 * function to load the images in the folder and display them (closed chest)
 *
 * @param image a pointer to char.
 *
 * @pre: char != NULL
 * @post: the closed chests are loaded and displayed
 *
 * @return:
 *      pButtons a GtkWidget
 * 
 */
GtkWidget *load_image_button (char *image);


/**
 * manage_buttons_signals
 *
 * Function to manage all the signals of the chest buttons.
 *
 * @param pButtons a pointer to BUTTON.
 *
 * @pre: pButtons != NULL
 * @post: the signals are set
 *
 * @return:
 *      pButtons a pointer to BUTTON
 * 
 */
BUTTON *manage_buttons_signals (BUTTON *pButtons);

#endif //__CONTROLEUR__
