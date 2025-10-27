#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "enzyme.h"

struct enzyme {
    char *nom;
    int poids;
};

// Crée une enzyme avec nom et poids
ptr_enzyme creer_enzyme(char *_nom, int _poids) {
    ptr_enzyme enz = (ptr_enzyme) malloc(sizeof(struct enzyme));
    if (!enz) { perror("malloc enz"); exit(1); }

    enz->nom = strdup(_nom);  // allocation + copie
    if (!enz->nom) { perror("strdup"); exit(1); }

    enz->poids = _poids;
    return enz;
}

// Saisie manuelle de l'enzyme
ptr_enzyme saisie_enzyme() {
    char nom[30];
    int poids;

    printf("Veuillez entrer le nom : ");
    scanf("%29s", nom);
    printf("Veuillez entrer le poids : ");
    scanf("%d", &poids);

    return creer_enzyme(nom, poids);
}

// Lecture d'une enzyme depuis un fichier
ptr_enzyme lire_enzyme_fichier(FILE *f) {
    char nom[30];
    int poids;
    if (fscanf(f, "%29s %d", nom, &poids) != 2) {
        return NULL; // fin de fichier ou erreur de lecture
    }
    return creer_enzyme(nom, poids);
}

// Affiche l'enzyme
void affiche(ptr_enzyme enz) {
    if (!enz) return;
    printf("Enzyme: %s, poids : %d\n", enz->nom, enz->poids);
}

// Sauvegarde l'enzyme dans un fichier
void sauvegarde(ptr_enzyme enz, FILE* out) {
    if (!enz || !out) return;
    fprintf(out, "%s %d\n", enz->nom, enz->poids);
}
