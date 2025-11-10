// joueur.h

#ifndef JOUEUR_H
#define JOUEUR_H

#include "creatures.h" // Nécessaire pour Plongeur vs Creature

typedef struct {
    int points_de_vie_max;
    int points_de_vie;
    int niveau_oxygene_max;
    int niveau_oxygene;
    int niveau_fatigue; // 0 (reposé) à 5 (épuisé)
    int perles;
    int profondeur;
    int est_paralyse; // 1 si paralysé (effet Méduse), 0 sinon
} Plongeur;

void initialiser_plongeur(Plongeur *p);
void afficher_barre(int valeur, int max);
void afficher_interface(const Plongeur *p);

// MODIFIÉ : Ajout de pointeurs de sortie pour communiquer la conso O2 et la fatigue
int attaquer_creature(Plongeur *p, CreatureMarine *c, int *conso_oxygene, int *fatigue_augmentee);

#endif