#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "card.h"
#include "cf_match.h"

struct _s_match {
    struct s_node *first;
    unsigned int size;
};

struct s_node
{
    card elem;
    struct s_node *next;
};

struct s_node *create_node(card e) {
    struct s_node *new_node = malloc(sizeof(struct s_node));
    assert(new_node != NULL);
    new_node->elem = e;
    new_node->next = NULL;
    return new_node;
}

struct s_node *destroy_node(struct s_node *node) {

    node->next = NULL;
    node->elem = card_destroy(node->elem);
    free(node);
    node = NULL;
    return node;
}
cf_match match_new(void)
{
   cf_match new_match = malloc(sizeof(struct _s_match));
   assert(new_match != NULL);
   new_match->first = NULL;
   new_match->size = 0; 
   return new_match;
}

cf_match match_add(cf_match match, card c)
{
    if (match->first == NULL)
    {
        match->first = create_node(c);
    } else {
        struct s_node *aux = match->first;
        while (aux->next != NULL)
        {
            aux = aux->next;
        }
        aux->next = create_node(c);
    }
    match->size ++;

    return match;
    
}

unsigned int match_size(cf_match match)
{
    return match->size;
}

bool is_match_correct(cf_match match)
{
    bool valid = true;
    valid = (match->size % 2 == 0);
    valid = valid && (card_player(match->first->elem) == 1);

    struct s_node *aux = match->first;
    while (aux->next != NULL && valid)
    {
        if (card_player(aux->elem) == card_player(aux->next->elem))
        {
            valid = false;
        }

        if (card_equal_color(aux->elem, aux->next->elem))
        {
            valid = false;
        }
        
        aux = aux->next;
    }

    return valid;
          
}

static int player_score(cf_match match, unsigned int player)
{
    int score = 0;
    bool isFlush = false;
    bool upwardsFlush = false;
    struct s_node *aux = match->first;
    if (player == 1)
    {
        while (aux->next != NULL)
        {
            isFlush = false;
            upwardsFlush = false;
            if (card_number(aux->elem) == card_number(aux->next->elem) + 1)
            {
                isFlush = true;
                upwardsFlush = true;
            }

            if (card_number(aux->elem) == card_number(aux->next->elem) - 1)
            {
                isFlush = true;
                upwardsFlush = false;
            }
            
            if (card_player(aux->next->elem) == 1)
            {
                score = score + card_drop_points(aux->elem, aux->next->elem, isFlush, upwardsFlush);
            }
            

            aux = aux->next;
        }
        
    } else{
        while(aux->next != NULL){
            struct s_node *prev = aux;
            aux = aux->next;
            if (card_number(prev->elem)+1 == card_number(aux->elem))
            {
                isFlush = true;
                upwardsFlush = true;
            } else if (card_number(prev->elem) == card_number(aux->elem) - 1)
            {
                isFlush = true;
            }
            if (card_player(aux->elem) == 2)
            {
                score += card_drop_points(prev->elem, aux->elem, isFlush, upwardsFlush);
            }
            isFlush = false;
            upwardsFlush = false;
        }
    }
    return score;
}

unsigned int match_winner(cf_match match)
{

    int player1_score = player_score(match, 1);

    int player2_score = player_score(match, 2);

    printf("PLAYER1_SCORE %d \n", player1_score);
    printf("PLAYER2_SCORE: %d \n", player2_score);

    if (!is_match_correct(match))
    {
        return -1;
    }else if (player1_score > player2_score)
    {
        return 1;
    }else if (player2_score > player1_score)
    {
        return 2;
    }else{
        return 0;
    }
}

unsigned int winner_total_points(cf_match match)
{
    if (!is_match_correct(match)) {
        return -1;
    }

    int playerOneScore = player_score(match, 1);
    int playerTwoScore = player_score(match, 2);

    if (playerOneScore == playerTwoScore) {
        return 0;
    }
    return playerOneScore > playerTwoScore ? playerOneScore : playerTwoScore;
}

card* match_to_array(cf_match match)
{
    card *array = malloc(sizeof(card) * match_size(match));
    assert(array != NULL);
    struct s_node *aux = match->first;
    for (unsigned i = 0; i < match->size; i++)
    {
        array[i] = aux->elem;
        aux = aux->next;
    }
     return array;
}

void match_dump(cf_match match)
{
    card* array = match_to_array(match);
    for (unsigned int i = 0u; i < match_size(match); i++) {
        card_dump(array[i]);
    }
    free(array);
}

cf_match match_destroy(cf_match match)
{
    struct s_node *aux = match->first;
    struct s_node *prev = match->first;
    while (aux != NULL)
    {
        prev = aux;
        aux = aux->next;
        prev->elem = card_destroy(prev->elem);
        destroy_node(prev);
    }
    
    free(match);
    match = NULL;
    return match;
}
