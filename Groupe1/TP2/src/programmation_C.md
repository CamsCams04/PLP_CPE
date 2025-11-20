# C

# I. Débogage avec `gdb`

`gdb` est une **librairie de débogage** qui va nous permettre de repérer les **erreurs** et de les **corriger** plus facilement.

Grâce à cette outil, on va pouvoir **repérer facilement** où est le **problème** dans notre code et qu’est ce qui le fait planter.

Nous allons pouvoir également **observer** la **pile d’appel** que va faire le script afin de pouvoir **observer et étudier le comportement de l’exécution**.

Comme une majorité d’outils de débogage, on va avoir la possibilité de mettre des **points** **d’arrêts**. Cela va nous permettre de décider où le script va **s’arrêter** dans son exécution et de pouvoir **observer** l’**état des variables** à un moment donnée comme la variable tableau où nous pouvons examiner son contenu dans le TP2 exercice 1.

On va pouvoir également soit demander à `gdb` d’exécuter **entièrement** le code jusqu’aux points d’arrêts (si ils ont lieu) ou sinon de lui demander de faire **instruction par instruction**. Cette fonction va nous permettre d’**observer** le **comportement de nos variables** à chaque nouvelles instructions et de pouvoir repérer le plus précisément possible la **source de notre problème**.

`gdb` est un outils vraiment **intéressant et pratique** dans le **débogage** de script.

---

# II. Chaîne de compilation en C avec `gcc`

## II.I. Introduction

En C, la chaine de compilation possède plusieurs étapes :

- **Préprocesseur**
- **Compilation**
- **Assemblage**
- **Édition de liens**
- **Exécution**

## II.II. Définition des étapes

### 1. Préprocesseur

L’étape préprocesseur va s’occuper de toutes les inclusions `#includes` et des macros. En résumé toutes les instructions commençant par `#`.

Cette étape va nous permettre de produire un fichier source “pré-traité”, qui est prêt à être compilé.

Afin d’exécuter cette étape de **préprocesseur**, on va exécuter la commande suivante : 

```bash
gcc -E aire.c -o aire.i
```

- `-E` ⇒ indique à `gcc` de ne faire que le prétraitement.
- `aire.i` ⇒ fichier généré contenant le code source **après prétraitement,** avec tous les `#includes` remplacé par le contenu réel des fichiers et  toutes les macros développée.

Le fichier `.i` qui va être généré, donc ici `aire.i` va correspondre à cette étape de préprocesseur. Ce fichier n’est **pas exécutable.**

### 2. Compilation

L’étape de **compilation** transforme le code source **pré-traité** (fichier `.i`) en **code assembleur,** compréhensible par la machine mais encore sous forme texte.

Cette étape ne produit pas encore un exécutable, mais un fichier `.s` contenant les instructions assembleur.

Pour exécuter cette étape, on utilise la commande suivante :

```bash
gcc -O2 -S aire.i -o aire.s
```

- `-02` ⇒ indique à `gcc` de ne faire que la **compilation** (produire le code assembleur)
- `-S` ⇒ active un niveau d’**optimisation du code** pour améliorer l’efficacité de l’assembleur généré
- `aire.i` ⇒ fichier **pré-traité** généré lors de l’étape de préprocesseur
- `aire.s` ⇒ fichier généré contenant le **code assembleur** correspondant à notre programme

### 3. Assemblage

L’étape d’**assemblage** transforme le code en **assembleur** généré dans l’étape précédente (fichier `.s`) en un **fichier objet** (`.o`), qui contient du code machine compréhensible par le processeur mais pas encore **exécutable.**

Commande pour assembler le fichier :

```bash
gcc -c aire.s -o aire.o
```

- `-c` ⇒ indique à `gcc` de ne faire que l’assemblage
- `aire.s` ⇒ indique assembleur produit lors de l’étape de compilation
- `aire.o` ⇒ fichier **objet** généré, contenant le code machine

### 4. Édition de liens

L’étape d’**édition de liens** prend un ou plusieurs fichier objets `.o` et **les combine avec les bibliothèques nécessaires** pour produire un programme **exécutable.**

Commande pour lier le fichier objet et créer l’exécutable :

```bash
gcc aire.o -lm -o aire

# ou encore 

gcc main.o volume.o surface.o -lm -o sphere
```

- `aire.o` ⇒ fichier objet généré  à l’étape précédente
- `-lm` ⇒ option pour lier la **bibliothèque mathématique** (`libm`) si cotre programme utilise des fonctions mathématique (comme `M_PI`)
- `-o aire` ⇒ nom de l’exécutable

**À savoir :**

- Après cette, étape, le programme est prêt à été exécuté.
- On peut maintenant lancer le programme avec :

```bash
./aire
```

---

# III. Manipulation de chaine en C, les bases

En C les chaines de caractères se manipulent comme des tableaux. En effet elles sont gérés avec des tableau avec un caractère `char` dans chaque index du tableau. 

## Tableaux

Un tableau de charactère pour détecter sa taille ou le dernier éléments il faut tester sur \0 

Exemple : 

Si on a “Hello” dans un tableau C il sera découpé ainsi

| H | e | l | l | o | \0 |
| --- | --- | --- | --- | --- | --- |

## scanf

Dans un scanf on a plusieurs options utilisables en fonction de la variable que l’on souhaite recevoir

| %d | Lit un int. Ignore les espaces avant la valeur. |
| --- | --- |
| %s | Lit une chaîne sans espaces : s’arrête au premier espace, tabulation ou retour à la ligne. Ajoute automatiquement `\0` à la fin. |
| %[^\n] | Lit une chaîne **avec espaces** jusqu’au caractère `\n`. |

## string.h

Pour simplifier la manipulation des chaines de caracteres il existe une bibliothèques nommé string.h

`#include <string.h>` 

Voici quelques un de ses fonctions que nous avons utilisés dans ce TP 

### strlen

`strlen(char *str);` ⇒ int

Calcule la longueur d'une chaîne de caractères (nombre de caractères avant le caractère nul `\0`).

- Exemple d’utilisation :

```c
int lengthChaine1 = strlen(chaine1);
int lengthChaine2 = strlen(chaine2);
```

### strcat

`strcat(char *dest, const char *src);` ⇒ char *str

Concatène la chaîne `src` à la fin d’une chaîne `dest`. Attention à la taille du tableau `dest` pour éviter les débordements.

### strcpy

`strcpy(char *dest, const char *src);` ⇒ char *str

Copie la chaîne `src` dans la chaîne `dest`, y compris le caractère nul final.

---

# IV. Gestion des structures pour les données et recherche dans les fichiers.

## IV.I. Structure

Les **structures** en C sont des types de données personnalisés qui permettent de regrouper plusieurs variables de types différents sous un même nom.

Cela permet d’avoir un code plus clair et structuré. On peut ainsi facilité par exemple le passage de variable. 

### Déclaration d’une structure

```c
struct etudiant{    
	char nom[255];    
	char prenom[255];    
	char adresse[510];   
	int notes[2];
};
```

Ici un étudiant peux donc être utilisé comme un type. 

### Utilisation

`struct etudiant etudiants[5];` Ainsi je crée un tableau d’étudiant

`etudiants[i].nom` Je peux accéder au nom de l’étudiant i

Pour initialiser j’ai deux options 

`scanf("%s", etudiants[i].nom);`

ou

`etudiants[i].nom = “Marco”`

## IV.II. Recherche dans les fichiers

La **recherche dans les fichiers** en C consiste à parcourir nu fichier texte pour **trouver des informations spécifiques**, comme une phrase ou un mot, puis éventuellement effectuer des actions comme compter les occurrences ou afficher les lignes correspondantes. (cf. Exercice 2.6)

### 1. Étapes générales

1. **Ouvrir le fichier**
    - On utilise la fonction `fopen` avec un mode approprié (`”r”` pour lecture, `"w"` pour écriture, `"a"` pour ajout).
    - Il est important de vérifier si l’ouverture a réussi (pointeur `NULL` si le fichier n’existe pas).
2. **Lire le fichier**
    - Pour parcourir le fichier, on peut lire **ligne par ligne** avec `fgets` ou **caractère par caractère** avec `fgetc`.
    - On va privilégié l’utilisation de la lecture ligne par ligne pour la recherche de phrases ou afficher des informations formatées. cela est souvent plus pratique.
3. **Chercher l’information**
    - Pour trouver un mot ou une phrase dans une ligne, on peut utiliser des fonctions de manipulation de chaînes comme :
        - `strstr` ⇒ chercher une sous-chaîne dans une chaîne
        - `strcmp` ⇒ comparer des chaînes
        - `strncmp` ⇒ comparer un nombre limité de caractères
4. **Traiter les résultats** 
    - On  peut afficher la ligne, compter les nombre d’occurrences ou stocker les résultats dans une structure pour un traitement ultérieur. (cf. Exercice 2.6)
5. **Fermer le fichier**
    - Toujours utiliser `fclose` pour libérer les ressources une fois la lecture terminée, et donc fermer le traitement du fichier.

### 2. Point importants

- **Gestion des erreurs :** Vérifier que `fopen` ne retourne pas `NULL` sinon cela veut dire que le fichier n’existe pas.
- **Taille des lignes :** définir un buffer suffisamment grand pour contenir les lignes du fichier.
- **Sensibilité à la casse :** `strstr` est sensible à la casse.

### 3. Application de la lecture de fichier

Dans l**’exercice 2.6 du TP2**, suite à avoir demandé à l’utiliser le fichier à lire et la phrase à chercher, on va ouvrir le fichier avec :

```c
FILE *inputFile = fopen(filename, "r");
```

On va par la suite s’assurer qu’on puisse ouvrir le fichier :

```c
if(inputFile == NULL) {
	fprintf(stderr, "Erreur : impossible d'ouvrir le fichier '%s'\n", filename);        
	return -1;
}
```

Puis on va parcourir ligne par ligne le fichier et on va checker pour chaque ligne si on trouve une occurrence de notre phrase.

```c
while(fgets(line, sizeof line, inputFile) != NULL) {
	if (strstr(line, sentence) != NULL) {
		printf("Occurence trouvée à la ligne %d : %s", line_num, line);
		if (line[strlen(line) - 1] != '\n') printf("\n");
		found++;
	}
	line_num++;
}
```

Dans cette exercice, on devait regarder si on trouvait la phrase renseigné par l’utilisateur dans notre fichier, indiquer la ligne ou l’on trouve la phrase et enfin indiquer le nombre d’occurrence trouvée de la phrase de l’utilisateur.