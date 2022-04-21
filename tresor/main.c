#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "vue_tresor.h"
#include "controleur_tresor.h"
#include "modele_tresor.h"


int main (int argc, char **argv) {

    GtkWidget *pWindow;
    GtkWidget *pTable;
    BUTTON *pControleur;
    MODELE *pData;

    pControleur = create_button(pControleur);
    if(pControleur == NULL) {
        printf("!!! MEMORY PROBLEM !!!\n");
        exit(EXIT_FAILURE);
    }

    gtk_init(&argc, &argv);

    //create the window and the structure of widgets
    pWindow = create_window();
    pTable = gtk_table_new(4, 3, TRUE);

    //make and display the text
    pControleur = create_labels(pControleur, pTable, pWindow);
    //make and display the retry button
    pControleur = create_buttonRetry(pControleur, pTable);
    //make and display the chests
    pControleur = create_buttons_chest(pControleur, pTable, pData);
    //manage the signals of all the buttons
    pControleur = manage_buttons_signals(pControleur);

    gtk_container_add(GTK_CONTAINER(pWindow), GTK_WIDGET(pTable));
    gtk_widget_show_all(pWindow);

    gtk_main();

    destroy_button(pControleur);
    return EXIT_SUCCESS;
}
