/* 
 * Fichier : couleurs.c
 * Auteur : Baptiste Rousselot, Camille Morfin
 * Description : Dans ce programme, on va stocker 100 couleurs et afficher les différentes couleurs avec leur nombres d'occurences
*/

#include <stdio.h>

#define NB_COULEUR 100

/* --- Structure de couleur --- */
struct Couleur
{
    int r;
    int g;
    int b;
    int a;
    int nb;
};

/* --- Vérifie si les couleurs sont égale ou non --- */
int est_egale(struct Couleur c1, struct Couleur c2) {
    return c1.r == c2.r && c1.g == c2.g && c1.b == c2.b && c1.a == c2.a;
}

int main() {
    /* --- Définition des variables --- */
    struct Couleur couleurs[NB_COULEUR];
    struct Couleur couleurs_count[NB_COULEUR];
    int nb_distinctes = 0;

    /* --- Définition des 5 couleurs de base --- */
    struct Couleur base[5] = {
        {255, 0, 0, 255},
        {0, 255, 0, 255},   
        {0, 0, 255, 255},   
        {255, 255, 0, 255}, 
        {0, 0, 0, 255}
    };
    
    /* --- Création des 100 couleurs --- */
    for (int i = 0; i < NB_COULEUR; i++) {
        couleurs[i] = base[i % 5];
    };

    /* --- Parcours du tableau de 100 couleurs --- */
    for (int i = 0; i < NB_COULEUR; i++) {
        //si la couleurs n'est pas dans couleur l'ajouter, sinon ajouter 1 à nb dans couleur_c
        int trouve = 0;
        for(int j = 0; j < nb_distinctes; j++){
            if(est_egale(couleurs[i], couleurs_count[j])) {
                couleurs_count[j].nb++;
                trouve = 1;
                break;
            }
        }
        if(!trouve) {
            couleurs_count[nb_distinctes] = couleurs[i];
            couleurs_count[nb_distinctes].nb = 1;
            nb_distinctes++;
        };
    }

    /* --- Afffichage des différentes couelurs avec leur nombre d'occurrence --- */
    printf("\nCouleurs distinctes\n");
    for (int i = 0; i < nb_distinctes; i++) {
        printf("\033[38;2;%d;%d;%dm", couleurs_count[i].r, couleurs_count[i].g, couleurs_count[i].b);
        printf("Couleur R=%d G=%d B=%d A=%d : %d fois\n", couleurs_count[i].r, couleurs_count[i].g, couleurs_count[i].b, couleurs_count[i].a, couleurs_count[i].nb);
        printf("\033[0m"); // Cela permet de mettre en couleur dans la console
    }

    return 0;
}