#include <libchessviz/chess_board.h>
#include <libchessviz/create_board.h>
#include <libchessviz/free_board.h>
#include <libchessviz/move.h>
#include <libchessviz/print_board.h>
#include <libchessviz/read_board.h>

int main(void)
{
    ChessBoard* b1 = create_board();

    print_board(b1, stdout);

    if (read_moves(b1, stdin))
        make_moves(b1);

    free_board(b1);

    return 0;
}
