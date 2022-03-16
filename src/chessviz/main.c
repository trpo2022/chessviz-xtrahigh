#include <libchessviz/board.h>

int main(void)
{
    ChessBoard* b1 = create_board();

    print_board(b1, stdout);

    if (read_moves(b1, stdin))
        make_moves(b1);

    return 0;
}
