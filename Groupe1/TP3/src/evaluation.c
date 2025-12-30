#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "evaluation.h"

double evaluation_calc(char operateur, double lhs, double rhs) {
    switch (operateur)
    {
    case '+':
        return lhs + rhs;
    case '-':
        return lhs - rhs;
    case '*':
        return lhs * rhs;
    case '/':
        if(rhs != 0) {
            return lhs / rhs;
        }
        else {
            printf("Erreur : division par zéro\n");
                return 0.0;
            }
    default:
        printf("Erreur : opérateur inconnu '%c'\n", operateur);
        return 0.0;
    }
}

double eval_postfix(char **tokens, int count) {
    double stack[100];
    int top = -1;

    for (int i = 0; i < count; i++) {
        char *tok = tokens[i];

        char *end;
        double val = strtod(tok, &end);

        // Si nombre
        if (*end == '\0') {
            stack[++top] = val;
        }
        // Si opérateur
        else if (strlen(tok) == 1 && strchr("+-*/", tok[0])) {
            if (top < 1) {
                printf("Erreur postfix : pas assez d'opérandes\n");
                return 0;
            }
            double rhs = stack[top--];
            double lhs = stack[top--];

            double res = evaluation_calc(tok[0], lhs, rhs);
            stack[++top] = res;
        }
        else {
            printf("Token invalide : %s\n", tok);
            return 0;
        }
    }

    if (top != 0) {
        printf("Erreur postfix : pile invalide\n");
        return 0;
    }

    return stack[top];
}
