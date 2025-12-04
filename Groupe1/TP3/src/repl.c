#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "date_utils.h"

// Enumeration des différentes commandes
enum Functions{
    version,
    help,
    echo, 
    quit, 
    date
};

// Structure d'une commande
struct Commande
{
    char param[255];
    enum Functions enume;
    char lang[255];
};

/* --- Remplace quelques lettres accentuées communes par leur équivalent ASCII. --- */
void strip_accents_inplace(char *s) {
    unsigned char *p = (unsigned char*)s;
    while (*p) {
        switch (*p)
        {
        case 0xC3: {
            unsigned char next = *(p+1);
            if (next) {
                if (next == 0xA9) { *p = 'e'; /* é (C3 A9) -> e */
                    memmove(p+1, p+2, strlen((char*)p+2)+1); 
                    continue;
                }
                if (next == 0xA8) { *p = 'e'; memmove(p+1, p+2, strlen((char*)p+2)+1); continue; } /* è */
                if (next == 0xAA) { *p = 'e'; memmove(p+1, p+2, strlen((char*)p+2)+1); continue; } /* ê approximé */
                if (next == 0xA0) { *p = 'a'; memmove(p+1, p+2, strlen((char*)p+2)+1); continue; } /* à */
                if (next == 0xA2) { *p = 'a'; memmove(p+1, p+2, strlen((char*)p+2)+1); continue; } /* â */
                if (next == 0xB4) { *p = 'o'; memmove(p+1, p+2, strlen((char*)p+2)+1); continue; } /* ó approximé */
                if (next == 0xA9) { *p = 'e'; memmove(p+1, p+2, strlen((char*)p+2)+1); continue; }
                if (next == 0xA3) { *p = 'u'; memmove(p+1, p+2, strlen((char*)p+2)+1); continue; } /* ù */
                if (next == 0xA7) { *p = 'c'; memmove(p+1, p+2, strlen((char*)p+2)+1); continue; } /* ç */
                /* Si non reconnu, on passe au caractère suivant */
            }
            break;
        }
        default:
            p++;
        }
    }
}

/* --- Transformation en minuscule --- */
void to_lower_case(char *s) {
    for( ; *s; ++s) *s = (char)tolower((unsigned char)*s);
}

/* --- Comparaison insensible à la casse --- */
int equals_normalized(const char *a, const char *b) {
    char tmpa[256], tmpb[256];
    strncpy(tmpa, a, sizeof(tmpa)-1); tmpa[sizeof(tmpa)-1] = 0;
    strncpy(tmpb, b, sizeof(tmpb)-1); tmpb[sizeof(tmpb)-1] = 0;
    to_lower_case(tmpa);
    to_lower_case(tmpb);
    strip_accents_inplace(tmpa);
    strip_accents_inplace(tmpb);
    return strcmp(tmpa, tmpb) == 0;
}


/**
 * Affichage de la version
 */
void afficher_version(){
    char version[255] = "12.12.12";

    printf("Version %s\n", version);
}

/**
 * Affichage d'information sur les différentes commandes disponibles
 */
void afficher_help(const char *langue){
    if (strcmp(langue, "fr") == 0) {
        printf("Voici la liste des commandes :\n");
        printf("================================\n");
        printf("echo <texte>   : Affiche le texte saisi après la commande.\n");
        printf("version        : Affiche la version du programme.\n");
        printf("help           : Affiche cette liste d'aide.\n");
        printf("date           : Afficher la date\n");
        printf("\nquit           : Quitte le programme.\n");
    } else if (strcmp(langue, "en") == 0) {
        printf("Voici la liste des commandes :\n");
        printf("================================\n");
        printf("echo <texte>   : Affiche le texte saisi après la commande.\n");
        printf("version        : Affiche la version du programme.\n");
        printf("help           : Affiche cette liste d'aide.\n");
        printf("date           : Afficher la date\n");
        printf("\nquit           : Quitte le programme.\n");
    }
};

/**
 * Traitement de la commande echo
 */
void traiter_echo(const char *commande){
// Traite la commande "echo" pour afficher du texte
    printf("Echo: ");
    // Imprime la chaîne
    for (int i = 5; commande[i] != '\0'; i++)
    {
        printf("%c", commande[i]);
    }
    printf("\n"); // Saut de ligne après la sortie
}


int quiting(){
    // Quitte le programme si la commande est "quit"
    printf("Arrêt...\n");
    return 0;
}


/**
 * Programme qui simule un interpréteur de commandes simple.
 * Il lit les commandes utilisateur et les traite en fonction de leur contenu.
 */
int main()
{
    int continuer = 1; // Variable pour contrôler la boucle principale

    struct Commande commandes[] = {
        {"quit",    quit,   "en"},
        {"quitter", quit,   "fr"},
        {"echo",    echo,   "fr"},
        {"version", version,"fr"},
        {"help",    help,   "en"},
        {"aider",   help,   "fr"},
        {"aide", help, "fr"},
        {"date",    date, "fr"}
    };

    int nb_commandes = sizeof(commandes) / sizeof(commandes[0]);
    
    // Boucle principale qui lit et traite les commandes utilisateur
     while (continuer) {
        printf("> ");
        char commande[1024];
        if (!fgets(commande, sizeof(commande), stdin)) break;
        commande[strcspn(commande, "\n")] = 0;

        /* copie pour normalisation ; on normalise uniquement la première "motte" */
        char cmd_copy[256];
        strncpy(cmd_copy, commande, sizeof(cmd_copy)-1);
        cmd_copy[sizeof(cmd_copy)-1] = 0;

        /* extraire le premier mot (la "commande") */
        char *first_space = strchr(cmd_copy, ' ');
        if (first_space) *first_space = '\0';

        /* normaliser (minuscules + sans accents) pour la comparaison */
        to_lower_case(cmd_copy);
        strip_accents_inplace(cmd_copy);

        enum Functions fonction = -1;
        char langue[255];
        for (int i = 0; i < nb_commandes; ++i) {
            char param_copy[256];
            strncpy(param_copy, commandes[i].param, sizeof(param_copy)-1);
            param_copy[sizeof(param_copy)-1] = 0;
            to_lower_case(param_copy);
            strip_accents_inplace(param_copy);

            if (strcmp(cmd_copy, param_copy) == 0) {
                fonction = commandes[i].enume;
                strncpy(langue, commandes[i].lang, sizeof(langue)-1);
                langue[sizeof(langue)-1] = '\0';
                break;
            }
        }

        switch (fonction) {
            case quit:
                continuer = quiting();
                break;
            case echo:
                traiter_echo(commande);
                break;
            case version:
                afficher_version();
                break;
            case help:
                afficher_help(langue);
                break;
            case date:
                afficher_date();
                break;
            default:
                printf("Commande non reconnue. Tapez 'aide' pour la liste des commandes.\n");
                break;
        }
        printf("\n");
    }
    return 0;
}
