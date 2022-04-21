/**
 * vue_tresor.h
 * 
 * This file contains type definitions and prototypes
 * functions related to the View part.
 * 
 * @author: EL MASRI Sam s190377
 * @date: 17/04/2022
 * @projet: INFO0030 Projet 3
 */

#ifndef __VUE__
#define __VUE__

#include <gtk/gtk.h>

/**
 * create_window
 *
 * create the window with GTK+
 *
 * @post: the window is created and the widget window is returned
 *
 * @return:
 *      pW the window widget
 *
 */
GtkWidget *create_window ();


/**
 * change_chest
 *
 * Callback when a chest is clicked
 * update the image of the chest
 *
 * @param buttonChest a widget, a button.
 * @param data data to pass in argument (gpointer).
 *
 * @pre: buttonChest != NULL, data != NULL
 * @post: the image of the chest is changed.
 *
 * @return: /
 *
 */
void change_chest (GtkWidget *buttonChest, gpointer data);


/**
 * draw_chest
 *
 * function to load draw an image
 *
 * @param buttonChest a widget, a button.
 * @param image the image in the folder.
 *
 * @pre: buttonChest != NULL, image != NULL
 * @post: the image of the widget is changed.
 *
 * @return: /
 *
 */
void draw_chest (GtkWidget *buttonChest, char *image);

#endif //__VUE__
