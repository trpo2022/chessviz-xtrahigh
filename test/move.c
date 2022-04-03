#include <libchessviz/chess_board.h>
#include <libchessviz/create_board.h>
#include <libchessviz/free_board.h>
#include <libchessviz/move.c>

#include <ctest.h>

CTEST(movements, move_piece)
{
    ChessBoard* board = create_board();
    ASSERT_NOT_NULL(board);

    int fc = 0;
    int fr = 0;
    int tc = 0;
    int tr = 0;

    int result = move_piece(board, fc, fr, tc, tr);
    ASSERT_FALSE(result);

    tc = 'a';
    fr = '1';
    tr = '1';

    for (fc = 'a'; fc <= 'h'; fc++) {
        result = move_piece(board, fc, fr, tc, tr);
        ASSERT_TRUE(result);
    }

    for (fc = 'h'; fr <= '8'; fr++) {
        result = move_piece(board, fc, fr, tc, tr);
        ASSERT_TRUE(result);
    }

    for (fr = '8'; tc <= 'h'; tc++) {
        result = move_piece(board, fc, fr, tc, tr);
        ASSERT_TRUE(result);
    }

    for (tc = 'h'; tr <= '8'; tr++) {
        result = move_piece(board, fc, fr, tc, tr);
        ASSERT_TRUE(result);
    }

    result = move_piece(board, fc, fr, tc, tr);
    ASSERT_FALSE(result);

    fc = 'm';
    fr = '9';
    tc = 'w';
    tr = '0';

    result = move_piece(board, fc, fr, tc, tr);
    ASSERT_FALSE(result);

    free_board(board);
}
