#ifndef JOUEUR_H
#define JOUEUR_H

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
void afficher_interface(Plongeur p);
int attaquer_creature(Plongeur *p, struct CreatureMarine *c);

#endif
