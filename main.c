#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "joueur.h"
#include "creatures.h"
#include "combat.h"

int main() {
    srand(time(NULL));

    Plongeur joueur;
    initialiser_plongeur(&joueur);

    CreatureMarine creatures[4];
    int nb = generer_creatures(creatures, joueur.profondeur);

    combat(&joueur, creatures, nb);
    return 0;
}
