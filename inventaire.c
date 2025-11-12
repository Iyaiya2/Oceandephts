#include <stdio.h>
#include <string.h>
#include "inventaire.h"

// Initialisation de l'inventaire
void initialiser_inventaire(Inventaire *inv) {
    inv->nb_objets = 0;
    inv->harpon_equipe = -1;
    inv->combi_equipe = -1;
    inv->perles = 0;
}

// Affiche une récompense simple
void afficher_recompense(Objet o) {
    printf("\n=================== TRÉSOR DÉCOUVERT ===================\n");
    printf("Nom: %s\n", o.nom);
    printf("ATK: %d-%d\n", o.attaque_min, o.attaque_max);
    printf("DEF: %d\n", o.defense);
    printf("Conso Oxygene: %d\n", o.conso_oxygene);
    printf("Spécial: %s\n", o.special);
    printf("Quantité: %d\n", o.quantite);
    printf("Appuyez sur Entrée pour continuer...\n");
    getchar();
}

// Ajoute un objet dans l'inventaire
void ajouter_objet_inventaire(Inventaire *inv, Objet o) {
    if (inv->nb_objets >= MAX_INVENTAIRE) {
        printf("Inventaire plein ! Vous ne pouvez pas prendre %s.\n", o.nom);
        return;
    }
    inv->objets[inv->nb_objets] = o;
    inv->nb_objets++;
    printf("%s ajouté à votre inventaire !\n", o.nom);
}

// Affiche l'inventaire simple
void afficher_inventaire(Inventaire *inv) {
    printf("\n======= INVENTAIRE =======\n");
    for (int i = 0; i < inv->nb_objets; i++) {
        printf("%d - %s (ATK %d-%d, DEF %d, O2 %d, Qté %d)\n",
               i+1,
               inv->objets[i].nom,
               inv->objets[i].attaque_min,
               inv->objets[i].attaque_max,
               inv->objets[i].defense,
               inv->objets[i].conso_oxygene,
               inv->objets[i].quantite);
    }
    printf("Perles: %d\n", inv->perles);
}

// Utiliser un objet (consommable)
void utiliser_objet(Inventaire *inv, int index) {
    if (index < 0 || index >= inv->nb_objets) {
        printf("Objet invalide.\n");
        return;
    }
    if (inv->objets[index].quantite > 0) {
        inv->objets[index].quantite--;
        printf("Vous utilisez %s !\n", inv->objets[index].nom);
    } else {
        printf("Vous n'avez plus de %s.\n", inv->objets[index].nom);
    }
}

// Equiper un harpon
void equiper_harpon(Inventaire *inv, int index) {
    if (index < 0 || index >= inv->nb_objets) {
        printf("Objet invalide.\n");
        return;
    }
    inv->harpon_equipe = index;
    printf("%s équipé comme harpon !\n", inv->objets[index].nom);
}

// Equiper une combinaison
void equiper_combi(Inventaire *inv, int index) {
    if (index < 0 || index >= inv->nb_objets) {
        printf("Objet invalide.\n");
        return;
    }
    inv->combi_equipe = index;
    printf("%s équipée comme combinaison !\n", inv->objets[index].nom);
}
