/**
 * controleur_tresor.c
 * This file contains the type definitions and
 * the functions linked to the Controller part.
 * 
 * @author: EL MASRI Sam s190377
 * @date: 17/04/2022
 * @projet: INFO0030 Projet 3
 */


#include "controleur_tresor.h"
#include "modele_tresor.h"
#include "vue_tresor.h"
#include <gtk/gtk.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

//-----------------------------------ALL---------------------------------------
//----------------------------------MACROS-------------------------------------

#define RETRY 0
#define FIRST_C 1
#define SECOND_C 2
#define THIRD_C 3

#define BUTTON0 0
#define BUTTON1 1
#define BUTTON2 2

#define NBR_LABEL 3
#define NBR_BUTTON 4

//-----------------------------------ALL---------------------------------------
//--------------------------------STRUCTURE(S)---------------------------------

struct BUTTON_t {
    GtkWidget *buttons[NBR_BUTTON];
    GtkWidget *pLabel[NBR_LABEL];
    GtkWidget *pTable;
    GtkWidget *pWindow;
    MODELE *pData;
    int nbrClicks;
    int isClicked[NBR_BUTTON-1];
};

//-----------------------------CREATE/DESTROY/SET------------------------------
//----------------------------------FUNCTIONS----------------------------------

BUTTON *create_button (BUTTON *pButtons) {
    assert(pButtons != NULL);
    pButtons = malloc(sizeof(BUTTON));
    if(pButtons == NULL)
        return NULL;

    pButtons->pData = create_modele(pButtons->pData);
    if(pButtons->pData == NULL)
        return NULL;

    return pButtons;
}

void destroy_button (BUTTON *pButtons) {
    assert(pButtons != NULL);

    destroy_modele(pButtons->pData);
    free(pButtons);
}

BUTTON *set_nbrClicks (BUTTON *pButtons, int x) {
    assert(pButtons != NULL && x >= 0);

    pButtons->nbrClicks = x;

    return pButtons;
}


//----------------------------STATIC-------------------------------------------
//---------------------------FUNCTIONS-----------------------------------------

/**
 * @brief CALLBACK when pressing the retry button
 * 
 * @param pWidget 
 * @param data 
 * 
 * @pre pWidget != NULL, data != NULL
 */
static void click_on_retry (GtkWidget *pWidget, gpointer data) {
    assert(pWidget != NULL && data != NULL);

    BUTTON *pButtons = (BUTTON *) data;

    draw_chest(pButtons->buttons[FIRST_C], COFFRE_FERME);
    draw_chest(pButtons->buttons[SECOND_C], COFFRE_FERME);
    draw_chest(pButtons->buttons[THIRD_C], COFFRE_FERME);

    gtk_widget_set_sensitive(pButtons->buttons[RETRY], FALSE);

    pButtons->nbrClicks = 0;
    pButtons->pData = set_random_chest(pButtons->pData);

    gtk_widget_destroy(pButtons->buttons[FIRST_C]);
    gtk_widget_destroy(pButtons->buttons[SECOND_C]);
    gtk_widget_destroy(pButtons->buttons[THIRD_C]);


    char text[MAX_INPUT] = "Choose a chest !";
    gtk_label_set_text(GTK_LABEL(pButtons->pLabel[2]), text);

    pButtons = create_buttons_chest
               (pButtons, pButtons->pTable, pButtons->pData);

    manage_buttons_signals(pButtons);

}


/**
 * @brief Increment a variable of BUTTON structure when the player lost
 *        and display the new score.
 * 
 * @param pButtons 
 * 
 * @pre pButtons != NULL
 * 
 * @return BUTTON* 
 */
static BUTTON *increment_nbrDefeats (BUTTON *pButtons) {
    assert(pButtons != NULL);

    int temp = get_nbrDefeats(pButtons->pData);
    temp++;
    pButtons->pData = set_nbrDefeats(pButtons->pData, temp);

    char message[MAX_INPUT];
    sprintf(message, "Defeats: %d", get_nbrDefeats(pButtons->pData));
    gtk_label_set_text(GTK_LABEL(pButtons->pLabel[1]), message);

    strcpy(message, "You lost !");

    gtk_label_set_text(GTK_LABEL(pButtons->pLabel[2]), message);

    return pButtons;
}


/**
 * @brief Increment a variable of BUTTON structure when the player won
 *        and display the new score.
 * 
 * @param pButtons 
 * 
 * @pre pButtons != NULL
 * 
 * @return BUTTON* 
 */
static BUTTON *increment_nbrVictories (BUTTON *pButtons) {
    assert(pButtons != NULL);

    int temp = get_nbrVictories(pButtons->pData);
    temp++;
    pButtons->pData = set_nbrVictories(pButtons->pData, temp);

    char message[MAX_INPUT];
    sprintf(message, "Victories: %d", get_nbrVictories(pButtons->pData));
    gtk_label_set_text(GTK_LABEL(pButtons->pLabel[0]), message);

    strcpy(message, "You won !");

    gtk_label_set_text(GTK_LABEL(pButtons->pLabel[2]), message);

    return pButtons;
}

/**
 * @brief CALLBACK when the player press a chest button.
 *        Increment a variable when the player press a chest button.
 * 
 * @param pWidget 
 * @param data 
 * 
 * @pre pWidget != NULL, data != NULL
 */
static void increment_nbrClicks (GtkWidget *pWidget, gpointer data) {
    assert(pWidget != NULL && data != NULL);

    BUTTON *pButtons = (BUTTON *) data;

    pButtons->nbrClicks++;

    gtk_widget_set_sensitive(pWidget, FALSE);

    const unsigned int MAX_CLICKS = 2;

    if(pButtons->nbrClicks == MAX_CLICKS) {
        gtk_widget_set_sensitive(pButtons->buttons[RETRY], TRUE);
        gtk_widget_set_sensitive(pButtons->buttons[FIRST_C], FALSE);
        gtk_widget_set_sensitive(pButtons->buttons[SECOND_C], FALSE);
        gtk_widget_set_sensitive(pButtons->buttons[THIRD_C], FALSE);

        pButtons = increment_nbrDefeats(pButtons);
    }
    
}

/**
 * @brief CALLBACK when the player choose the right chest(full chest)
 * 
 * @param currentButton 
 * @param data
 * 
 * @pre currentBouton != NULL, data != NULL 
 */
static void choose_right_chest (GtkWidget *currentButton, gpointer data) {
    assert(currentButton != NULL && data != NULL);

    BUTTON *pButtons = (BUTTON *) data;

    gtk_widget_set_sensitive(pButtons->buttons[RETRY], TRUE);
    gtk_widget_set_sensitive(pButtons->buttons[FIRST_C], FALSE);
    gtk_widget_set_sensitive(pButtons->buttons[SECOND_C], FALSE);
    gtk_widget_set_sensitive(pButtons->buttons[THIRD_C], FALSE);

    pButtons = increment_nbrVictories(pButtons);
    
}


//----------------------------GLOBAL-------------------------------------------
//---------------------------FUNCTIONS-----------------------------------------

void destroy_window (GtkWidget *pW, gpointer data) {

    gtk_main_quit();
}


BUTTON *create_labels (BUTTON *pButtons, GtkWidget *pT, GtkWidget *pW) {
    assert(pButtons != NULL && pT != NULL && pW != NULL);

    pButtons->pLabel[0] = gtk_label_new("Victories: 0");
    pButtons->pLabel[1] = gtk_label_new("Defeats: 0");
    pButtons->pLabel[2] = gtk_label_new("Choose a chest !");

    pButtons->pTable = pT;
    pButtons->pWindow = pW;

    gtk_table_attach(GTK_TABLE(pT), pButtons->pLabel[0], 
                     0, 2, 0, 1, GTK_EXPAND, GTK_EXPAND, 0, 0);
    gtk_table_attach(GTK_TABLE(pT), pButtons->pLabel[1],
                     1, 3, 0, 1, GTK_EXPAND, GTK_EXPAND, 0, 0);
    gtk_table_attach(GTK_TABLE(pT), pButtons->pLabel[2],
                     0, 3, 0, 2, GTK_EXPAND, GTK_EXPAND, 0, 0);

    pButtons->pData = set_nbrDefeats(pButtons->pData, 0);
    pButtons->pData = set_nbrVictories(pButtons->pData, 0);

    return pButtons;
}


BUTTON *create_buttonRetry (BUTTON *pButtons, GtkWidget *pTable) {
    assert(pButtons != NULL && pTable != NULL);

    pButtons->pData = set_random_chest(pButtons->pData);
    pButtons->buttons[RETRY] = gtk_button_new_with_label("Retry");
    pButtons = set_nbrClicks(pButtons, 0);

    gtk_table_attach(GTK_TABLE(pTable), pButtons->buttons[RETRY], 0, 3, 0, 3,
                     GTK_EXPAND | GTK_FILL, GTK_EXPAND, 0, 0);

    g_signal_connect(G_OBJECT (pButtons->buttons[RETRY]), "clicked", 
                     G_CALLBACK(click_on_retry), pButtons);
                     
    gtk_widget_set_sensitive(pButtons->buttons[RETRY], FALSE);

    return pButtons;
}


GtkWidget *load_image_button (char *image) {
    assert(image != NULL);

    GdkPixbuf *pbTemp = gdk_pixbuf_new_from_file(image, NULL);
    if(pbTemp == NULL) {
        printf("*.jpg not found !\n");
        exit(EXIT_FAILURE);
    }
    GdkPixbuf *pb = gdk_pixbuf_scale_simple(pbTemp, 100, 100, 
                                            GDK_INTERP_NEAREST);

    GtkWidget *pButton = gtk_button_new();

    GtkWidget *imageTemp = gtk_image_new_from_pixbuf(pb);
    gtk_button_set_image(GTK_BUTTON(pButton), imageTemp);

    return pButton;
}


BUTTON *create_buttons_chest (BUTTON *pButtons, GtkWidget *pTable, MODELE *pData) {
    assert(pButtons != NULL && pTable != NULL && pData != NULL);

    pButtons->buttons[FIRST_C] = load_image_button(COFFRE_FERME);

    pButtons->buttons[SECOND_C] = load_image_button(COFFRE_FERME);

    pButtons->buttons[THIRD_C] = load_image_button(COFFRE_FERME);


    return pButtons;
}


BUTTON *manage_buttons_signals (BUTTON *pButtons) {
    assert(pButtons != NULL);

    gtk_table_attach(GTK_TABLE(pButtons->pTable), 
                     pButtons->buttons[FIRST_C], 0, 1, 2, 4,
                     GTK_EXPAND | GTK_FILL, GTK_EXPAND, 10, 10);

    gtk_table_attach(GTK_TABLE(pButtons->pTable), 
                     pButtons->buttons[SECOND_C], 1, 2, 2, 4, 
                     GTK_EXPAND | GTK_FILL, GTK_EXPAND, 10, 10);

    gtk_table_attach(GTK_TABLE(pButtons->pTable), 
                     pButtons->buttons[THIRD_C], 2, 3, 2, 4,
                     GTK_EXPAND | GTK_FILL, GTK_EXPAND, 10, 10);

    unsigned int rightChest = get_rightChest(pButtons->pData);

    //choose the right chest and give it the "1" data for the callback
    switch (rightChest) {
    case BUTTON0:
        g_signal_connect(G_OBJECT(pButtons->buttons[FIRST_C]), "clicked", 
                         G_CALLBACK(change_chest), (gpointer) "1");
        g_signal_connect(G_OBJECT(pButtons->buttons[FIRST_C]), "clicked", 
                         G_CALLBACK(choose_right_chest), pButtons);
        g_signal_connect(G_OBJECT(pButtons->buttons[SECOND_C]), "clicked", 
                         G_CALLBACK(change_chest), (gpointer) "0");
        g_signal_connect(G_OBJECT(pButtons->buttons[THIRD_C]), "clicked", 
                         G_CALLBACK(change_chest), (gpointer) "0");

        g_signal_connect(G_OBJECT(pButtons->buttons[SECOND_C]), "clicked", 
                         G_CALLBACK(increment_nbrClicks), pButtons);
        g_signal_connect(G_OBJECT(pButtons->buttons[THIRD_C]), "clicked", 
                         G_CALLBACK(increment_nbrClicks), pButtons);

        break;
    case BUTTON1:
        g_signal_connect(G_OBJECT(pButtons->buttons[FIRST_C]), "clicked", 
                         G_CALLBACK(change_chest), (gpointer) "0");
        g_signal_connect(G_OBJECT(pButtons->buttons[SECOND_C]), "clicked", 
                         G_CALLBACK(change_chest), (gpointer) "1");
        g_signal_connect(G_OBJECT(pButtons->buttons[SECOND_C]), "clicked", 
                         G_CALLBACK(choose_right_chest), pButtons);
        g_signal_connect(G_OBJECT(pButtons->buttons[THIRD_C]), "clicked", 
                         G_CALLBACK(change_chest), (gpointer) "0");

        g_signal_connect(G_OBJECT(pButtons->buttons[THIRD_C]), "clicked", 
                         G_CALLBACK(increment_nbrClicks), pButtons);
        g_signal_connect(G_OBJECT(pButtons->buttons[FIRST_C]), "clicked", 
                         G_CALLBACK(increment_nbrClicks), pButtons);   

        break;
    case BUTTON2:
        g_signal_connect(G_OBJECT(pButtons->buttons[FIRST_C]), "clicked", 
                         G_CALLBACK(change_chest), (gpointer) "0");
        g_signal_connect(G_OBJECT(pButtons->buttons[SECOND_C]), "clicked", 
                         G_CALLBACK(change_chest), (gpointer) "0");
        g_signal_connect(G_OBJECT(pButtons->buttons[THIRD_C]), "clicked", 
                         G_CALLBACK(change_chest), (gpointer) "1");
        g_signal_connect(G_OBJECT(pButtons->buttons[THIRD_C]), "clicked", 
                         G_CALLBACK(choose_right_chest), pButtons);

        g_signal_connect(G_OBJECT(pButtons->buttons[FIRST_C]), "clicked", 
                         G_CALLBACK(increment_nbrClicks), pButtons);
        g_signal_connect(G_OBJECT(pButtons->buttons[SECOND_C]), "clicked", 
                         G_CALLBACK(increment_nbrClicks), pButtons);

        break;

    }
    
    gtk_widget_show_all(pButtons->pWindow);

    return pButtons;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
