#include <libchessviz/move.h>

#define is_positive_pos \
    (from_col >= 0 && to_col >= 0 && from_row >= 0 && to_row >= 0)
#define is_within_board                                                    \
    (from_col < BOARD_SIZE && to_col < BOARD_SIZE && from_row < BOARD_SIZE \
     && to_row < BOARD_SIZE)

static int
move_piece(ChessBoard* b, int from_col, int from_row, int to_col, int to_row)
{
    from_col -= 'a';
    to_col -= 'a';
    from_row -= '0' + 1;
    to_row -= '0' + 1;

    int moved = 0;
    if (is_positive_pos && is_within_board) {
        b->board[to_row][to_col] = b->board[from_row][from_col];
        b->board[from_row][from_col] = ' ';
        moved = 1;
    }

    return moved;
}

void make_moves(ChessBoard* b)
{
    for (int i = 0; i < b->turns; i++) {
        b->turn++;
        for (int j = 0; j < MOVES_IN_TURN; j++) {
            move_piece(
                    b,
                    b->moves[i][j][0],
                    b->moves[i][j][1],
                    b->moves[i][j][3],
                    b->moves[i][j][4]);
            print_board(b, stdout, j);
        }
    }
}
