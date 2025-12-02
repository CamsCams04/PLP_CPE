/* Fichier : controle.c
   Auteur : Baptiste Rousselot, Camille Morfin
   Description : Parcours les 100 premier entier (3 méthodes différentes) et applique les règles.
*/
#include <stdio.h>

int main(){
    int tab[1000];
    int tab2[1000];
    int tab3[1000];
    int it = 1;
    int k = 0;
    int j = 0;
    int c = 0;

    for(int i = 1; i < 1000; i++) {
        if(i%4 == 0 && i%6 != 0){
            tab[k] = i;
            k++;
        }
        if(i%5 == 0 || i%7 == 0){
            if(i%10 == 0){
                break;
            } else {
                tab3[c] = i;
                c++;
            }
        }
    }

    while(it <=1000){
        if(it%2 == 0 && it%8 == 0){
            tab2[j] = it;
            j++;
        }
        it++;
    }

    for(int i=0;i < k;i++){
        printf("%d ",tab[i]);
    }
    printf("\n");
    for(int i=0;i < j;i++){
        printf("%d ",tab2[i]);
    }
    printf("\n");
    for(int i=0;i < c;i++){
        printf("%d ",tab3[i]);
    }

    return 0;
}
