#include <libchessviz/print_board_plain.h>

int main(void)
{
    char board[BOARD_SIZE][BOARD_SIZE + 1]
            = {"RNBQKBNR", "PPPPPPPP", "", "", "", "", "pppppppp", "rnbqkbnrp"};

    print_board(board);

    return 0;
}
