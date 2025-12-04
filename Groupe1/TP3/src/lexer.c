#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include "lexer.h"

char** lexeur(char *input){

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