#include <stdio.h>
#include <stdlib.h>
#include "combat.h" // Assurez-vous que cette en-tête contient les déclarations nécessaires
#include "joueur.h" // Nécessaire pour Plongeur et attaquer_creature (si elle est là)
#include "creatures.h" // Nécessaire pour CreatureMarine

// --- NOUVEAU : Règle 1 - Limite d'attaques par Fatigue ---
int calculer_attaques_max(int niveau_fatigue) {
    if (niveau_fatigue <= 1) {
        return 3; // Fatigue 0 ou 1
    } else if (niveau_fatigue <= 3) {
        return 2; // Fatigue 2 ou 3
    } else { // niveau_fatigue est 4 ou 5
        return 1; // Fatigue 4 ou 5
    }
}

// --- NOUVEAU : Règle 2 - Consommation Oxygène Automatique (Étape 3 du tour) ---
void consommer_oxygene_auto(Plongeur *p) {
    // Consommation automatique de base (exemple : -5 par tour)
    int conso_auto = 5;
    p->niveau_oxygene -= conso_auto;

    printf("\nConsommation automatique d'Oxygene: -%d.\n", conso_auto);

    // Règle: Si oxygène <= 0, -5 PV par tour
    if (p->niveau_oxygene <= 0) {
        p->niveau_oxygene = 0;
        p->points_de_vie -= 5;
        if (p->points_de_vie < 0) p->points_de_vie = 0;
        printf("OXYGENE EPUISE ! Vous perdez 5 points de vie par asphyxie. \n");
    }
}

// Fonction d'attaque des créatures vers le plongeur (comme dans votre code original)
void attaque_creature(Plongeur *p, CreatureMarine c) {
    if (!c.est_vivant) return;
    int degats = rand() % (c.attaque_maximale - c.attaque_minimale + 1) + c.attaque_minimale;
    printf(" %s vous attaque et inflige %d degats !\n", c.nom, degats);
    p->points_de_vie -= degats;
    if (p->points_de_vie < 0) p->points_de_vie = 0;
}

// --- FONCTION COMBAT RÉORGANISÉE ---
void combat(Plongeur *p, CreatureMarine creatures[], int nb) {
    int choix;
    int cible_id;

    while (p->points_de_vie > 0) { // La boucle du tour de combat (Étape 7 : Vérification)

        // --- ÉTAPE 1 du tour : Affichage de l'état ---
        afficher_interface(p);

        // Affichage des créatures et préparation de la fatigue
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        for (int i = 0; i < nb; i++) {
            if (creatures[i].est_vivant)
                printf("%d - %s (%d/%d PV)\n", i + 1, creatures[i].nom,
                       creatures[i].points_de_vie_actuels, creatures[i].points_de_vie_max);
        }
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

        // Règle 1: Calculer la limite d'attaque basée sur la fatigue
        int max_attaques = calculer_attaques_max(p->niveau_fatigue);
        int attaques_effectuees = 0;

        // --- ÉTAPE 2 du tour : Actions du joueur (Limité par la fatigue) ---
        while (attaques_effectuees < max_attaques) {

            printf("Actions disponibles (Attaques restantes: %d/%d):\n", max_attaques - attaques_effectuees, max_attaques);
            printf("1 - Attaquer avec harpon\n2 - Utiliser competence marine\n3 - Consommer objet\n4 - Terminer le tour\n> ");
            if (scanf("%d", &choix) != 1) { /* Gestion d'erreur */ }

            if (choix == 1) {
                printf("Ciblez une creature (ID) : > ");
                if (scanf("%d", &cible_id) != 1) { /* Gestion d'erreur */ }
                cible_id--; // ID joueur (1, 2...) -> index tableau (0, 1...)

                if (cible_id >= 0 && cible_id < nb && creatures[cible_id].est_vivant) {

                    // L'appel à attaquer_creature dans joueur.c gère O2 et Fatigue +1
                    attaquer_creature(p, &creatures[cible_id]); // Assurez-vous que le prototype de joueur.c est correct

                    attaques_effectuees++; // Compte l'action de combat

                } else {
                    printf("Cible invalide ou creature deja vaincue.\n");
                }
            } else if (choix == 4) {
                printf("Fin du tour pour le plongeur.\n");
                break; // Sort de la boucle des actions du joueur
            } else {
                printf("Action non implementée ou invalide.\n");
            }
        }

        if (attaques_effectuees >= max_attaques) {
            printf("\nLa limite d'attaques (Fatigue) est atteinte ce tour. Fin de l'action du plongeur.\n");
        }

        // --- ÉTAPE 3 du tour : Consommation Oxygène automatique (Règle 2 suite) ---
        consommer_oxygene_auto(p);

        // --- ÉTAPE 5 du tour : Attaques des créatures (sera trié par Vitesse à l'Étape 3) ---
        // Utilise votre fonction originale pour la riposte
        for (int i = 0; i < nb; i++)
            if (creatures[i].est_vivant)
                attaque_creature(p, creatures[i]);

        // --- ÉTAPE 6 du tour : Récupération Fatigue (Règle 1 suite) ---
        if (p->niveau_fatigue > 0) {
            p->niveau_fatigue -= 1;
            printf("Recuperation de la fatigue: -1 niveau.\n");
        }

        // Vérification de victoire (si toutes les créatures sont mortes) doit être ajoutée ici.
    }

    printf("\nLe combat est termine.\n");
}