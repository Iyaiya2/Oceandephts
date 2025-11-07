#include <stdio.h>
#include <stdlib.h>
#include "joueur.h"

void initialiser_plongeur(Plongeur *p) {
    p->points_de_vie_max = 100;
    p->points_de_vie = 87;
    p->niveau_oxygene_max = 100;
    p->niveau_oxygene = 58;
    p->niveau_fatigue = 3;
    p->perles = 42;
    p->profondeur = 247;
}

static void afficher_barre(int valeur, int max) {
    int largeur = 40; // La taille totale de votre barre (40 caractères)

    // Calcul de la proportion remplie (nombre de caractères pleins)
    int remplie = (valeur * largeur) / max;

    // S'assurer que 'remplie' ne dépasse pas la 'largeur'
    if (remplie > largeur) remplie = largeur;

    // --- 1. Affichage de la partie remplie ---
    for (int i = 0; i < remplie; i++) {
        printf("|"); // Utilisation du caractère '#' pour la partie pleine
    }

    // --- 2. Affichage de la partie vide ---
    for (int i = remplie; i < largeur; i++) {
        printf("."); // Utilisation du caractère '.' (ou ' ') pour la partie vide
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
    // La fatigue a un max fixe de 5
    afficher_barre(p->niveau_fatigue, 5);
    printf("] %d/5\n", p->niveau_fatigue);

    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}

int attaquer_creature(Plongeur *p, CreatureMarine *c) {
    // Règle 3: Calcul des dégâts (avec variabilité)
    int attaque_min = 15;
    int attaque_max = 25;

    int degats_base = rand() % (attaque_max - attaque_min + 1) + attaque_min;
    int degats = degats_base - c->defense;

    if (degats < 1) degats = 1; // Minimum garanti

    // Application des dégâts à la créature
    c->points_de_vie_actuels -= degats;
    if (c->points_de_vie_actuels < 0) {
        c->points_de_vie_actuels = 0;
    }

    // Règle 2: Consommation d'oxygène (Attaque normale) : -2 à -4
    int conso_oxygene = rand() % (4 - 2 + 1) + 2;
    p->niveau_oxygene -= conso_oxygene;

    // Règle 1: Augmentation de la fatigue (+1, max 5)
    if (p->niveau_fatigue < 5) {
        p->niveau_fatigue += 1;
    }

    // Affichage pour le journal de combat
    printf("Vous attaquez %s et infligez %d degats !\n", c->nom, degats);
    printf("Oxygene consomme: -%d (action de combat). Fatigue augmentee: +1 (effort physique).\n", conso_oxygene);

    return degats;
}
