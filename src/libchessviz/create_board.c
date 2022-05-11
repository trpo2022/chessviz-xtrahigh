#include <libchessviz/create_board.h>

#include <string.h>

ChessBoard* create_board(void)
{
    ChessBoard* b = (ChessBoard*)malloc(sizeof(ChessBoard));

    if (b != NULL) {
        b->turn = INITIAL_TURNS;
        b->turns = INITIAL_TURNS;
        strncpy(b->board[0], "RNBQKBNR", BOARD_SIZE + 1);
        strncpy(b->board[1], "PPPPPPPP", BOARD_SIZE + 1);
        strncpy(b->board[2], "        ", BOARD_SIZE + 1);
        strncpy(b->board[3], "        ", BOARD_SIZE + 1);
        strncpy(b->board[4], "        ", BOARD_SIZE + 1);
        strncpy(b->board[5], "        ", BOARD_SIZE + 1);
        strncpy(b->board[6], "pppppppp", BOARD_SIZE + 1);
        strncpy(b->board[7], "rnbqkbnr", BOARD_SIZE + 1);
    }

    return b;
}
