#include <stdio.h>
#include <string.h>

int searchSentence(const char *filename, char *sentence) {
    FILE *inputFile = fopen(filename, "r");
    if(inputFile == NULL) {
        fprintf(stderr, "Erreur : impossible d'ouvrir le fichier '%s'\n", filename);
        return -1;
    }

    char line[1024];
    int line_num = 1;
    int found = 0;

    while(fgets(line, sizeof line, inputFile) != NULL) {
        if (strstr(line, sentence) != NULL) {
            printf("Occurence trouvée à la ligne %d : %s", line_num, line);
            if (line[strlen(line) - 1] != '\n') printf("\n");
            found++;
        }
        line_num++;
    }

    if(found == 0) {
        printf("Aucune occurence de \"%s\" trouvé dans %s\n", sentence, filename);
    } else {
        printf("Total d'occurences : %d\n", found);
    };

    fclose(inputFile);
    return found;
}

int main() {
    char filename[255];     // Name of file
    char sentence[255];     // sentence to search

    /* ------------------------ */
    /* --- Get informations --- */
    /* ------------------------ */
    printf("Veuillez donner le nom du fichier dans lequel effectuer la recherche (ne pas oublier le .md, .txt, ...): \n");
    scanf(" %254[^\n]", filename);

    printf("Veuillez renseigner la phrase à rechercher : \n");
    scanf(" %254[^\n]", sentence);

    searchSentence(filename, sentence);

    return 0;
}