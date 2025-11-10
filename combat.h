// combat.h

#ifndef COMBAT_H
#define COMBAT_H

#include "joueur.h"
#include "creatures.h"

// Prototypes des fonctions utilitaires
int calculer_attaques_max(int niveau_fatigue);
void consommer_oxygene_auto(Plongeur *p);
void attaque_creature(Plongeur *p, CreatureMarine c); // L'attaque de la creature sur le plongeur
void combat(Plongeur *p, CreatureMarine creatures[], int nb);

// MODIFIÉ : Ajout des paramètres O2/Fatigue pour l'affichage précis
void afficher_interface_combat(Plongeur *p, CreatureMarine *c, int degats_infliges, int conso_oxygene, int fatigue_augmentee);

// Fonctions de tri pour l'Etape 3
void echanger_creatures(CreatureMarine *a, CreatureMarine *b);
void trier_creatures_par_vitesse(CreatureMarine creatures[], int nb);

#endif