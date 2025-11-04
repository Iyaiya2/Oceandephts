#ifndef JOUEUR_H
#define JOUEUR_H

#include "creatures.h"

typedef struct {
    int points_de_vie;
    int points_de_vie_max;
    int niveau_oxygene;
    int niveau_oxygene_max;
    int niveau_fatigue;
    int perles;
    int profondeur;
} Plongeur;

void initialiser_plongeur(Plongeur *p);
void afficher_interface(const Plongeur *p);
int attaquer_creature(Plongeur *p, CreatureMarine *c);

#endif
