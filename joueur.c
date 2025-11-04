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
    int largeur = 40;
    int remplie = (valeur * largeur) / max;
    for (int i = 0; i < largeur; i++) {
        if (i < remplie) printf("|");
        else printf("|");
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
}

int attaquer_creature(Plongeur *p, CreatureMarine *c) {
    int degats_base = rand() % (25 - 15 + 1) + 15;
    int degats = degats_base - c->defense;
    if (degats < 1) degats = 1;

    c->points_de_vie_actuels -= degats;
    if (c->points_de_vie_actuels < 0) c->points_de_vie_actuels = 0;

    printf("💥 Vous attaquez %s et infligez %d degats !\n", c->nom, degats);
    return degats;
}
