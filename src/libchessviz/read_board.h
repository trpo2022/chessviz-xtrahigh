#ifndef READ_BOARD_H
#define READ_BOARD_H

#include <libchessviz/chess_board.h>

#include <stdio.h>

#define MOVE_WHITE 0
#define MOVE_BLACK 1

int read_moves(ChessBoard* b, FILE* src);

#endif
