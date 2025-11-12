#include <stdio.h>
#include <string.h>
#include "inventaire.h"

void initialiser_inventaire(Inventaire *p) {
    // Vider l'inventaire
    for (int i = 0; i < MAX_OBJETS; i++) {
        p->inventaire[i] = (Objet){"", 0, 0, 0, 0, 0, 0};
    }

    // Équipements et perles
    strcpy(p->harpon_equipe.nom, "Aucun");
    strcpy(p->combi_equipe.nom, "Aucun");
    p->perles = 127;

    // Exemples d'objets stylés
    strcpy(p->inventaire[0].nom, "Harpon Rouillé");
    p->inventaire[0].attaque = 12;

    strcpy(p->inventaire[1].nom, "Combi Néoprène");
    p->inventaire[1].defense = 5;

    strcpy(p->inventaire[2].nom, "Capsule O2");
    p->inventaire[2].oxygene = 20;
    p->inventaire[2].quantite = 3;

    strcpy(p->inventaire[3].nom, "Trousse de soin");
    p->inventaire[3].pv = 25;
    p->inventaire[3].quantite = 2;

    strcpy(p->inventaire[4].nom, "Stimulant");
    p->inventaire[4].fatigue = 2;
    p->inventaire[4].quantite = 2;
}

void afficher_et_gestion_inventaire(Inventaire *p) {
    printf("\nMaximum %d objets dans l'inventaire\n", MAX_OBJETS);
    printf("INVENTAIRE SOUS-MARIN\n");
    printf("+-----------------+-----------------+------------+\n");
    printf("| EQUIPE HARPON   | EQUIPE COMBI    | PERLES     |\n");
    printf("| %-15s | %-15s | %10d |\n",
           p->harpon_equipe.nom[0] ? p->harpon_equipe.nom : "Aucun",
           p->combi_equipe.nom[0] ? p->combi_equipe.nom : "Aucun",
           p->perles);
    printf("+-----------------+-----------------+------------+\n");

    // Affichage des objets
    for (int i = 0; i < MAX_OBJETS; i++) {
        Objet obj = p->inventaire[i];
        if (obj.nom[0] != '\0') {
            printf("%2d - %-15s | ATK:%3d DEF:%3d | O2:%3d PV:%3d | Fatigue:%2d Qt:%2d\n",
                   i + 1,
                   obj.nom,
                   obj.attaque,
                   obj.defense,
                   obj.oxygene,
                   obj.pv,
                   obj.fatigue,
                   obj.quantite);
        } else {
            printf("%2d - Vide\n", i + 1);
        }
    }

    printf("+-----------------------------------------------------------+\n");
    printf("1 - Utiliser objet  2 - Equiper harpon  3 - Equiper combi  4 - Retour\n");
}
