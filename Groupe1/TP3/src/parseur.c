#include "parseur.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static const char *map_op(char c, enum OpType *out) {
    if(!out) return "erreur interne";

    switch (c) {
    case '+':
        *out = OP_ADD; 
        return NULL;
    case '-':
        *out = OP_SUB; 
        return NULL;
    case '*':
        *out = OP_MUL; 
        return NULL;
    case '/':
        *out = OP_DIV; 
        return NULL;    
    default:
        return "Cet opérateur inconnu";
    }
}

struct Expression *parse_tokens(const struct Token *tokens, int n, char **error_msg) {
    if(error_msg) *error_msg = NULL;
    if(!tokens || n<=0) {
        if (error_msg) *error_msg = strdup("aucun token fourni");
        return NULL;
    }

    int i = 0;
    while (i < n && tokens[i].type == TOK_EOF) i++; //ignore les EOF eventuels
    
    if (i >= n || tokens[i].type != TOK_NUMBER) {
        if (error_msg) *error_msg = strdup("erreur de syntaxe: attendu un nombre en première position");
        return NULL;
    }
    double lhs = tokens[i].value;
    i++;

    if (i >= n || tokens[i].type != TOK_OPERATOR) {
        if (error_msg) *error_msg = strdup("erreur de syntaxe: attendu un opérateur après le premier nombre");
        return NULL;
    }
    enum OpType op;
    const char *err = map_op(tokens[i].op, &op);
    if (err) {
        if (error_msg) *error_msg = strdup(err);
        return NULL;
    }
    i++;

    if (i >= n || tokens[i].type != TOK_NUMBER) {
        if (error_msg) *error_msg = strdup("erreur de syntaxe: attendu un deuxième nombre après l'opérateur");
        return NULL;
    }
    double rhs = tokens[i].value;
    i++;

    while (i < n) {
        if(tokens[i].type != TOK_EOF) {
            if (error_msg) *error_msg = strdup("tokens supplémentaires non utilisés");
            return NULL;
        }
        i++;
    };

    struct Expression *res = malloc(sizeof(*res));
    if(!res) {
        if(error_msg) *error_msg = strdup("problème d'allocation");
        return NULL;
    }
    res->op = op;
    res->lhs = lhs;
    res->rhs = rhs;
    return res;
}
