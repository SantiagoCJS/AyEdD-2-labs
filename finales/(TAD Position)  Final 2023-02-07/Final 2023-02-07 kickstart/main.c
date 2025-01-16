#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include "position.h"

void print_board(struct _position *pos) {
    unsigned **board = position_board(pos);
    struct _position *pos_aux = position_initial(6);
    do {

        do {
            printf("%u ", board[position_row(pos_aux)] [position_column(pos_aux)]);
            position_right(pos_aux);
        } while (position_column(pos_aux) != 0);
        printf("\n");
        position_down(pos_aux);
    } while (position_row(pos_aux) != 0);
    printf("\n");



    do
    {
        free(board[position_column(pos_aux)]);
        position_right(pos_aux);
    } while (position_column(pos_aux) != 0);
   
    free(board);
    free(pos_aux);
}



int main()
{
    struct _position *pos = position_initial(6);
    struct _position *pos_absolute = position_absolute (2,3,6);
    pos_absolute = position_left(pos_absolute);
    pos_absolute = position_right(pos_absolute);
    pos = position_left(pos);
    pos = position_left(pos);
    pos = position_right(pos);
    pos = position_down(pos);
    pos = position_up(pos);
    unsigned int row = position_row(pos);
    printf("row: %u\n", row);
    unsigned column = position_column(pos);
    printf("column: %u\n", column);
    print_board(pos);
    list_t asd;
    asd = position_movements(pos_absolute);  
    list_show(asd);

    position_destroy(pos);
    position_destroy(pos_absolute);
    list_destroy(asd);
    
    return 0;
}