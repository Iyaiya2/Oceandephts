#ifndef INVENTAIRE_H
#define INVENTAIRE_H

#define MAX_INVENTAIRE 8

typedef struct {
    char nom[30];
    int attaque_min;
    int attaque_max;
    int defense;
    int conso_oxygene;
    char special[50];
    int quantite; // pour consommables
} Objet;

typedef struct {
    Objet objets[MAX_INVENTAIRE];
    int nb_objets;
    int harpon_equipe; // -1 si aucun
    int combi_equipe;  // -1 si aucune
    int perles;
} Inventaire;

// Fonctions
void initialiser_inventaire(Inventaire *inv);
void afficher_recompense(Objet o);
void ajouter_objet_inventaire(Inventaire *inv, Objet o);
void afficher_inventaire(Inventaire *inv);
void utiliser_objet(Inventaire *inv, int index);
void equiper_harpon(Inventaire *inv, int index);
void equiper_combi(Inventaire *inv, int index);

#endif
