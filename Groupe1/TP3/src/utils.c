#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "utils.h"

#define CMD_COUNT 8

// Enumeration des possibilités de quitter
const char *typos_quitter[] = {
    "qutter", "quiter", "quitterr", "quittter", "qiitter",
    "qyitter", "qitter", "quitte", "quitetr", "uqitter"
};

// Enumeration des possibilités de quit
const char *typos_quit[] = {
    "qit", "quittt", "quitt", "qiut", "qut", 
    "quite", "auit", "quiyt", "quut", "qquit", "quittter"
};

// Enumeration des possibilités de echo
const char *typos_echo[] = {
    "eco", "eho", "ehco", "ecco", "ech", 
    "dcho", "echoo", "3cho", "eclo", "ecjo"
};

// Enumeration des possibilités de version
const char *typos_version[] = {
    "vesion", "verion", "versin", "versionn", "verrion", 
    "verison", "bers ion", "verson", "verzion", "versio"
};

// Enumeration des possibilités de help
const char *typos_help[] = {
    "hep", "hlep", "hellp", "helpp", "hepl", 
    "hezp", "gelp", "hell", "heap", "hlp"
};

// Enumeration des possibilités de aider
const char *typos_aider[] = {
    "ider", "ader", "aidr", "aid er", "aiider", 
    "ayd er", "aideer", "auder", "aqder", "aide"
};

// Enumeration des possibilités de aide
const char *typos_aide[] = {
    "ide", "ade", "aidee", "aied", "aice", 
    "aode", "aiide", "aude", "aixe", "aide4"
};

// Enumeration des possibilités de date
const char *typos_date[] = {
    "dae", "dat", "datee", "dte", "daze", 
    "dzte", "datr", "dqte", "daet", "dare"
};

const char *typos_calc[] = {
    "alc", "clac", "cacl", "callc", "calcc", 
    "calk", "cavc", "cal", "calx"
};


// tableau global
const char **commands_typos[CMD_COUNT] = {
    typos_quitter,
    typos_quit,
    typos_echo,
    typos_version,
    typos_help,
    typos_aider,
    typos_aide,
    typos_calc
};

const char *command_names[CMD_COUNT] = {
    "quitter",
    "quit",
    "echo",
    "version",
    "help",
    "aider",
    "aide",
    "calc"
};

/**
 * Fonction pour retrouver les erreurs de frappe
 * {char *} - commande: contenue de la commande écrit dans le prompt
 */
void gestion_erreur(const char *commande) {
    for (int cmd = 0; cmd < CMD_COUNT; cmd++) {
        for (int i = 0; i < 10; i++) {
            if (strcmp(commande, commands_typos[cmd][i]) == 0) {
                printf(
                    "Commande inconnue : \"%s\".\n"
                    "Essayez plutôt : \"%s\".\n",
                    commande,
                    command_names[cmd]
                );
                return;
            }
        }
    }
    printf("Commande non reconnue. Tapez 'aide' pour la liste des commandes.\n");
}

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