#include <libchessviz/chess_board.h>
#include <libchessviz/create_board.h>
#include <libchessviz/free_board.h>

#include <ctest.h>

#include <string.h>

CTEST(board, create_board)
{
    ChessBoard* board = create_board();

    ASSERT_NOT_NULL(board);

    ASSERT_EQUAL(0, board->turn);
    ASSERT_EQUAL(0, board->turns);

    ASSERT_EQUAL(0, strcmp("RNBQKBNR", board->board[0]));
    ASSERT_EQUAL(0, strcmp("PPPPPPPP", board->board[1]));
    ASSERT_EQUAL(0, strcmp("pppppppp", board->board[6]));
    ASSERT_EQUAL(0, strcmp("rnbqkbnr", board->board[7]));
    for (int i = 2; i < 6; i++)
        ASSERT_EQUAL(0, strcmp("        ", board->board[i]));

    free_board(board);
}
