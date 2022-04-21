/**
 * vue_tresor.c
 * This file contains the type definitions and
 * the functions linked to the View part.
 * 
 * @author: EL MASRI Sam s190377
 * @date: 17/04/2022
 * @projet: INFO0030 Projet 3
 */


#include <gtk/gtk.h>
#include <assert.h>
#include "vue_tresor.h"
#include "controleur_tresor.h"


//----------------------------GLOBAL-------------------------------------------
//---------------------------FUNCTIONS-----------------------------------------

GtkWidget *create_window () {
   GtkWidget *pW = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    //to destroy the window when press red button
    g_signal_connect(G_OBJECT(pW), "destroy",
                     G_CALLBACK(destroy_window), NULL);

    //set the title of the window
    gtk_window_set_title(GTK_WINDOW(pW), "Treasure Hunt");
    gtk_window_set_default_size(GTK_WINDOW(pW), 400, 200);

    return pW;
}


void draw_chest (GtkWidget *buttonChest, char *image) {
    assert(buttonChest != NULL && image != NULL);

    GdkPixbuf *pbTemp = gdk_pixbuf_new_from_file(image, NULL);
    if(pbTemp == NULL) {
    //    return NULL;
    }
    GdkPixbuf *pb = gdk_pixbuf_scale_simple(pbTemp, 100, 100, 
                                            GDK_INTERP_NEAREST);

    GtkWidget *imageTemp = gtk_image_new_from_pixbuf(pb);
    gtk_button_set_image(GTK_BUTTON(buttonChest), imageTemp);
}


void change_chest (GtkWidget *buttonChest, gpointer data) {
    assert(buttonChest != NULL && data != NULL);

    const unsigned int MAX_DATA = 2;
    char image[MAX_INPUT];
    char temp[MAX_DATA];
    
    strcpy(temp, (char *) data);
    
    if(temp[0] == '1') {
        strcpy(image, COFFRE_PLEIN);
    }
    else {
        strcpy(image, COFFRE_VIDE);

    }

    draw_chest(buttonChest, image);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
