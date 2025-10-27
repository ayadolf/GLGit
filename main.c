#include <stdio.h>
#include <stdlib.h>
#include "enzyme.h"
#include "pathway.h"
#include "liste.h"

void afficheMenu();
void saisie(liste);
void affichage(liste);
void ouvrir(liste, const char *);
void sauvegarder(liste);

int main() {
    liste list_pathway = creerliste();
    int reponse;
    char nom_fichier[100];

    while (1) {
        afficheMenu();
        printf("Votre choix : ");
        scanf("%d", &reponse);

        switch (reponse) {
        case 1:
            saisie(list_pathway);
            break;
        case 2:
            affichage(list_pathway);
            break;
        case 3:
            sauvegarder(list_pathway);
            break;
        case 4:
            printf("Nom du fichier à ouvrir : ");
            scanf("%99s", nom_fichier);
            ouvrir(list_pathway, nom_fichier);
            break;
        case 5:
            list_pathway = supprimer(list_pathway);
            break;
        case 0:
            printf("Fin du programme.\n");
            return 0;
        default:
            printf("Choix invalide.\n");
        }
    }
}

void saisie(liste list_pathway) {
    int nombre;
    printf("Combien de voies ? ");
    scanf("%d", &nombre);

    for (int i = 0; i < nombre; i++) {
        ptr_pathway item = creerpathway();
        saisie_voie(item);
        ajouter(list_pathway, item);
    }
}

void affichage(liste list_pathway) {
    if (case_vide(list_pathway)) {
        printf("Aucune voie à afficher.\n");
    } else {
        afficherliste(list_pathway);
    }
}

void ouvrir(liste list_pathway, const char *nom) {
    FILE *fichier = fopen(nom, "r");
    if (!fichier) {
        perror("Erreur ouverture fichier");
        return;
    }

    while (!feof(fichier)) {
        ptr_pathway item = creerpathway();
        if (!ouvrir_voie(item, fichier)) {
            liberer_pathway(item);
            break;
        }
        ajouter(list_pathway, item);
    }

    fclose(fichier);
    printf("Chargement terminé ✅\n");
}

void sauvegarder(liste list_pathway) {
    if (case_vide(list_pathway)) {
        printf("Rien à sauvegarder.\n");
        return;
    }

    FILE *out = fopen("resul.txt", "w");
    if (!out) {
        perror("Erreur création fichier");
        return;
    }

    liste tmp = list_pathway;
    while (!case_vide(tmp)) {
        sauvegarder_voie(retourcontenu(tmp), out);
        tmp = case_suivante(tmp);
    }

    fclose(out);
    printf("Sauvegarde réalisée ✅ (resul.txt)\n");
}

void afficheMenu() {
    printf("\n===== Programme Enzyme =====\n");
    printf("1. Saisir informations\n");
    printf("2. Afficher\n");
    printf("3. Sauvegarder\n");
    printf("4. Ouvrir un fichier\n");
    printf("5. Supprimer voie\n");
    printf("0. Quitter\n");
}
