#include <stdio.h>
#include <stdlib.h>
#include "combat.h"

void attaque_creature(Plongeur *p, CreatureMarine c) {
    if (!c.est_vivant) return;
    int degats = rand() % (c.attaque_maximale - c.attaque_minimale + 1) + c.attaque_minimale;
    printf("🦈 %s vous attaque et inflige %d degats !\n", c.nom, degats);
    p->points_de_vie -= degats;
    if (p->points_de_vie < 0) p->points_de_vie = 0;
}

void combat(Plongeur *p, CreatureMarine creatures[], int nb) {
    int choix;
    do {
        afficher_interface(p);
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        for (int i = 0; i < nb; i++) {
            if (creatures[i].est_vivant)
                printf("%s (%d/%d PV)\n", creatures[i].nom,
                       creatures[i].points_de_vie_actuels, creatures[i].points_de_vie_max);
        }
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("Actions disponibles:\n");
        printf("1 - Attaquer avec harpon\n");
        printf("2 - Utiliser competence marine\n");
        printf("3 - Consommer objet\n");
        printf("4 - Terminer le tour\n> ");
        scanf("%d", &choix);

        if (choix == 1)
            attaquer_creature(p, &creatures[0]);

        for (int i = 0; i < nb; i++)
            if (creatures[i].est_vivant)
                attaque_creature(p, creatures[i]);

    } while (p->points_de_vie > 0);
}
