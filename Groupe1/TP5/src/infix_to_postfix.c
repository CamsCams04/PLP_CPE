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
    char op_stack[100];
    int top = -1;

    char *output = malloc(256);
    if (!output) return NULL;
    output[0] = '\0';

    for (int i = 0; i < count; i++) {
        char *tok = tokens[i];

        /* --- Si un nombre --- */
        char *end;
        strtod(tok, &end);
        if (*end == '\0') {
            strcat(output, tok);
            strcat(output, " ");
            continue;
        }

        /* --- Si une parenthèse ouvrante --- */
        if (strcmp(tok, "(") == 0) {
            op_stack[++top] = '(';
            continue;
        }

        /* -- Si parentèse fermante --- */
        if (strcmp(tok, ")") == 0) {
            while (top >= 0 && op_stack[top] != '(') {
                char tmp[2] = { op_stack[top--], '\0' };
                strcat(output, tmp);
                strcat(output, " ");
            }
            if (top < 0) {
                printf("Erreur : parenthèse fermante sans ouvrante\n");
                free(output);
                return NULL;
            }
            top--; // supprimer '('
            continue;
        }

        /* --- Si opérateur --- */
        if (strlen(tok) == 1 && strchr("+-*/", tok[0])) {
            char op = tok[0];
            while (top >= 0 &&
                   op_stack[top] != '(' &&
                   priority(op_stack[top]) >= priority(op)) {

                char tmp[2] = { op_stack[top--], '\0' };
                strcat(output, tmp);
                strcat(output, " ");
            }
            op_stack[++top] = op;
            continue;
        }
        
        /* --- Token invalide --- */
        printf("Token invalide : %s\n", tok);
        free(output);
        return NULL;
    }

    /* --- Vider la pile --- */
    while (top >= 0) {
        if (op_stack[top] == '(') {
            printf("Erreur : parenth�se ouvrante non ferm�e\n");
            free(output);
            return NULL;
        }
        char tmp[2] = { op_stack[top--], '\0' };
        strcat(output, tmp);
        strcat(output, " ");
    }

    return output;
}
