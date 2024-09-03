#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "dict.c"
#include "arbre.c"

// struct Noeud
// {
//     char caractere;
//     struct Noeud *gauche;
//     struct Noeud *droite;
// };

// // Fonction pour créer un nouveau nœud
// struct Noeud *creerNoeud(char caractere)
// {
//     struct Noeud *nouveauNoeud = (struct Noeud *)malloc(sizeof(struct Noeud));
//     nouveauNoeud->caractere = caractere;
//     nouveauNoeud->gauche = NULL;
//     nouveauNoeud->droite = NULL;
//     return nouveauNoeud;
// }


// // Fonction pour insérer un mot dans l'arbre binaire de recherche
// struct Noeud *inserer(struct Noeud *racine, Mot *dictionnaire)
// {
//     if (racine == NULL)
//     {
//         // Si la racine est NULL, créer un nouveau nœud pour la première lettre du mot
//         racine = creerNoeud(dictionnaire->mot[0]);
//         struct Noeud *tmp = racine;

//         // Insérer les lettres suivantes dans la suite du mot
//         for (int i = 1; i <= strlen(dictionnaire->mot) - 1; i++)
//         {
//             tmp->gauche = creerNoeud(dictionnaire->mot[i]);
//             tmp = tmp->gauche;
//             printf("%c", dictionnaire->mot[i]);
//         }
//     }
//     dictionnaire->suivant;

//     // Si la racine n'est pas NULL, parcourir le dictionnaire
//     while (dictionnaire != NULL)
//     {
//         struct Noeud *tmp = racine;

//         // Parcourir les lettres du mot actuel dans le dictionnaire
//         for (int i = 0; i <= strlen(dictionnaire->mot) - 1; i++)
//         {

//             // Vérifier si la lettre existe déjà comme fils
//             while (tmp->gauche != NULL)
//             {
//                 if (tmp->gauche->caractere == dictionnaire->mot[i])
//                 {
//                     tmp = tmp->gauche;
//                 }
//                 else
//                 {
//                     tmp->droite = creerNoeud(dictionnaire->mot[i]);
//                     tmp = tmp->droite;
//                     for (int i = 1; i <= strlen(dictionnaire->mot) - 1; i++)
//                     {
//                         tmp->gauche = creerNoeud(dictionnaire->mot[i]);
//                         tmp = tmp->gauche;
//                         printf("%c", dictionnaire->mot[i]);
//                     }
//                 }
//             }
//             // Si la lettre n'existe pas, l'ajouter comme fils
//         }

//         dictionnaire = dictionnaire->suivant;
//     }

//     return racine;
//     // if (dictionnaire->mot[0] < racine->caractere) {
//     //     racine->gauche = inserer(racine->gauche);
//     // } else if (caractere > racine->caractere) {
//     //     racine->droite = inserer(racine->droite);
//     // }

//     // Ignorer les doublons (caractère déjà présent dans l'arbre)
// }



/*************************************************************************/
void InsererMotArbre(char mot[], TArbre a, TArbre p) {
    
    printf("%s \n", mot[0]);

    // Déclarer un tableau pour stocker le reste du mot
    char motRest[strlen(mot)];

    // Créer un nouvel arbre avec la première lettre du mot
    TArbre m = createNode(mot[0], 0, NULL, NULL);

    // Si l'arbre actuel est vide, initialiser l'arbre avec le nouveau
    if (a->c == 0) {
        printf("%s \n", mot[0]);
        a = m;

        // Si le mot a plus d'une lettre, récursivement insérer le reste du mot
        if ((strlen(mot) - 1) > 0) {
            strncpy(motRest, mot + 1, strlen(mot) - 1);
            free(m);
            InsererMotArbre(motRest, a->FG, a);
        } else {
            printf("0");
            // Si le mot a une seule lettre, ajouter un caractère nul à gauche
            TArbre m1 = createNode((char)"\0", 0, NULL, NULL);
            a->FG = m1;
        }
    } else {
        // Si le caractère de l'arbre actuel est égal à la première lettre du mot
        if (a->c == m->c) {
            printf("3\n");
            // Récursivement insérer le reste du mot à gauche
            strncpy(motRest, mot + 1, strlen(mot) - 1);
            free(m);
            InsererMotArbre(motRest, a->FG, a);
        } else if (a->c < m->c) {
            // Si le caractère de l'arbre actuel est inférieur à la première lettre du mot
            printf("2\n");

            // Si le fils droit est vide, ajouter le nouvel arbre comme fils droit
            if (a->FD == NULL) {
                printf("21\n");
                a->FD = m;
                TArbre c = m;
                
                // Construire les sous-arbres à gauche avec le reste du mot
                while (strcmp(motRest, "") != 0) {
                    strncpy(motRest, mot + 1, strlen(mot) - 1);
                    TArbre aux = createNode(motRest[1], 0, NULL, NULL);
                    c->FG = aux;
                    c = aux;
                }
                // Ajouter un caractère nul comme dernier fils gauche
                TArbre last = createNode((char)"\0", 1, NULL, NULL);
                c->FG = last;
            } else {
                // Sinon, récursivement insérer le reste du mot à droite
                printf("22\n");
                InsererMotArbre(motRest, a->FD, a);
            }
        } else {
            // Si le caractère de l'arbre actuel est supérieur à la première lettre du mot
            printf("1\n");

            // Ajouter le nouvel arbre comme fils droit et ajuster le père
            m->FD = a;
            p->FD = m;
            // Récursivement insérer le reste du mot à droite
            strncpy(motRest, mot + 1, strlen(mot) - 1);
            InsererMotArbre(motRest, m, p);
        }
    }
}

void dicoAfficherAvecCommentaires(TArbre a, int niveau, const char *position) {
    // Initialise un tableau de caractères pour stocker les mots
    char ch[100] = "";  // Utilisation d'une taille arbitraire ici, veuillez ajuster selon les besoins
    int i = 0;          // Indice du tableau
    TArbre p, aux;

    // Ajoute la première lettre du mot à la racine de l'arbre
    ch[i] = a->c;
    i++;
    p = a->FG;  // Déplace le pointeur vers le fils gauche de la racine

    // Parcours de l'arbre
    while (p != NULL) {
        // Vérifie s'il y a un fils droit
        if (p->FD != NULL) {
            // Vérifie s'il y a aussi un fils gauche
            if (p->FG != NULL) {
                // Ajoute la lettre du nœud courant au tableau
                ch[i] = p->c;
                i++;
                aux = p->FG;

                // Parcours du sous-arbre gauche jusqu'à rencontrer un caractère nul
                while (aux->c != '\0') {
                    ch[i] = aux->c;
                    i++;
                    aux = aux->FG;
                }

                // Affiche le mot formé par les lettres dans le tableau avec des commentaires
                printf("\033[1;33mNiveau %d - %s = %s\033[0m\n", niveau, position, ch);

                // Déplace le pointeur vers le fils droit
                p = p->FD;

                // Réinitialise le tableau pour le prochain mot
                int j;
                for (j = 0; j < i; j++) {
                    ch[j] = '\0';
                }

                i = 0;  // Réinitialise l'indice du tableau
            } else {
                // S'il n'y a pas de fils gauche, déplace le pointeur vers le fils droit
                p = p->FD;
            }
        } else {
            // S'il n'y a pas de fils droit, déplace le pointeur vers le fils droit de la racine
            p = a->FD;
        }
    }
}

// Fonction pour afficher l'arbre avec des commentaires
void afficherArbreAvecCommentaires(TArbre a, int niveau, const char *position) {
    if (a != NULL) {
        printf("\033[1;33mNiveau %d - %s = %c\033[0m\n", niveau, position, a->c);
        dicoAfficherAvecCommentaires(a->FG, niveau + 1, "Gauche");
        dicoAfficherAvecCommentaires(a->FD, niveau + 1, "Droite");
    }
}


/*************************************************************************/


int main()
{
    Mot *dictionnaire = NULL;
    int nombreMots;
    TArbre racine = NULL;
    int i = 0;

    do {
        printf("\033[1;32m \tEntrez le nombre de mots pour le dictionnaire : \033[0m");
        scanf("%d", &nombreMots);
        getchar(); // Absorber le retour à la ligne
    } while (nombreMots <= 0);

    // Saisie des mots avec contrôle de la validité
    for (int i = 0; i < nombreMots; i++) {
        char mot[50];
        int validInput = 0;

        // Boucle de saisie avec contrôle de validité
        while (!validInput) {
            printf("\033[1;32m \tEntrez le mot %d : \033[0m", i + 1);
            fgets(mot, sizeof(mot), stdin);
            mot[strcspn(mot, "\n")] = '\0'; // Supprimer le caractère de retour à la ligne de fgets

            // Vérifier si la chaîne est alphabétique et de longueur supérieure à 0
            int j, isAlphabetic = 1;
            for (j = 0; j < strlen(mot); j++) {
                if (!isalpha(mot[j])) {
                    isAlphabetic = 0;
                    break;
                }
            }

            if (isAlphabetic && j > 0) {
                validInput = 1;
            } else {
                printf("\033[1;31m \tErreur : Veuillez entrer une chaine alphabetique de longueur superieure a 0.\033[0m\n");
            }
        }

        // Ajouter le mot au dictionnaire
        dictionnaire = ajouterMot(dictionnaire, mot);
    }

    while (dictionnaire != NULL) {
        InsererMotArbre(dictionnaire->mot, racine, NULL);
        dictionnaire = dictionnaire->suivant;
    }

    // Sauvegarder le dictionnaire dans le fichier "dict.txt"
    sauvegarderDictionnaire(dictionnaire, "dict.txt");
    printf("\033[1;32mAffichage de l'arbre binaire de recherche avec des commentaires : \033[0m\n");
    dicoAfficherAvecCommentaires(racine, 0, "Racine");
    
    // Libérer la mémoire allouée pour le dictionnaire
    libererDictionnaire(dictionnaire);

    return 0;
}
