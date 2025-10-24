#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "creatures.h"

int generer_creatures(CreatureMarine creatures[], int profondeur) {
    srand(time(NULL));
    int nb_creatures = rand() % 4 + 1; // 1 à 4 créatures

    for (int i = 0; i < nb_creatures; i++) {
        int type = rand() % 5;
        CreatureMarine c;
        c.id = i;
        c.est_vivant = 1;

        switch (type) {
            case 0:
                strcpy(c.nom, "Kraken");
                c.points_de_vie_max = 120 + rand() % 61;
                c.attaque_minimale = 25;
                c.attaque_maximale = 40;
                c.defense = 10;
                c.vitesse = 5;
                strcpy(c.effet_special, "double_attaque");
                break;
            case 1:
                strcpy(c.nom, "Requin-Tigre");
                c.points_de_vie_max = 60 + rand() % 41;
                c.attaque_minimale = 15;
                c.attaque_maximale = 25;
                c.defense = 8;
                c.vitesse = 7;
                strcpy(c.effet_special, "frénésie");
                break;
            case 2:
                strcpy(c.nom, "Méduse Bleue");
                c.points_de_vie_max = 20 + rand() % 21;
                c.attaque_minimale = 8;
                c.attaque_maximale = 15;
                c.defense = 3;
                c.vitesse = 4;
                strcpy(c.effet_special, "paralysie");
                break;
            case 3:
                strcpy(c.nom, "Poisson-Épée");
                c.points_de_vie_max = 70 + rand() % 21;
                c.attaque_minimale = 18;
                c.attaque_maximale = 28;
                c.defense = 5;
                c.vitesse = 6;
                strcpy(c.effet_special, "ignore_def");
                break;
            case 4:
                strcpy(c.nom, "Crabe Géant");
                c.points_de_vie_max = 80 + rand() % 41;
                c.attaque_minimale = 12;
                c.attaque_maximale = 20;
                c.defense = 12;
                c.vitesse = 3;
                strcpy(c.effet_special, "carapace");
                break;
        }

        c.points_de_vie_actuels = c.points_de_vie_max;
        creatures[i] = c;
    }
    return nb_creatures;
}

void afficher_creature(CreatureMarine c) {
    printf("%s (%d/%d PV)\n", c.nom, c.points_de_vie_actuels, c.points_de_vie_max);
}
