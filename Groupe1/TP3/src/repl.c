#include <stdio.h>
#include <string.h>

/**
 * Programme qui simule un interpréteur de commandes simple.
 * Il lit les commandes utilisateur et les traite en fonction de leur contenu.
 */

void afficher_version(){
    char version[255] = "12.12.12";

    printf("Version %s\n", version);
}

void afficher_help(){
    printf("Voici la liste des commandes :\n");
    printf("================================\n");
    printf("echo <texte>   : Affiche le texte saisi après la commande.\n");
    printf("quit           : Quitte le programme.\n");
    printf("version        : Affiche la version du programme.\n");
    printf("help           : Affiche cette liste d'aide.\n");
}

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

int main()
{
    int continuer = 1; // Variable pour contrôler la boucle principale

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

        // Traite la commande en fonction de son contenu
        if (strcmp(commande, "quit") == 0)
        {
            // Quitte le programme si la commande est "quit"
            printf("Arrêt...\n");
            continuer = 0;
        }
        else if (strncmp(commande, "echo ", 5) == 0)
        {
            traiter_echo(commande);
        }
        else if (strcmp(commande, "version") == 0){
            afficher_version();
        }
        else if (strcmp(commande, "help") == 0) {
            afficher_help();
        }
        else
        {
            // Affiche un message d'erreur si la commande est inconnue
            printf("Commande non reconnue. Essayez 'echo <text>' pour afficher du texte, ou tapez 'quit' pour quitter.\n");
        }

        printf("\n"); // Saut de ligne après la sortie
    }

    return 0;
}
