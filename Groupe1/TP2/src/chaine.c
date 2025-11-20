/* 
 * Fichier : chaine.c
 * Auteur : Baptiste Rousselot, Camille Morfin
 * Description : Dans ce programme, on va effectuer trois opérations sur deux chaines de caractères
 *                  - Calcule de la longueur
 *                  - Copie d'une chaine dans une autre
 *                  - Concaténation de deux chaine
*/

#include <stdio.h>
#include <string.h>

/* --- calcule la taille d'une chaine --- */
int lengthexo(char text[255]) {
    int totlen = 0;

    /* --- Parcours de toute la chaine --- */
    for(int i = 0; text[i] !='\0';i++){ // S'arrête si on croise le '\0'
        totlen++;
    }
    return totlen;
}

/* --- Concaténation de deux chaines de caractères --- */
void concat(char dest[255], const char src[255]) {
    int dest_len = lengthexo(dest); // Donne l'emplacement de la fin de la première chaine et le début de la nouvelle
    int src_i = 0;

    /* --- Copie tant qu'il reste de la place --- */
    while (dest_len < 254 && src[src_i] != '\0') {
        dest[dest_len++] = src[src_i++];
    }
    dest[dest_len] = '\0';
}

/* --- Copie d'une chaine de caractère dans une autre --- */
void copie(char dest[255], const char src[255]) {
    int dest_i = 0;
    int src_i = 0;

    /* --- Copie tant qu'il reste de la place --- */
    while (dest_i < 254 && src[src_i] != '\0') {
        dest[dest_i++] = src[src_i++];
    }
    dest[dest_i] = '\0';
}

int main() {
    char chaine1[255];
    char chaine2[255];

    printf("Veuillez renseigner une chaine de caractere :\n");
    scanf(" %254[^\n]", chaine1);

    printf("Veuillez renseigner une seconde chaine de caractere :\n");
    scanf(" %254[^\n]", chaine2);

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

    /* Concaténation : on ajoute chaine2 à la fin de chaine1 */
    concat(chaine1, chaine2);
    printf("Concatenation (chaine1 + chaine2) : %s\n", chaine1);
    printf("On peut aussi utiliser strcat !\n\n");

    /* Copie : on copie le contenue de chaine2 dans chaine1 */
    copie(chaine1, chaine2);
    printf("Copie de chaine 2 dans chaine 1.\nChaine 1 : %s\n", chaine1);
    printf("On peut aussi utiliser strcpy !\n");

    return 0;
}
