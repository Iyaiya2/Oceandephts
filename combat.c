// combat.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Nécessaire pour strcmp
#include "combat.h"
#include "joueur.h"
#include "creatures.h"

// ----------------------------------------------------
// NOUVEAU: Fonctions utilitaires de tri (Étape 3)
// ----------------------------------------------------

void echanger_creatures(CreatureMarine *a, CreatureMarine *b) {
    CreatureMarine temp = *a;
    *a = *b;
    *b = temp;
}

void trier_creatures_par_vitesse(CreatureMarine creatures[], int nb) {
    for (int i = 0; i < nb - 1; i++) {
        int max_idx = i;
        for (int j = i + 1; j < nb; j++) {
            if (creatures[j].vitesse > creatures[max_idx].vitesse) {
                max_idx = j;
            }
        }
        if (max_idx != i) {
            echanger_creatures(&creatures[i], &creatures[max_idx]);
        }
    }
}

// ----------------------------------------------------
// INTERFACE DE COMBAT (Modifiée pour ne pas afficher la riposte immédiate)
// ----------------------------------------------------

void afficher_interface_combat(Plongeur *p, CreatureMarine *c, int degats_infliges) {
    char nom_creature[32];
    snprintf(nom_creature, sizeof(nom_creature), "%s", c->nom);

    printf("\n+---------------------------------------------------------+\n");
    // Suppression des caracteres speciaux (┬á)
    printf("|  PLONGEUR (HARPON)                                      |\n");
    printf("|                                                         |\n");
    printf("|     =======>                                            |\n");
    printf("|                                                         |\n");
    // Utilisation d'espaces ASCII standards et ajustement du formatage
    printf("|  Degats infliges : %-3d points a %-25s |\n", degats_infliges, nom_creature);
    printf("+---------------------------------------------------------+\n");
    // L'Oxygene et la Fatigue sont gérés dans attaquer_creature (joueur.c)
}

// ----------------------------------------------------
// Logique des Règles (Inchangée)
// ----------------------------------------------------

int calculer_attaques_max(int niveau_fatigue) {
    if (niveau_fatigue <= 1) {
        return 3;
    } else if (niveau_fatigue <= 3) {
        return 2;
    } else {
        return 1;
    }
}

void consommer_oxygene_auto(Plongeur *p) {
    int conso_auto = 5;
    p->niveau_oxygene -= conso_auto;

    printf("\nConsommation automatique d'oxygene : -%d.\n", conso_auto);

    if (p->niveau_oxygene <= 0) {
        p->niveau_oxygene = 0;
        p->points_de_vie -= 5;
        if (p->points_de_vie < 0) p->points_de_vie = 0;
        printf("!!! OXYGENE EPUISE ! Vous perdez 5 points de vie par asphyxie. !!!\n");
    }
}

// ----------------------------------------------------
// ATTAQUE CREATURE (Réintégrée avec Stress O2 et Effets Spéciaux - Étape 3/4)
// ----------------------------------------------------

void attaque_creature(Plongeur *p, CreatureMarine c) {
    if (!c.est_vivant) return;

    int attaque_min = c.attaque_minimale;
    int attaque_max = c.attaque_maximale;
    int degats = rand() % (attaque_max - attaque_min + 1) + attaque_min;

    // Règle Requin : Frénésie sanguinaire (+30% dégâts si PV < 50%)
    if (strcmp(c.nom, "Requin") == 0 && c.points_de_vie_actuels < c.points_de_vie_max * 0.5) {
        degats = (int)(degats * 1.30);
        printf("   >> Requin: Frenesie sanguinaire (+30%% degats)!\n");
    }

    // Règle Kraken : 2 attaques consecutives
    int nb_attaques = (strcmp(c.nom, "Kraken") == 0) ? 2 : 1;

    for (int i = 0; i < nb_attaques; i++) {

        // Règle Méduse : Piqûre paralysante (Réduit les attaques du joueur de 1 au prochain tour)
        if (strcmp(c.nom, "Meduse") == 0) {
            // Assurez-vous que le nom dans la structure CreatureMarine correspond à "Meduse"
            p->est_paralyse = 1;
            printf("   >> Meduse: Piqure paralysante! Attaques du plongeur reduites au prochain tour.\n");
        }

        // Règle Conséquence : Perte O2 supplementaire par stress (1 à 2 points)
        int perte_o2_stress = rand() % (2 - 1 + 1) + 1;
        p->niveau_oxygene -= perte_o2_stress;

        printf(" >> %s vous attaque et inflige %d degats (Coup %d/%d)!\n", c.nom, degats, i + 1, nb_attaques);
        printf("   > O2 perdu par stress (Stress) : -%d.\n", perte_o2_stress);

        // Application des degats au plongeur
        p->points_de_vie -= degats;
        if (p->points_de_vie < 0) p->points_de_vie = 0;

        // AFFICHAGE STATUT APRES ATTAQUE
        printf("--- STATUT PLONGEUR APRES ATTAQUE ---\n");
        printf("Vie     ["); afficher_barre(p->points_de_vie, p->points_de_vie_max);
        printf("] %d/%d\n", p->points_de_vie, p->points_de_vie_max);

        printf("Oxygene ["); afficher_barre(p->niveau_oxygene, p->niveau_oxygene_max);
        printf("] %d/%d\n", p->niveau_oxygene, p->niveau_oxygene_max);

        if (p->points_de_vie <= 0) {
            printf("!!! PLONGEUR VAINCU. !!!\n");
            break;
        }
        printf("---------------------------------------\n");
    }
}

// ----------------------------------------------------
// FONCTION COMBAT (Réintégrée avec Tri et Paralysie)
// ----------------------------------------------------

void combat(Plongeur *p, CreatureMarine creatures[], int nb) {
    int choix;
    int cible_id;
    int toutes_vaincues;

    while (p->points_de_vie > 0) {

        // ÉTAPE 1 : Affichage de l'état actuel
        afficher_interface(p);

        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("CREATURES EN COMBAT (Vitesse: Rapide -> Lent)\n");
        for (int i = 0; i < nb; i++) {
            if (creatures[i].est_vivant)
                printf("%d - %s (%d/%d PV, Vitesse: %d)\n", i + 1, creatures[i].nom,
                       creatures[i].points_de_vie_actuels, creatures[i].points_de_vie_max, creatures[i].vitesse);
        }
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

        int max_attaques_base = calculer_attaques_max(p->niveau_fatigue);
        int attaques_effectuees = 0;

        // GESTION DE LA PARALYSIE DE LA MEDUSE (Debut du tour)
        int max_attaques = max_attaques_base;
        if (p->est_paralyse) {
            max_attaques = (max_attaques > 0) ? max_attaques - 1 : 0;
            printf("!!! PARALYSIE (-1 Attaque): Seulement %d attaques disponibles ce tour. !!!\n", max_attaques);
        }

        // ÉTAPE 2 : Actions du joueur
        while (attaques_effectuees < max_attaques) {
            printf("Actions disponibles (Attaques restantes : %d/%d):\n", max_attaques - attaques_effectuees, max_attaques);
            printf("1 - Attaquer avec le harpon\n2 - Utiliser une competence marine\n3 - Utiliser un objet\n4 - Terminer le tour\n> ");
            if (scanf("%d", &choix) != 1) { /* Gestion d'erreur */ }

            if (choix == 1) {
                printf("Ciblez une creature (ID) : > ");
                if (scanf("%d", &cible_id) != 1) { /* Gestion d'erreur */ }
                cible_id--;

                if (cible_id >= 0 && cible_id < nb && creatures[cible_id].est_vivant) {
                    int pv_avant = creatures[cible_id].points_de_vie_actuels;

                    // L'attaque inflige les degats, la fatigue et l'O2 (voir joueur.c)
                    attaquer_creature(p, &creatures[cible_id]);
                    attaques_effectuees++;

                    int degats_infliges = pv_avant - creatures[cible_id].points_de_vie_actuels;

                    // Affichage de la nouvelle interface de combat après l'attaque
                    afficher_interface_combat(p, &creatures[cible_id], degats_infliges);

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

        // ÉTAPE 3 : Consommation oxygène automatique
        consommer_oxygene_auto(p);

        // Fin de l'effet de paralysie (pour le prochain tour)
        p->est_paralyse = 0;

        // ÉTAPE 5 : Attaques des créatures par ordre de VITESSE (RIPOSTE)
        printf("\n--- PHASE DE RIPOSTE DES CREATURES ---\n");
        trier_creatures_par_vitesse(creatures, nb); // Tri des créatures par Vitesse

        for (int i = 0; i < nb; i++)
            if (creatures[i].est_vivant)
                attaque_creature(p, creatures[i]); // Applique les dégâts et le stress O2

        // ÉTAPE 6 : Récupération fatigue
        if (p->niveau_fatigue > 0) {
            p->niveau_fatigue -= 1;
            printf("Recuperation de la fatigue : -1 niveau.\n");
        }

        // ÉTAPE 7 : Vérification fin
        toutes_vaincues = 1;
        for (int i = 0; i < nb; i++) {
            if (creatures[i].est_vivant) {
                toutes_vaincues = 0;
                break;
            }
        }

        if (toutes_vaincues) {
            printf("\nVICTOIRE ! Toutes les creatures ont ete vaincues.\n");
            break;
        }
        if (p->points_de_vie <= 0) break;
    }

    printf("\nLe combat est termine.\n");
}