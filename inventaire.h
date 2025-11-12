#ifndef INVENTAIRE_H
#define INVENTAIRE_H

#define MAX_OBJETS 8

typedef struct {
    char nom[32];
    int attaque;    // bonus ATK si objet offensif
    int defense;    // bonus DEF si objet défensif
    int oxygene;    // oxygene restauré si consommable
    int pv;         // points de vie restaurés si consommable
    int fatigue;    // fatigue réduite si consommable
    int quantite;   // nombre disponible
} Objet;

typedef struct {
    Objet inventaire[MAX_OBJETS];
    Objet harpon_equipe;
    Objet combi_equipe;
    int perles;
} Inventaire;

void initialiser_inventaire(Inventaire *p);
void afficher_et_gestion_inventaire(Inventaire *p);

#endif
