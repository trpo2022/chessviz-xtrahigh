#ifndef _MOVE_H_
#define _MOVE_H_

#include <libchessviz/chess_board.h>
#include <libchessviz/print_board.h>

#include <stdio.h>

#define IS_PAWN 1
#define IS_NOT_PAWN 2
#define MOVE_ERR 0

void make_moves(ChessBoard* b);

#endif
