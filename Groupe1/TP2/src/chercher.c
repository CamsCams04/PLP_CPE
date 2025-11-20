/* 
 * Fichier : cherhcer.c
 * Auteur : Baptiste Rousselot, Camille Morfin
 * Description : Dans ce programme, on va chercher dans un tableau si la phrase est présente ou non dedans
*/

#include <stdio.h>

#define N_PHRASES 10
#define MAX_LEN 256

/* --- Comparaison des chaînes --- */
int equals(const char *a, const char *b) {
    if (a == NULL || b == NULL) return 0;
    while (*a != '\0' && *b != '\0') {
        if (*a != *b) return 0;
        a++;
        b++;
    }
    return (*a == '\0' && *b == '\0'); // retourne 1 si vrai et 0 sinon
}

/* --- Supprime le '\n' final s'il est présent --- */
void strip_newline(char *s) {
    if (s == NULL) return;
    size_t i = 0;
    while (s[i] != '\0') {
        if (s[i] == '\n') {
            s[i] = '\0'; 
            return;
        }
        i++;
    }
}

int main(void) {
    char phrases[N_PHRASES][MAX_LEN] = {
        "Bonjour, comment ça va ?",
        "Le temps est magnifique aujourd'hui.",
        "C'est une belle journée.",
        "La programmation en C est amusante.",
        "Les tableaux en C sont puissants.",
        "Les pointeurs en C peuvent être déroutants.",
        "Il fait beau dehors.",
        "La recherche dans un tableau est intéressante.",
        "Les structures de données sont importantes.",
        "Programmer en C, c'est génial."
    };

    char query[MAX_LEN];

    printf("Entrez la phrase à rechercher :\n");
    if (fgets(query, sizeof query, stdin) == NULL) return 1;
    strip_newline(query);

    for (int i = 0; i < N_PHRASES; i++) {
        if (equals(query, phrases[i])) {
            printf("Phrase trouvée (à l'index %d).\n", i);
            return 0;
        }
    }

    printf("Phrase non trouvée.\n");
    return 0;
}