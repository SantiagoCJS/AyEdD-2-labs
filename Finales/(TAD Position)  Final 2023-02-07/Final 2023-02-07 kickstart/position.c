#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "position.h"

struct _position {
        unsigned int row;
        unsigned int column;
        unsigned int dimension;
};



position_t position_initial(unsigned int dimension)
{
        struct _position *new_position = malloc(sizeof(struct _position));
        new_position->column = 0;
        new_position->row = 0;
        new_position->dimension = dimension;
        return new_position;
}

position_t position_absolute(unsigned int row, unsigned int column,
                             unsigned int dimension)
{
        struct _position *new_position = malloc(sizeof(struct _position));
        new_position->column = column;
        new_position->row = row;
        new_position->dimension = dimension;
        return new_position;
}

position_t position_left(position_t pos)
{
        pos->column = (pos->column + (pos->dimension - 1))% pos->dimension;
        return pos;
}

position_t position_right(position_t pos)
{
        pos->column = (pos->column + (pos->dimension + 1)) % pos->dimension;
        return pos;
}

position_t position_down(position_t pos)
{
        pos->row = (pos->row + (pos->dimension + 1)) % pos->dimension;
        return pos;
}

position_t position_up(position_t pos)
{
        pos->row = (pos->row + (pos->dimension - 1)) % pos->dimension;
        return pos;
}

unsigned int position_row(position_t pos)
{
        return pos->row;
}

unsigned int position_column(position_t pos)
{
        return pos->column;
}

unsigned int **position_board(position_t pos)
{
        unsigned int **board = calloc(pos->dimension, sizeof(unsigned int *));
        assert(board != NULL);
        for (unsigned int i = 0; i < pos->dimension; i++) {
                board[i] = calloc(pos->dimension, sizeof(unsigned int));
        }
        board[pos->row][pos->column] = 1;
        return board;
}

list_t position_movements(position_t pos)
{
        list_t movements = list_empty();

        for (unsigned i = 0; i < pos->column; i++)
        {
                movements = list_append(movements, RIGHT);
        }

        for (unsigned i = 0; i < pos->row; i++)
        {
                movements = list_append(movements, DOWN);
        }
        
        return movements;
}

position_t position_destroy(position_t pos)
{
        free(pos);
        pos = NULL;
        return pos;
}
