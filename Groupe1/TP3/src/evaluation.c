#include <stdio.h>
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
