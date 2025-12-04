#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

static char** lexeur(char *input){

    const char *separateur = " ";

    char **arrayToken = calloc(255, sizeof(char*));

    char *token = strtok(input,separateur);
    int i = 0;
    while (token != NULL)
    {
        arrayToken[i++] = token;
        token = strtok(NULL, separateur);
    }

    return arrayToken;
}

int main() {
    char test[] = "12 + 1 /  3";
    char **result = lexeur(test);
    for (int i = 0; result[i] != NULL; i++) {
        printf("Token[%d]: %s\n", i, result[i]);
    }
    free(result);
    return 0;
}