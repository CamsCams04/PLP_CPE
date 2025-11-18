#include <stdio.h>

struct etudiant
{
    char nom[255];
    char prenom[255];
    char adresse[510];
    int notes[2];
};

int main(){

    struct etudiant etudiants[5];

    for(int i = 0;i<5;i++){
        printf("entrez les infos de l'etu n %d \n",i);
        printf("Nom : ");
        scanf("%s", etudiants[i].nom);

        printf("Prénom : ");
        scanf("%s", etudiants[i].prenom);

        printf("Adresse : ");
        scanf(" %[^\n]", etudiants[i].adresse);

        printf("Note 1 : ");
        scanf("%d", &etudiants[i].notes[0]);

        printf("Note 2 : ");
        scanf("%d", &etudiants[i].notes[1]);
    }

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
