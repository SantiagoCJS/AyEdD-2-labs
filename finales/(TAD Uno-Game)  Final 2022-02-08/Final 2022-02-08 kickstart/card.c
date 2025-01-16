#include <stdlib.h>
#include <stdbool.h>

#include <assert.h>
#include "card.h"

struct s_card {
    unsigned int num;
    color_t color;
    type_t type;
};

static bool
invrep(card_t c) {
    // Invariante de representación
    bool valid=false;
    valid = c != NULL;
    valid = 1 <= c->num && c->num < 10;
    valid = (c->color == blue) || (c->color == red) || (c->color == yellow) || (c->color == green);
    valid = (c->type == normal) || (c->type == change_color) || (c->type == skip);
    return valid;
}

card_t
card_new(unsigned int num, color_t color, type_t s) {
    card_t card = malloc(sizeof(struct s_card));
    assert(card != NULL);
    card->num = num;
    card->color = color;
    card->type = s;

    assert(invrep(card));
    return card;
}


type_t
card_get_number(card_t card) {
    assert(invrep(card));
    return card->num;
}

color_t
card_get_color(card_t card) {
    assert(invrep(card));
    return card->color;
}

type_t
card_get_type(card_t card) {
    assert(invrep(card));
    return card->type;
}

bool
card_samecolor(card_t c1, card_t c2) {
    assert(invrep(c1) && invrep(c2));
    return (c1->color == c2->color);
}


bool
card_samenum(card_t c1, card_t c2) {
    assert(invrep(c1) && invrep(c2));
    return (c1->num == c2->num);
}

bool
card_compatible(card_t new_card, card_t pile_card) {
    bool compatible=false;
    assert(invrep(new_card) && invrep(pile_card));

    if (card_get_type(pile_card) == change_color) {
        if (card_get_type(new_card) == change_color) {
            compatible = true;
        } else {
            compatible = card_samecolor(new_card,pile_card);
        }
        
    } else if (card_get_type(pile_card) == normal) {
        if (card_get_type(new_card) == normal) {
            compatible = card_samecolor(pile_card,new_card) || card_samenum(pile_card, new_card);
        } else if (card_get_type(new_card) == skip) {
            compatible = card_samecolor(pile_card,new_card);
        } else {
            compatible = true;
        }
        
    } else {
        if (card_get_type(new_card) == skip) {
            compatible = true;
        } else if (card_get_type(new_card) == change_color) {
            compatible = true;
        } else {
            compatible = card_samecolor(new_card,pile_card);
        }
    }
    

    return compatible;
}

card_t
card_destroy(card_t card) {
    assert(invrep(card));
    free(card);
    card = NULL;
    return card;
}


