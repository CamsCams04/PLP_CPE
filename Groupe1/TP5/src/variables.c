#include "variables.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VARS 128

static Variable table[MAX_VARS];
static int var_count = 0;

/* -------------------------------- */
/* --- Recherche d'une variable --- */
/* -------------------------------- */

Variable *find_variable(const char *name) {
    for (int i = 0; i < var_count; i++) {
        if (strcmp(table[i].name, name) == 0) {
            return &table[i];
        }
    }
    return NULL;
}

/* ----------------------------- */
/* --- Détermination du type --- */
/* ----------------------------- */

VarType detect_type(const char *value) {
    if (value[0] == '"' && value[strlen(value) - 1] == '"') {
        return VAR_STRING;
    }
    if(strchr(value, '.')) {
        return VAR_DOUBLE;
    }
    return VAR_INT;
}

/* ----------------------------------- */
/* --- Créer/Modifier une variable --- */
/* ----------------------------------- */

int set_variable(const char *name, VarType type, const char *value_str) {
    Variable *v = find_variable(name);

    if(v) {
        // variable existante -> vérifier type
        if(v->type != type) {
            return -1; // changement de type interdit
        }
    } else {
        // nouvelle variable
        if(var_count >= MAX_VARS) return -2;

        v = &table[var_count++];
        v->name = strdup(name);
        v->type = type;
    }

    // Affectation valeur
    switch (type)
    {
    case VAR_INT:
        v->value.i = atoi(value_str); // ASCII to Integer
        break;
    case VAR_DOUBLE:
        v->value.d = atof(value_str); // ASCII to Float
        break;
    case VAR_STRING:
        v->value.s = strdup(value_str + 1); // sans "
        v->value.s[strlen(v->value.s) - 1] = '\0';
        break;
    }
    return 0;
}

/* -------------------------- */
/* --- Affichage variable --- */
/* -------------------------- */

void print_variable(const Variable *v) {
    if (!v) return;

    switch (v->type) {
        case VAR_INT:
            printf("%d\n", v->value.i);
            break;
         case VAR_DOUBLE:
            printf("%g\n", v->value.d);
            break;
        case VAR_STRING:
            printf("\"%s\"\n", v->value.s);
            break;
    }
}
