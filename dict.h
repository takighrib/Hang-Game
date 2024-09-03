#ifndef DICT_H
#define DICT_H

// Structure pour représenter un mot dans le dictionnaire
typedef struct Mot
{
    char mot[50];
    struct Mot *suivant;
} Mot;

// Fonction pour comparer deux chaînes de caractères (utilisée pour le tri)
int comparerMots(const char *mot1, const char *mot2);

// Fonction pour ajouter un mot au dictionnaire tout en maintenant l'ordre alphabétique
Mot *ajouterMot(Mot *dictionnaire, const char *mot);

// Fonction pour rechercher un mot dans le dictionnaire
Mot *rechercherMot(Mot *dictionnaire, const char *mot);

// Fonction pour sauvegarder le dictionnaire dans un fichier
void sauvegarderDictionnaire(Mot *dictionnaire, const char *nomFichier);

// Fonction pour supprimer un mot du dictionnaire
Mot *supprimerMot(Mot *dictionnaire, const char *mot, const char *nomFichier);

// Fonction pour afficher le dictionnaire
void afficherDictionnaire(Mot *dictionnaire);

// Fonction pour libérer la mémoire allouée pour le dictionnaire
void libererDictionnaire(Mot *dictionnaire);

// Fonction pour charger le dictionnaire depuis un fichier
Mot *chargerDictionnaire(const char *nomFichier);

#endif 
