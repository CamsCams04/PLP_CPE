#include <stdio.h>
#include <string.h>

int lengthexo(char text[255]) {
    int totlen = 0;

    for(int i = 0; text[i] !='\0';i++){
        totlen++;
    }
    return totlen;
}

int main() {
    char chaine1[255];
    char chaine2[255];

    printf("Veuillez renseigner une chaine de caractère :\n");
    scanf("%s", chaine1);

    printf("Veuillez renseigner une seconde chaine de caractère :\n");
    scanf("%s", chaine2);

    printf("La chiane 1 : %s\n", chaine1);
    printf("La chiane 2 : %s\n\n", chaine2);

    // Taille avec strlen
    int lengthChaine1 = strlen(chaine1);
    int lengthChaine2 = strlen(chaine2);

    printf("Taille avec la fonction strlen : \n");
    printf("length chaine 1: %d\n",lengthChaine1);
    printf("length chaine 2 : %d\n\n",lengthChaine2);

    // Taille avec fonction personnalisée
    lengthChaine1 = lengthexo(chaine1);
    lengthChaine2 = lengthexo(chaine2);

    printf("Taille avec une fonction créée : \n");
    printf("length chaine 1: %d\n",lengthChaine1);
    printf("length chaine 2 : %d\n\n",lengthChaine2);

    return 0;
}
