
## OceanDepth Projet C — 
## Exploration et survie sous-marine 
##  Présentation du projet OceanDepth est un jeu en langage C visant àune expérience d’exploration sous-marine. Le joueur incarne un plongeur qui doit gérer ses ressources (oxygène, points de vie, fatigue), affronter des créatures marines, collecter des trésors et améliorer son équipement. Ce projet permet de travailler la programmation modulaire en C, la gestion de structures de données, la manipulation de chaînes de caractères, ainsi que la conception d’un système de jeu tour par tour dans une interface entièrement textuelle.
## Principe du jeu

Le joueur commence avec des ressources limitées (PV, oxygène, fatigue) et évolue au fur et à mesure qu’il explore les fonds marins.

### Ressources principales :
- PV (Points de Vie)
- Oxygène (diminue à chaque action)
- Fatigue (limite le nombre d’actions)
- Perles (monnaie servant à acheter ou échanger)

## Fonctionnalités principales

### 1. Système de Combat
- Combat au tour par tour
- Attaques avec harpon ou compétences
- Consommation d’oxygène et augmentation de fatigue
- Créatures possédant des effets spéciaux (paralysie, frénésie, triple attaque…)

### 2. Gestion d'inventaire
- 8 emplacements maximum
- Possibilité d’équiper un harpon + une combinaison
- Objets disponibles :
    - Équipement : harpons, combinaisons
    - Consommables : capsule d’oxygène, trousse de soin
    - Ressources : perles
- Chaque objet possède ses propres statistiques (ATK, DEF, O2, effet…)

### 3. Interface Utilisateur
- Affichage des barres de vie / oxygène / fatigue
- Journal de combat détaillé
- Interface entièrement en terminal (sans bibliothèque graphique)

### 4. Récompenses et Loot
- Récompenses aléatoires à la fin d'un combat
- Rareté des objets : commun, rare, épique
- Exemple d’objets :
    - Capsule d’oxygène : +40 O2
    - Harpon électrique : ATK 35–50, +effet spécial

## Compilation et Exécution

### Avec Makefile :
