/* Fichier : cercle.c
   Auteur : Baptiste Rousselot, Camille Morfin
   Description : Ce programme calcule l'aire et le périmètre d'un cercle en fonction du rayon donné par l'utilisateur.
*/
#include <stdio.h>
#include <math.h>

double getAir(double rayon) {
    double air = rayon * rayon * M_PI;
    return air;
};

double getPerimetre(double rayon, double air) {
    double perimetre = 2 * rayon * M_PI;
    return perimetre;
}

int main() {
    /* --- Définition des variables --- */
    double rayon;
    double air;
    double perimetre;
    
    /* --- Récupération du rayon --- */
    printf("Veuillez saisir le rayon du cercle :\n ");
    scanf("%lf", &rayon);

    printf("Vous avez choisi le rayon %lf\n", rayon);

    /* --- Calcul de l'air --- */
    air = getAir(rayon);
    printf("L'air de votre cercle est %lf\n", air);

    /* --- Calcul du perimètre --- */
    perimetre = getPerimetre(rayon, air);
    printf("Le perimetre de votre cercle est %lf\n", perimetre);

    return 0;
};
