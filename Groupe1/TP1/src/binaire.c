#include <stdio.h>
#include <string.h>

int main(){

    int entier = 12;
    int reste;
    int resultat[32];
    int i = 0;

    while(entier>0){
        resultat[i++] = entier%2;
        entier = entier/2;
    }
    for (int j = i - 1; j >= 0; j--) {
        printf("%d", resultat[j]);
    }
}
