#ifndef READ_BOARD_H
#define READ_BOARD_H

#include <libchessviz/chess_board.h>

#include <stdio.h>

#define MOVE_BLACK 1
#define MOVE_WHITE 0

#define CORRECT_MOVE 1
#define WRONG_MOVE 0

#define READ_END 1
#define READ_ERR 0

int read_moves(ChessBoard* b, FILE* src);

int is_piece_ltr(char s);

#endif
