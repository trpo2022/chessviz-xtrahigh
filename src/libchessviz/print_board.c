#include <libchessviz/print_board.h>

#include <stdarg.h>

void print_board(const ChessBoard* b, FILE* dist, ...)
{
    // j = MOVE_WHITE or j = MOVE_BLACK
    va_list params;
    va_start(params, dist);
    int j = va_arg(params, int);
    va_end(params);

    // If it's not the default board, print the turn number and move info
    if (b->turns != 0)
        fprintf(dist,
                "\nT%d/%d: %s\n",
                b->turn,
                b->turns,
                b->moves[b->turn - 1][j]);

    for (int i = BOARD_SIZE - 1; i >= 0; i--) {
        fprintf(dist, "%d ", i + 1);
        for (int j = 0; j < BOARD_SIZE; j++)
            fprintf(dist, "%c ", b->board[i][j]);
        fprintf(dist, "\n");
    }

    fprintf(dist, "  a b c d e f g h\n");
}
