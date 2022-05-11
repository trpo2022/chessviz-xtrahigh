#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#define TRUE 1
#define FALSE 0

#define BOARD_SIZE 8

#define TURNS_MAX 220
#define MOVES_IN_TURN 2
#define MOVE_SIZE 7

typedef struct {
    char board[BOARD_SIZE][BOARD_SIZE + 1];
    char moves[TURNS_MAX][MOVES_IN_TURN][MOVE_SIZE];
    int turn;
    int turns;
} ChessBoard;

#endif
