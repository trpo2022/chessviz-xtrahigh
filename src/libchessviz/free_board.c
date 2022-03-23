#include <libchessviz/free_board.h>

#include <stdlib.h>

void free_board(ChessBoard* b)
{
    if (b)
        free(b);
}
