// #include <stdio.h>

#define NB_COULEUR 100

struct Couleur
{
    int r;
    int g;
    int b;
    int a;
    int nb;
};

int est_egale(struct Couleur c1, struct Couleur c2) {
    return c1.r == c2.r && c1.g == c2.g && c1.b == c2.b && c1.a == c2.a;
}

int main() {
    struct Couleur couleurs[NB_COULEUR];
    struct Couleur couleurs_count[NB_COULEUR];
    int nb_distinctes = 0;

    struct Couleur base[5] = {
        {255, 0, 0, 255},
        {0, 255, 0, 255},   
        {0, 0, 255, 255},   
        {255, 255, 0, 255}, 
        {0, 0, 0, 255}
    };
    
    for (int i = 0; i < NB_COULEUR; i++) {
        couleurs[i] = base[i % 5];
    };

    // for (int i = 0; i < NB_COULEUR; i++) {
    //     printf("\033[38;2;%d;%d;%dm", couleurs[i].r, couleurs[i].g, couleurs[i].b);
    //     printf("Couleur %d : R=%d G=%d B=%d A=%d\n", i+1, couleurs[i].r, couleurs[i].g, couleurs[i].b, couleurs[i].a);
    //     printf("\033[0m");
    // }

    for (int i = 0; i < NB_COULEUR; i++) {
        //si la couleurs n'est pas dans couleur c l'ajouter, sinon ajouter 1 à nb dans couleur_c
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

    printf("\nCouleurs distinctes\n");
    for (int i = 0; i < nb_distinctes; i++) {
        printf("\033[38;2;%d;%d;%dm", couleurs_count[i].r, couleurs_count[i].g, couleurs_count[i].b);
        printf("Couleur R=%d G=%d B=%d A=%d : %d fois\n", couleurs_count[i].r, couleurs_count[i].g, couleurs_count[i].b, couleurs_count[i].a, couleurs_count[i].nb);
        printf("\033[0m");
    }

    return 0;
}