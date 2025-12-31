#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "date_utils.h"
#include "utils.h"
#include "lexer.h"
#include "parseur.h"
#include "evaluation.h"
#include "infix_to_postfix.h"
#include "variables.h"

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
    /* --- Extraction de l'expression après "calc " --- */
    char input[256] = "";
    strcat(input, commande + 5);

    /* --- LEXER --- */
    char **result = lexeur(input);
    if(!result) {
        printf("Lexer error: résultat NULL\n");
        return;
    }

    // compte des tokens
    int count_token = 0;
    while(result[count_token] != NULL) count_token++;

    // Conversion infixée -> postfixée
    char *postfix = infix_to_postfix(result, count_token);
    if(!postfix) {
        printf("Erreur conversion postfix\n");
        // libération mémoire
        for(int i=0; i<count_token; i++) free(result[i]);
        free(result);
        return;
    }

   printf("Postfix : %s\n", postfix);

   // LEXER expression postfixée
   char **post_tokens = lexeur(postfix);
    if (!post_tokens) {
        printf("Erreur lexer postfix\n");
        free(postfix);
        free(result);
        return;
    }

    int post_count = 0;
    while (post_tokens[post_count] != NULL) post_count++;


    // Evaluation postfixée
    double result_final = eval_postfix(post_tokens, post_count);

    printf("Résultat : %g\n", result_final);

    // Nettoyage mémoire
    free(postfix);
    free(result);
    free(post_tokens);
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

void traiter_affectation(const char *input) {
    char name[128];
    char value[256];

    if (sscanf(input, " %127[^= ] = %255[^\n]", name, value) != 2) {
        printf("Erreur de syntaxe\n");
        return;
    }

    VarType type = detect_type(value);
    int res = set_variable(name, type, value);

    if (res == -1) {
        printf("Erreur : changement de type non autorisé pour %s\n", name);
        return;
    }

    printf("Variable %s définie\n", name);
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

        /* --- Gestion des variables : affectation --- */
        if (strchr(commande, '=') != NULL) {
            traiter_affectation(commande);
            printf("\n");
            continue;
        }

        /* --- Gestion des variables : lecture --- */
        Variable *v = find_variable(commande);
        if(v) {
            print_variable(v);
            printf("\n");
            continue;
        }

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
