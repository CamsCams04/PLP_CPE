#include <stdio.h>
#include <string.h>
#include "date_utils.h"

/**
 * Programme qui simule un interpréteur de commandes simple.
 * Il lit les commandes utilisateur et les traite en fonction de leur contenu.
 */
enum Functions{
    version,
    help,
    echo, 
    quit, 
    date
};
struct Commande
{
    char param[255];
    enum Functions enume;
};

// void afficher_version();
// void afficher_help();
// void traiter_echo(const char *commande);
// int quiting();

void afficher_version(){
    char version[255] = "12.12.12";

    printf("Version %s\n", version);
}

void afficher_help(){
    printf("Voici la liste des commandes :\n");
    printf("================================\n");
    printf("echo <texte>   : Affiche le texte saisi après la commande.\n");
    printf("version        : Affiche la version du programme.\n");
    printf("help           : Affiche cette liste d'aide.\n");
    printf("date           : Afficher la date\n");
    printf("\nquit           : Quitte le programme.\n");
};

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

int main()
{
    int continuer = 1; // Variable pour contrôler la boucle principale

    struct Commande commandes[] = {
        {"quit",    quit},
        {"quitter", quit},
        {"echo",    echo},
        {"version", version},
        {"help",    help},
        {"aider",   help},
        {"date",    date}
    };
    
    // Boucle principale qui lit et traite les commandes utilisateur
    while (continuer)
    {
        printf("> "); // Affiche le prompt de commande

        // Buffer pour stocker la commande utilisateur
        char commande[1024];

        // Lit la commande utilisateur et la stocke dans le buffer
        fgets(commande, sizeof(commande), stdin);

        // Enlève le caractère de fin de ligne ajouté par fgets
        commande[strcspn(commande, "\n")] = 0;

        enum Functions fonction = -1;

        int nb_commandes = sizeof(commandes);

        for( int i = 0 ; i < nb_commandes;i++){
            if (strncmp(commande, commandes[i].param, strlen(commandes[i].param)) == 0) {
                fonction = commandes[i].enume;
                break;
            }
        }

        switch (fonction)
        {
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
            afficher_help();
            break;
        case date:
            afficher_date();
            break;
        default:
            printf("Commande non reconnue. Essayez 'echo <text>' pour afficher du texte, ou tapez 'quit' pour quitter.\n");
            break;
        }

        printf("\n");
    }
    return 0;
}
