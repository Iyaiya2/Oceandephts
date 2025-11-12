#ifndef JOUEUR_H
#define JOUEUR_H

#include "creatures.h"  // Nécessaire pour Plongeur vs Creature
#include "inventaire.h"  // Pour inclure l'Inventaire dans le Plongeur

#include "inventaire.h"

typedef struct {
    int points_de_vie_max;
    int points_de_vie;
    int niveau_oxygene_max;
    int niveau_oxygene;
    int niveau_fatigue;
    int perles;
    int profondeur;
    int est_paralyse;
    Inventaire inventaire;  // <-- ajouter ici
} Plongeur;


// Initialisation et affichage
void initialiser_plongeur(Plongeur *p);
void afficher_barre(int valeur, int max);
void afficher_interface(const Plongeur *p);

// Attaque vers une créature (pointeurs pour conso O2 et fatigue)
int attaquer_creature(Plongeur *p, CreatureMarine *c, int *conso_oxygene, int *fatigue_augmentee);

#endif
