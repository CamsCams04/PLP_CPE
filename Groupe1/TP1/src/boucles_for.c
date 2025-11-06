#include <stdio.h>

int main() {
    /* --- Définition des variables --- */
    int size;

    /* --- Récupération de la taille du triangle --- */
    printf("Veuillez entrer la taille du triangle (<10) : ");
    scanf("%d", &size);

    /* --- Vérification inférieur strict à 10 --- */
    while(size >= 10) {
        printf("Attention, la taille doit être inférieur à 10 : ");
        scanf("%d", &size);
    }


    for(int i = 0; i < size; i++) {
        for(int j = 0; j <= i; j++) {
            /* --- Vérification des bords --- */
            if(j == 0 || j == i || i+1 == size) {
                /* --- est un bord --- */
                printf("*");
            } else {
                /* --- n'est pas un bord --- */
                printf("#");
            }
        }
        printf("\n");
    }
}