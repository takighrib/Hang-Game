#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dict.h"

int comparerMots(const char *mot1, const char *mot2)
{
    return strcmp(mot1, mot2);
}

Mot *ajouterMot(Mot *dictionnaire, const char *mot)
{
    Mot *nouveauMot = (Mot *)malloc(sizeof(Mot));
    if (nouveauMot == NULL)
    {
        perror("Erreur d'allocation mémoire");
        exit(EXIT_FAILURE);
    }

    // Copier le mot dans la structure
    strncpy(nouveauMot->mot, mot, sizeof(nouveauMot->mot) - 1);
    nouveauMot->mot[sizeof(nouveauMot->mot) - 1] = '\0';

    // Cas où le dictionnaire est vide ou le premier mot doit être inséré en premier
    if (dictionnaire == NULL || comparerMots(mot, dictionnaire->mot) < 0)
    {
        nouveauMot->suivant = dictionnaire;
        return nouveauMot;
    }

    // Cas général d'insertion dans l'ordre alphabétique
    Mot *precedent = NULL;
    Mot *courant = dictionnaire;

    while (courant != NULL && comparerMots(mot, courant->mot) > 0)
    {
        precedent = courant;
        courant = courant->suivant;
    }

    nouveauMot->suivant = courant;

    // Mettre à jour le pointeur du mot précédent ou la tête du dictionnaire
    if (precedent != NULL)
    {
        precedent->suivant = nouveauMot;
    }
    else
    {
        dictionnaire = nouveauMot;
    }

    return dictionnaire;
}

Mot *rechercherMot(Mot *dictionnaire, const char *mot)
{
    while (dictionnaire != NULL)
    {
        if (strcmp(dictionnaire->mot, mot) == 0)
        {
            return dictionnaire; // Le mot a été trouvé
        }
        dictionnaire = dictionnaire->suivant;
    }
    return NULL; // Le mot n'a pas été trouvé
}

void sauvegarderDictionnaire(Mot *dictionnaire, const char *nomFichier)
{
    FILE *fichier = fopen(nomFichier, "w");
    if (fichier == NULL)
    {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    while (dictionnaire != NULL)
    {
        fprintf(fichier, "%s\n", dictionnaire->mot);
        dictionnaire = dictionnaire->suivant;
    }

    fclose(fichier);
}


Mot *supprimerMot(Mot *dictionnaire, const char *mot, const char *nomFichier)
{
    Mot *precedent = NULL;
    Mot *courant = dictionnaire;

    // Recherche du mot à supprimer
    while (courant != NULL)
    {
        if (strcmp(courant->mot, mot) == 0)
        {
            // Le mot a été trouvé, le supprimer de la liste
            if (precedent != NULL)
            {
                precedent->suivant = courant->suivant;
            }
            else
            {
                dictionnaire = courant->suivant;
            }
            free(courant);
            sauvegarderDictionnaire(dictionnaire, nomFichier);
            return dictionnaire; // Retourner la tête de la nouvelle liste
        }

        precedent = courant;
        courant = courant->suivant;
    }

    return dictionnaire; // Retourner la tête de la liste inchangée
}


void afficherDictionnaire(Mot *dictionnaire)
{
    printf("\033[1;33m \tDictionnaire:\033[0m\n");
    while (dictionnaire != NULL)
    {
        printf("%s\n", dictionnaire->mot);
        dictionnaire = dictionnaire->suivant;
    }
}


void libererDictionnaire(Mot *dictionnaire)
{
    Mot *courant = dictionnaire;
    while (courant != NULL)
    {
        Mot *suivant = courant->suivant;
        free(courant);
        courant = suivant;
    }
}

Mot *chargerDictionnaire(const char *nomFichier)
{
    FILE *fichier = fopen(nomFichier, "r");
    if (fichier == NULL)
    {
        // Si le fichier n'existe pas, retourner un dictionnaire vide
        return NULL;
    }

    Mot *dictionnaire = NULL;
    char mot[50];

    while (fgets(mot, sizeof(mot), fichier) != NULL)
    {
        mot[strcspn(mot, "\n")] = '\0'; // Supprimer le caractère de retour à la ligne
        dictionnaire = ajouterMot(dictionnaire, mot);
    }

    fclose(fichier);

    return dictionnaire;
}
