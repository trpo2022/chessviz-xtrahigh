#include <libchessviz/chess_board.h>
#include <libchessviz/create_board.h>
#include <libchessviz/free_board.h>
#include <libchessviz/move.c>

#include <ctest.h>

CTEST(move, move_piece)
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

CTEST(move, is_pawn_move_correct)
{
    ChessBoard* board = create_board();
    ASSERT_NOT_NULL(board);

    ASSERT_TRUE(is_pawn_move_correct(board, "a2-a4"));
    ASSERT_TRUE(is_pawn_move_correct(board, "b2-b4"));
    ASSERT_TRUE(is_pawn_move_correct(board, "c2-c4"));
    ASSERT_TRUE(is_pawn_move_correct(board, "d2-d4"));
    ASSERT_TRUE(is_pawn_move_correct(board, "e2-e4"));
    ASSERT_TRUE(is_pawn_move_correct(board, "f2-f4"));
    ASSERT_TRUE(is_pawn_move_correct(board, "g2-g4"));

    ASSERT_TRUE(is_pawn_move_correct(board, "a2-a3"));
    ASSERT_TRUE(is_pawn_move_correct(board, "b2-b3"));
    ASSERT_TRUE(is_pawn_move_correct(board, "c2-c3"));
    ASSERT_TRUE(is_pawn_move_correct(board, "d2-d3"));
    ASSERT_TRUE(is_pawn_move_correct(board, "e2-e3"));
    ASSERT_TRUE(is_pawn_move_correct(board, "f2-f3"));
    ASSERT_TRUE(is_pawn_move_correct(board, "g2-g3"));

    ASSERT_FALSE(is_pawn_move_correct(board, "a2-a5"));
    ASSERT_FALSE(is_pawn_move_correct(board, "b2-b5"));
    ASSERT_FALSE(is_pawn_move_correct(board, "c2-c5"));
    ASSERT_FALSE(is_pawn_move_correct(board, "d2-d5"));
    ASSERT_FALSE(is_pawn_move_correct(board, "e2-e5"));
    ASSERT_FALSE(is_pawn_move_correct(board, "f2-f5"));
    ASSERT_FALSE(is_pawn_move_correct(board, "g2-g5"));
    ASSERT_FALSE(is_pawn_move_correct(board, "g2-d2"));
    ASSERT_FALSE(is_pawn_move_correct(board, "g2-d5"));
    ASSERT_FALSE(is_pawn_move_correct(board, "g2-c1"));

    free_board(board);
}
