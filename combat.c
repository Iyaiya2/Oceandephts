#include <stdio.h>
#include <stdlib.h>
#include "combat.h"
#include "joueur.h"
#include "creatures.h"

// --- Fonction pour afficher l'interface de combat ---
void afficher_interface_combat(Plongeur *p, CreatureMarine *c, int degats_infliges, int degats_recus) {
    char nom_creature[32];
    snprintf(nom_creature, sizeof(nom_creature), "%s", c->nom);

    printf("\n+---------------------------------------------------------+\n");
    printf("|  Vous attaquez %-43s|\n", nom_creature);
    printf("|                                                         |\n");
    printf("|     PLONGEUR              VS         %-12s |\n", nom_creature);
    printf("|                                                        |\n");
    printf("|    =======>                       <=========           |\n");
    printf("|                                                        |\n");
    printf("|  Degats infliges : %-3d points                         |\n", degats_infliges);
    printf("|  %s riposte ! Vous perdez %-3d points de vie           |\n", nom_creature, degats_recus);
    printf("+---------------------------------------------------------+\n");

    printf("Oxygene consomme : -3 (action de combat)\n");
    printf("Fatigue augmentee : +1 (effort physique)\n\n");
}

// --- Regle 1 : Limite d'attaques selon la fatigue ---
int calculer_attaques_max(int niveau_fatigue) {
    if (niveau_fatigue <= 1) {
        return 3;
    } else if (niveau_fatigue <= 3) {
        return 2;
    } else {
        return 1;
    }
}

// --- Regle 2 : Consommation automatique d'oxygene ---
void consommer_oxygene_auto(Plongeur *p) {
    int conso_auto = 5;
    p->niveau_oxygene -= conso_auto;

    printf("\nConsommation automatique d'oxygene : -%d.\n", conso_auto);

    if (p->niveau_oxygene <= 0) {
        p->niveau_oxygene = 0;
        p->points_de_vie -= 5;
        if (p->points_de_vie < 0) p->points_de_vie = 0;
        printf("OXYGENE EPUISE ! Vous perdez 5 points de vie par asphyxie.\n");
    }
}

// --- Attaque d'une creature vers le plongeur ---
void attaque_creature(Plongeur *p, CreatureMarine c) {
    if (!c.est_vivant) return;
    int degats = rand() % (c.attaque_maximale - c.attaque_minimale + 1) + c.attaque_minimale;
    printf("%s vous attaque et inflige %d degats !\n", c.nom, degats);
    p->points_de_vie -= degats;
    if (p->points_de_vie < 0) p->points_de_vie = 0;
}

// --- Fonction principale de combat ---
void combat(Plongeur *p, CreatureMarine creatures[], int nb) {
    int choix;
    int cible_id;

    while (p->points_de_vie > 0) {
        afficher_interface(p);

        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        for (int i = 0; i < nb; i++) {
            if (creatures[i].est_vivant)
                printf("%d - %s (%d/%d PV)\n", i + 1, creatures[i].nom,
                       creatures[i].points_de_vie_actuels, creatures[i].points_de_vie_max);
        }
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

        int max_attaques = calculer_attaques_max(p->niveau_fatigue);
        int attaques_effectuees = 0;

        while (attaques_effectuees < max_attaques) {
            printf("Actions disponibles (Attaques restantes : %d/%d):\n", max_attaques - attaques_effectuees, max_attaques);
            printf("1 - Attaquer avec le harpon\n2 - Utiliser une competence marine\n3 - Utiliser un objet\n4 - Terminer le tour\n> ");
            if (scanf("%d", &choix) != 1) { }

            if (choix == 1) {
                printf("Ciblez une creature (ID) : > ");
                if (scanf("%d", &cible_id) != 1) { }
                cible_id--;

                if (cible_id >= 0 && cible_id < nb && creatures[cible_id].est_vivant) {
                    int pv_avant = creatures[cible_id].points_de_vie_actuels;
                    int pv_joueur_avant = p->points_de_vie;

                    attaquer_creature(p, &creatures[cible_id]);
                    attaques_effectuees++;

                    int degats_infliges = pv_avant - creatures[cible_id].points_de_vie_actuels;
                    int degats_recus = pv_joueur_avant - p->points_de_vie;

                    afficher_interface_combat(p, &creatures[cible_id], degats_infliges, degats_recus);

                } else {
                    printf("Cible invalide ou creature deja vaincue.\n");
                }
            } else if (choix == 4) {
                printf("Fin du tour du plongeur.\n");
                break;
            } else {
                printf("Action non valide ou non implemente.\n");
            }
        }

        if (attaques_effectuees >= max_attaques) {
            printf("\nLimite d'attaques (Fatigue) atteinte pour ce tour. Fin de l'action du plongeur.\n");
        }

        consommer_oxygene_auto(p);

        for (int i = 0; i < nb; i++)
            if (creatures[i].est_vivant)
                attaque_creature(p, creatures[i]);

        if (p->niveau_fatigue > 0) {
            p->niveau_fatigue -= 1;
            printf("Recuperation de la fatigue : -1 niveau.\n");
        }
    }

    printf("\nLe combat est termine.\n");
}
