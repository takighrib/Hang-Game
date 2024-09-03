#include <stdio.h>
#include <stdlib.h>

// Structure représentant un nœud dans un arbre binaire
struct Node {
    char c;               
    int occ;             
    struct Node *FG;      
    struct Node *FD;     
};


typedef struct Node Node;
typedef Node *TArbre;      // TArbre est un pointeur vers la structure Node

// Fonction pour créer un arbre vide
TArbre arbreConsVide() {
    return NULL;
}

// Fonction pour vérifier si un arbre est vide
int arbreEstVide(TArbre a) {
    return (a == NULL);
}

// Fonction pour créer un nouveau nœud
TArbre createNode(char c, int n, TArbre fg, TArbre fd) {
    TArbre newNode = malloc(sizeof(Node)); 
    if (newNode == NULL) {
        perror("Erreur d'allocation mémoire");
        exit(EXIT_FAILURE);
    }

    newNode->c = c;
    newNode->occ = n;
    newNode->FD = fd;
    newNode->FG = fg;
    return newNode;
}

// Fonction pour obtenir le caractère de la racine d'un arbre
char arbreRacineLettre(TArbre a) {
    return a->c;
}

// Fonction pour obtenir le nombre d'occurrences de la racine d'un arbre
int arbreRacineNbOcc(TArbre a) {
    return a->occ;
}

// Fonction récursive pour calculer le nombre d'occurrences d'un caractère dans un arbre
int nboccur(TArbre a, char c) {
    if (a == NULL)
        return 0;
    else if (a->c == c)
        return (1 + nboccur(a->FD, c) + nboccur(a->FG, c));
    else
        return (nboccur(a->FD, c) + nboccur(a->FG, c));
}

// Fonction pour obtenir le fils gauche d'un nœud
TArbre arbreFilsGauche(TArbre a) {
    return a->FG;
}

// Fonction pour obtenir le fils droit d'un nœud
TArbre arbreFilsDroit(TArbre a) {
    return a->FD;
}

// Fonction récursive pour supprimer tous les nœuds d'un arbre
void arbreSuppr(TArbre a) {
    if (!arbreEstVide(a->FD)) {
        arbreSuppr(a->FD);
    }
    if (!arbreEstVide(a->FG)) {
        arbreSuppr(a->FG);
    }
    free(a);
}

// Fonction pour libérer tous les nœuds de l'arbre (sans libérer l'arbre lui-même)
void libererTousNoeuds(TArbre a) {
    if (a != NULL) {
        libererTousNoeuds(a->FG);
        libererTousNoeuds(a->FD);
        free(a);
    }
}
