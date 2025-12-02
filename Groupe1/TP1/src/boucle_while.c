/* Fichier : boucle_while.c
   Auteur : Baptiste Rousselot, Camille Morfin
   Description : Dessine une pyramide en fonction de la taille donnée par l'utilisateur. (avec une boucle while)
*/
#include <stdio.h>

int main(){
    int i = 0;
    int size;

    scanf("%d", &size);
    printf("%d < %d \n",i, size);

    while(i < size){
        int j = 0;
        while(j <= i ){
            /* --- Vérification des bords --- */
            if(j==0 || j==i || i == size-1){
                printf("*");
            } else {
                /* --- n'est pas un bord --- */
                printf("#");
            }
            j++;
       }
       printf("\n");
       i++;
    }

    return 0;
}
