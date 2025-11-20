/* Fichier : binaire.c
   Auteur : Baptiste Rousselot, Camille Morfin
   Description : Ce programme convertit un entier décimal en binaire et affiche le résultat.
*/
#include <stdio.h>
#include <string.h>

int main(){

    int entier = 12;
    int reste;
    int resultat[32];
    int i = 0;

    // transformation en binaire (le resultat est à l'envers)
    while(entier>0){
        resultat[i++] = entier%2;
        entier = entier/2;
    }
    // affiche à l'envers
    for (int j = i - 1; j >= 0; j--) {
        printf("%d", resultat[j]);
    }
}
