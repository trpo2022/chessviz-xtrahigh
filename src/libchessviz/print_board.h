#ifndef PRINT_BOARD_H
#define PRINT_BOARD_H

#include <libchessviz/chess_board.h>

#include <stdio.h>

void print_board(const ChessBoard* b, FILE* dist, ...);

#endif
