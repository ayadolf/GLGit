#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "enzyme.h"

struct enzyme {
    char *nom;
    int poids;
};

// Création d'une enzyme
ptr_enzyme creer_enzyme(const char *_nom, int _poids) {
    ptr_enzyme enz = malloc(sizeof(struct enzyme));
    if (!enz) { perror("malloc enz"); exit(EXIT_FAILURE); }

    enz->nom = strdup(_nom); // allocation + copie automatique
    if (!enz->nom) { perror("strdup"); exit(EXIT_FAILURE); }

    enz->poids = _poids;
    return enz;
}

// Saisie utilisateur
ptr_enzyme saisie_enzyme() {
    char nom[30];
    int poids;

    printf("Veuillez entrer le nom : ");
    scanf("%29s", nom);
    printf("Veuillez entrer le poids : ");
    scanf("%d", &poids);

    return creer_enzyme(nom, poids);
}

// Lecture depuis un fichier
ptr_enzyme lire_enzyme_fichier(FILE *f) {
    char nom[30];
    int poids;

    if (fscanf(f, "%29s %d", nom, &poids) != 2) {
        return NULL; // Fin du fichier ou erreur
    }
    return creer_enzyme(nom, poids);
}

// Affichage
void affiche(ptr_enzyme enz) {
    if (!enz) return;
    printf("Enzyme: %s, poids : %d\n", enz->nom, enz->poids);
}

// Sauvegarde dans fichier
void sauvegarde(ptr_enzyme enz, FILE *out) {
    if (!enz || !out) return;
    fprintf(out, "%s %d\n", enz->nom, enz->poids);
}

// Libération mémoire
void liberer_enzyme(ptr_enzyme enz) {
    if (enz) {
        free(enz->nom);
        free(enz);
    }
}
