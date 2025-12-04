#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "date_utils.h"
#include "utils.h"
#include "lexer.h"
#include "parseur.h"

// Enumeration des différentes commandes
enum Functions{
    version,
    help,
    echo, 
    quit, 
    date,
    calc
};

// Structure d'une commande
struct Commande
{
    char param[255];
    enum Functions enume;
    char lang[255];
};



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
        printf("aider          : Affiche cette liste d'aide.\n");
        printf("date           : Afficher la date\n");
        printf("\nquitter      : Quitte le programme.\n");
    } else if (strcmp(langue, "en") == 0) {
        printf("Command list :\n");
        printf("================================\n");
        printf("echo <text>     : Display text after the command.\n");
        printf("version         : Display program version.\n");
        printf("help            : Dislay help.\n");
        printf("date            : Display current date\n");
        printf("\nquit          : Quit this program.\n");
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

/**
 * Traitemet de ma commande calc
 * {char *} - commande
 */
void traiter_calc(const char *commande){
    char input[255] = "";
    strcat(input, commande + 5);

    char **result = lexeur(input);
    if(!result) {
        printf("Lexer error: résultat NULL\n");
        return;
    }

    // compte des tokens
    int count_token = 0;
    while(result[count_token] != NULL) count_token++;

    // Convertion en struct tocken
    struct Token *toks = malloc(sizeof(*toks) * (count_token + 1));
    if(!toks) {
        printf("Erreur d'allocation des tokens\n");
        free(result);
        return;
    }
    for(int i = 0; i < count_token; i++) {
        const char *s = result[i];
        toks[i].raw = s;
        toks[i].op = 0;
        toks[i].value = 0.0;

        char *end = NULL;
        errno = 0;
        double value = strtod(s, &end);
        if(end && *end == '\0') {        // si toute la chaîne est un nombre
            toks[i].type = TOK_NUMBER;
            toks[i].value = value;        // ⚡ stocker la valeur
        } else if (s[0] != '\0' && s[1] == '\0' && 
                (s[0] == '+' || s[0] == '-' || s[0] == '*' || s[0] == '/')) {
            toks[i].type = TOK_OPERATOR;
            toks[i].op = s[0];
        } else {
            toks[i].type = TOK_INVALID;
        }
    }
    toks[count_token].type = TOK_EOF;
    toks[count_token].raw = NULL;
    toks[count_token].op = 0;
    toks[count_token].value = 0.0;

    char *err = NULL;
    struct Expression *expr = parse_tokens(toks, count_token + 1, &err);
    if (!expr) {
        printf("Parse Erreur: %s\n", err ? err : "inconnue");
        free(err);
        free(toks);
        free(result);
        return;
    }
    char opview = (
        expr->op==OP_ADD?'+': (
            expr->op==OP_DIV?'/': (
                expr->op==OP_MUL?'*':'-'
            ))
    );
    printf("Parseur: opération: %c, opérande1: %g, opérande2: %g\n", opview, expr->lhs, expr->rhs);
    free(expr);
    free(toks);
    free(result);
}


int quiting(const char *langue){
    // Quitte le programme si la commande est "quit"
        if (strcmp(langue, "fr") == 0) {
            printf("Arrêt...\n");
        } else if (strcmp(langue, "en") == 0) {
            printf("Stopping...\n");
        }
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
        {"date",    date, "fr"},
        {"calc", calc, "fr"}
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
                continuer = quiting(langue);
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
            case calc: 
                traiter_calc(commande);
                break;
            default:
                gestion_erreur(commande);
                break;
        }
        printf("\n");
    }
    return 0;
}
