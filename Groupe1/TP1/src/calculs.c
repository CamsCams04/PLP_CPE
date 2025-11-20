/* Fichier : calculs.c
   Auteur : Baptiste Rousselot, Camille Morfin
   Description : Ce code réalise des calculs mathématiques de base en fonction de l'entrée utilisateur.
*/
#include <stdio.h>

int main() {
    /* --- Déclaration des variables --- */
    int num1;
    int num2;
    char op;

    printf("Veuillez donner une opération à réaliser :\n");
    printf("Opérateur (+, -, *, /, modulo  ,&, |, ~): ");
    scanf("%c", &op);
    printf("Premier nombre : ");
    scanf("%d", &num1);
    if(op != '~') {
        printf("Deuxième nombre : ");
        scanf("%d", &num2);
    }

    switch(op) {
        case '+':
            printf("%d %c %d = %d\n", num1, op, num2, (num1 + num2));
            break;
        case '-':
            printf("%d %c %d = %d\n", num1, op, num2, (num1 - num2));
            break;
        case '*':
            printf("%d %c %d = %d\n", num1, op, num2, (num1 * num2));
            break;
        case '/':
            if(num2 != 0) {
                printf("%d %c %d = %d\n", num1, op, num2, (num1 / num2));
            } else {
                printf("La division par 0 est impossible");
                return 1;
            }
            break;
        case '%':
            if(num2 != 0) {
                printf("%d %c %d = %d\n", num1, op, num2, (num1 % num2));
            } else {
                printf("La division par 0 est impossible");
                return 1;
            }
            break;
        case '&':
            printf("%d %c %d = %d\n", num1, op, num2, (num1 & num2));
            break;
        case '|':
            printf("%d %c %d = %d\n", num1, op, num2, (num1 | num2));
            break;
        case '~':
            printf("%c%d = %d\n", op, num1, ~num1);
            break;
        default:
            printf("l'opérateur %c n'est pas valide !", op);
    }

}