#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "infix_to_postfix.h"

#define MAX_STACK 100   // Taille max de la pile opérateurs
#define MAX_OUTPUT 256  // Taille max de la chiane postfixés

/* --------------------------- */
/* --- Liste des priorités --- */
/* --------------------------- */

static int priority(char op) {
    switch (op) {
        case '+':
        case '-': return 1;
        case '*':
        case '/': return 2;
        default: return 0;
    }
}

/* ------------------------------ */
/* --- Fonction de convertion --- */
/* ------------------------------ */

char *infix_to_postfix(char **tokens, int count) {
    char op_stack[MAX_STACK];
    int top = -1;

    char *output = malloc(MAX_OUTPUT);
    if (!output) return NULL;
    output[0] = '\0';

    for (int i = 0; i < count; i++) {
        char *tok = tokens[i];

        //  Si un nombre -> sortie directe
        char *end;
        strtod(tok, &end);
        if (*end == '\0') {
            strcat(output, tok);
            strcat(output, " ");
        }
        // Si opérateur
        else if (strlen(tok) == 1 && strchr("+-*/", tok[0])) {
            char op = tok[0];

            while (top >= 0 && priority(op_stack[top]) >= priority(op)) {
                char tmp[2] = { op_stack[top--], '\0' };
                strcat(output, tmp);
                strcat(output, " ");
            }
            op_stack[++top] = op;
        }
        else {
            printf("Token invalide : %s\n", tok);
            free(output);
            return NULL;
        }
    }

    // Vider la pile
    while (top >= 0) {
        char tmp[2] = { op_stack[top--], '\0' };
        strcat(output, tmp);
        strcat(output, " ");
    }

    return output;
}
