#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h> // Nécessaire pour strcpy
#include "joueur.h"
#include "creatures.h"
#include "combat.h"

int generer_creatures(CreatureMarine creatures[], int profondeur) {
    int nb_creatures = rand() % 4 + 1; // entre 1 et 4

    for (int i = 0; i < nb_creatures; i++) {
        int type = rand() % 5;
        CreatureMarine c;
        c.id = i;
        c.est_vivant = 1;

        // Option : modifier la difficulté en fonction de la profondeur
        int bonus = profondeur / 10; // exemple : +1 attaque tous les 10 niveaux

        switch (type) {
            case 0:
                strcpy(c.nom, "Kraken");
                c.points_de_vie_max = 120 + rand() % 61 + bonus * 10;
                c.attaque_minimale = 25 + bonus;
                c.attaque_maximale = 40 + bonus;
                c.defense = 10 + bonus;
                c.vitesse = 5;
                strcpy(c.effet_special, "double_attaque");
                break;

            case 1:
                strcpy(c.nom, "Requin-Tigre");
                c.points_de_vie_max = 60 + rand() % 41 + bonus * 5;
                c.attaque_minimale = 15 + bonus;
                c.attaque_maximale = 25 + bonus;
                c.defense = 8 + bonus;
                c.vitesse = 7;
                strcpy(c.effet_special, "frenesie");
                break;

            case 2:
                strcpy(c.nom, "Meduse Bleue");
                c.points_de_vie_max = 20 + rand() % 21 + bonus * 3;
                c.attaque_minimale = 8 + bonus;
                c.attaque_maximale = 15 + bonus;
                c.defense = 3;
                c.vitesse = 4;
                strcpy(c.effet_special, "paralysie");
                break;

            case 3:
                strcpy(c.nom, "Poisson-Epee");
                c.points_de_vie_max = 70 + rand() % 21 + bonus * 5;
                c.attaque_minimale = 18 + bonus;
                c.attaque_maximale = 28 + bonus;
                c.defense = 5 + bonus;
                c.vitesse = 6;
                strcpy(c.effet_special, "ignore_def");
                break;

            case 4:
                strcpy(c.nom, "Crabe Geant");
                c.points_de_vie_max = 80 + rand() % 41 + bonus * 5;
                c.attaque_minimale = 12 + bonus;
                c.attaque_maximale = 20 + bonus;
                c.defense = 12 + bonus;
                c.vitesse = 3;
                strcpy(c.effet_special, "carapace");
                break;
        }

        c.points_de_vie_actuels = c.points_de_vie_max;
        creatures[i] = c;
    }

    return nb_creatures;
}

void afficher_creature(const CreatureMarine *c) {
    printf("%s (%d/%d PV) ATK: %d-%d DEF: %d VIT: %d Effet: %s\n",
           c->nom,
           c->points_de_vie_actuels,
           c->points_de_vie_max,
           c->attaque_minimale,
           c->attaque_maximale,
           c->defense,
           c->vitesse,
           c->effet_special);
}

