#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"

/* --- Prise en compte de l'expression même si pas d'espace --- */
char** lexeur(const char *input) {
    char **tokens = calloc(255, sizeof(char*));
    if (!tokens) return NULL;

    int t = 0;
    int i = 0;

    while (input[i]) {
        if (isdigit(input[i]) || input[i] == '.') {
            // Lecture d'un nombre
            char buffer[64];
            int j = 0;
            while (isdigit(input[i]) || input[i] == '.') {
                buffer[j++] = input[i++];
            }
            buffer[j] = '\0';
            tokens[t++] = strdup(buffer);
        } else if (strchr("+-*/()", input[i])) {
            // Lecture d'un opérateur ou parenthèse
            char buffer[2] = {input[i], '\0'};
            tokens[t++] = strdup(buffer);
            i++;
        } else if (isspace(input[i])) {
            // Ignorer les espaces
            i++;
        } else {
            printf("Caractère non autorisé : %c\n", input[i]);
            i++;
        }
    }
    tokens[t] = NULL; // fin du tableau
    return tokens;
}
