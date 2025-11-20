/* 
 * Fichier : bd_école.c
 * Auteur : Baptiste Rousselot, Camille Morfin
 * Description : Dans ce programme, on va gérer les données de 5 étudiant.e.s.
*/

#include <stdio.h>

/* --- Structure de l'étudiant --- */
struct etudiant
{
    char nom[255];
    char prenom[255];
    char adresse[510];
    int notes[2];
};

int main(){

    struct etudiant etudiants[5];   // Création d'un tableau de 5 étudiants

    /* --- Pour chaque étudiant --- */
    for(int i = 0;i<5;i++){
        /* --- Renseignement des informations --- */
        printf("entrez les infos de l'etu n %d \n",i);
        /* --- Du nom --- */
        printf("Nom : ");
        scanf("%s", etudiants[i].nom);

        /* --- Du prénom --- */
        printf("Prénom : ");
        scanf("%s", etudiants[i].prenom);

        /* --- De l'adresse --- */
        printf("Adresse : ");
        scanf(" %[^\n]", etudiants[i].adresse);

        /* --- Renseignement des notes --- */
        printf("Note 1 : ");
        scanf("%d", &etudiants[i].notes[0]);

        printf("Note 2 : ");
        scanf("%d", &etudiants[i].notes[1]);
    }

    /* --- Afficahge des informations des 5 étudiants --- */
    for(int  j= 0;j<5;j++){
        printf(
            "Etudiant n %d | %s %s \n | Adresse %s",j,etudiants[j].nom, etudiants[j].prenom, etudiants[j].adresse
        );
        for(int n = 0;n<2;n++){
            printf("notes %d : %d |",n,etudiants[j].notes[n]);
        }
        printf("\n");
    }

    return 0;
}
