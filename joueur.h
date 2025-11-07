#ifndef JOUEUR_H
#define JOUEUR_H

#include "creatures.h"

// Structure représentant le plongeur (le joueur)
typedef struct {
    int points_de_vie;
    int points_de_vie_max;
    int niveau_oxygene;
    int niveau_oxygene_max;
    int niveau_fatigue;
    int perles;
    int profondeur;
    char nom_arme[30]; // 🔹 optionnel : pour afficher le nom de l’arme ("harpon")
} Plongeur;

// Initialise les valeurs de départ du plongeur
void initialiser_plongeur(Plongeur *p);

// Affiche l'état actuel du joueur (PV, oxygène, fatigue, etc.)
void afficher_interface(const Plongeur *p);

// Fonction d'attaque du plongeur contre une créature
int attaquer_creature(Plongeur *p, CreatureMarine *c);

#endif
