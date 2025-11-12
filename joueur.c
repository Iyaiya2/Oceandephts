// joueur.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "joueur.h"
#include "creatures.h"
#include "inventaire.h" // <-- Ajouté pour pouvoir initialiser l'inventaire

void initialiser_plongeur(Plongeur *p) {
    p->points_de_vie_max = 100;
    p->points_de_vie = 100;
    p->niveau_oxygene_max = 100;
    p->niveau_oxygene = 100;
    p->niveau_fatigue = 0;
    p->perles = 42;
    p->profondeur = 247;
    p->est_paralyse = 0;

    // --- Initialisation de l'inventaire directement ---
    memset(&p->inventaire, 0, sizeof(Inventaire));

    strcpy(p->inventaire.inventaire[0].nom, "Harpon Rouille");
    p->inventaire.inventaire[0].attaque = 12;
    p->inventaire.inventaire[0].quantite = 1;

    strcpy(p->inventaire.inventaire[1].nom, "Combi Neoprene");
    p->inventaire.inventaire[1].defense = 5;
    p->inventaire.inventaire[1].quantite = 1;

    strcpy(p->inventaire.inventaire[2].nom, "Capsule O2");
    p->inventaire.inventaire[2].oxygene = 20;
    p->inventaire.inventaire[2].quantite = 3;

    strcpy(p->inventaire.inventaire[3].nom, "Trousse de soin");
    p->inventaire.inventaire[3].pv = 25;
    p->inventaire.inventaire[3].quantite = 2;

    strcpy(p->inventaire.inventaire[4].nom, "Stimulant");
    p->inventaire.inventaire[4].fatigue = 2;
    p->inventaire.inventaire[4].quantite = 2;

    p->inventaire.perles = p->perles;
}


void afficher_barre(int valeur, int max) {
    int largeur = 40;
    int remplie = (valeur * largeur) / max;

    if (remplie > largeur) remplie = largeur;

    for (int i = 0; i < remplie; i++) {
        printf("|");
    }

    for (int i = remplie; i < largeur; i++) {
        printf(".");
    }
}

void afficher_interface(const Plongeur *p) {
    printf("\nOceanDepths - Profondeur: -%dm\tPerles: %d\n", p->profondeur, p->perles);

    printf("Vie     [");
    afficher_barre(p->points_de_vie, p->points_de_vie_max);
    printf("] %d/%d\n", p->points_de_vie, p->points_de_vie_max);

    printf("Oxygene [");
    afficher_barre(p->niveau_oxygene, p->niveau_oxygene_max);
    printf("] %d/%d\n", p->niveau_oxygene, p->niveau_oxygene_max);

    printf("Fatigue [");
    afficher_barre(p->niveau_fatigue, 5);
    printf("] %d/5\n", p->niveau_fatigue);

    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    if (p->niveau_oxygene <= 10 && p->points_de_vie > 0) {
        printf("!!! ALERTE CRITIQUE : Oxygene faible (< 10). Danger de mort imminent. !!!\n");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    }
}

// MODIFIÉ : Utilise des pointeurs de sortie pour la conso O2 et la fatigue
int attaquer_creature(Plongeur *p, CreatureMarine *c, int *conso_oxygene, int *fatigue_augmentee) {
    int attaque_min = 15;
    int attaque_max = 25;

    int degats_base = rand() % (attaque_max - attaque_min + 1) + attaque_min;

    int degats = degats_base - c->defense;

    // 1. Appliquer l'effet du Crabe Geant
    if (strcmp(c->nom, "Crabe Geant") == 0) {
        degats = (int)(degats * 0.80);
        printf("   >> Crabe Geant: Carapace durcie! Degats reduits de 20%%.\n");
    }

    // 2. Garantir au moins 1 degat
    if (degats < 1) degats = 1;

    // Application des degats a la creature
    c->points_de_vie_actuels -= degats;
    if (c->points_de_vie_actuels < 0) {
        c->points_de_vie_actuels = 0;
    }

    // Règle 2: Consommation d'oxygene (-2 a -4)
    *conso_oxygene = rand() % (4 - 2 + 1) + 2; // Stocke la conso O2
    p->niveau_oxygene -= *conso_oxygene;

    // Règle 1: Augmentation de la fatigue (+1)
    *fatigue_augmentee = 0; // Initialisation
    if (p->niveau_fatigue < 5) {
        p->niveau_fatigue += 1;
        *fatigue_augmentee = 1; // Stocke l'augmentation de fatigue (1 ou 0)
    }

    return degats;
}
