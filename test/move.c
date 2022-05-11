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

    ASSERT_FALSE(move_piece(board, fc, fr, tc, tr));

    tc = 'a';
    fr = '1';
    tr = '1';

    for (fc = 'a'; fc <= 'h'; fc++)
        ASSERT_TRUE(move_piece(board, fc, fr, tc, tr));

    for (fc = 'h'; fr <= '8'; fr++)
        ASSERT_TRUE(move_piece(board, fc, fr, tc, tr));

    for (fr = '8'; tc <= 'h'; tc++)
        ASSERT_TRUE(move_piece(board, fc, fr, tc, tr));

    for (tc = 'h'; tr <= '8'; tr++)
        ASSERT_TRUE(move_piece(board, fc, fr, tc, tr));

    ASSERT_FALSE(move_piece(board, fc, fr, tc, tr));

    fc = 'm';
    fr = '9';
    tc = 'w';
    tr = '0';

    ASSERT_FALSE(move_piece(board, fc, fr, tc, tr));

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

CTEST(move, is_king_move_correct)
{
    ASSERT_TRUE(is_king_move_correct("Kd4-d3"));
    ASSERT_TRUE(is_king_move_correct("Kd4-c3"));
    ASSERT_TRUE(is_king_move_correct("Kd4-e3"));
    ASSERT_TRUE(is_king_move_correct("Kd4-d5"));
    ASSERT_TRUE(is_king_move_correct("Kd4-c5"));
    ASSERT_TRUE(is_king_move_correct("Kd4-e5"));
    ASSERT_TRUE(is_king_move_correct("Kd4-c4"));
    ASSERT_TRUE(is_king_move_correct("Kd4-e4"));

    ASSERT_FALSE(is_king_move_correct("Kd4-d1"));
    ASSERT_FALSE(is_king_move_correct("Kd4-c1"));
    ASSERT_FALSE(is_king_move_correct("Kd4-e1"));
    ASSERT_FALSE(is_king_move_correct("Kd4-d7"));
    ASSERT_FALSE(is_king_move_correct("Kd4-c7"));
    ASSERT_FALSE(is_king_move_correct("Kd4-e7"));
    ASSERT_FALSE(is_king_move_correct("Kd4-a4"));
    ASSERT_FALSE(is_king_move_correct("Kd4-h4"));
}

CTEST(move, is_queen_move_correct)
{
    ASSERT_TRUE(is_queen_move_correct("Kd4-d3"));
    ASSERT_TRUE(is_queen_move_correct("Kd4-c3"));
    ASSERT_TRUE(is_queen_move_correct("Kd4-e3"));
    ASSERT_TRUE(is_queen_move_correct("Kd4-d5"));
    ASSERT_TRUE(is_queen_move_correct("Kd4-c5"));
    ASSERT_TRUE(is_queen_move_correct("Kd4-e5"));
    ASSERT_TRUE(is_queen_move_correct("Kd4-c4"));
    ASSERT_TRUE(is_queen_move_correct("Kd4-e4"));

    ASSERT_TRUE(is_queen_move_correct("Kd4-d1"));
    ASSERT_TRUE(is_queen_move_correct("Kd4-c1"));
    ASSERT_TRUE(is_queen_move_correct("Kd4-e1"));
    ASSERT_TRUE(is_queen_move_correct("Kd4-d7"));
    ASSERT_TRUE(is_queen_move_correct("Kd4-c7"));
    ASSERT_TRUE(is_queen_move_correct("Kd4-e7"));
    ASSERT_TRUE(is_queen_move_correct("Kd4-a4"));
    ASSERT_TRUE(is_queen_move_correct("Kd4-h4"));
}

CTEST(move, is_rook_move_correct)
{
    ASSERT_TRUE(is_rook_move_correct("Kd1-d2"));
    ASSERT_TRUE(is_rook_move_correct("Kd2-d3"));
    ASSERT_TRUE(is_rook_move_correct("Kd3-d4"));
    ASSERT_TRUE(is_rook_move_correct("Kd4-d5"));
    ASSERT_TRUE(is_rook_move_correct("Kd5-d4"));
    ASSERT_TRUE(is_rook_move_correct("Kd5-d6"));
    ASSERT_TRUE(is_rook_move_correct("Kd6-d7"));
    ASSERT_TRUE(is_rook_move_correct("Kd7-d8"));

    ASSERT_TRUE(is_rook_move_correct("Ka2-b2"));
    ASSERT_TRUE(is_rook_move_correct("Kb2-c2"));
    ASSERT_TRUE(is_rook_move_correct("Kc2-d2"));
    ASSERT_TRUE(is_rook_move_correct("Kd2-e2"));
    ASSERT_TRUE(is_rook_move_correct("Ke2-f2"));
    ASSERT_TRUE(is_rook_move_correct("Kf2-g2"));
    ASSERT_TRUE(is_rook_move_correct("Kg2-h2"));
    ASSERT_TRUE(is_rook_move_correct("Kh2-a2"));

    ASSERT_FALSE(is_rook_move_correct("Kd4-c1"));
    ASSERT_FALSE(is_rook_move_correct("Kd4-e1"));
    ASSERT_FALSE(is_rook_move_correct("Kd4-c5"));
    ASSERT_FALSE(is_rook_move_correct("Kd4-e5"));
    ASSERT_FALSE(is_rook_move_correct("Kd4-c7"));
    ASSERT_FALSE(is_rook_move_correct("Kd4-e7"));
    ASSERT_FALSE(is_rook_move_correct("Kd4-c3"));
    ASSERT_FALSE(is_rook_move_correct("Kd4-e3"));
}

CTEST(move, is_bishop_move_correct)
{
    ASSERT_FALSE(is_bishop_move_correct("Kd1-d2"));
    ASSERT_FALSE(is_bishop_move_correct("Kd2-d3"));
    ASSERT_FALSE(is_bishop_move_correct("Kd3-d4"));
    ASSERT_FALSE(is_bishop_move_correct("Kd4-d5"));
    ASSERT_FALSE(is_bishop_move_correct("Kd5-d4"));
    ASSERT_FALSE(is_bishop_move_correct("Kd5-d6"));
    ASSERT_FALSE(is_bishop_move_correct("Kd6-d7"));
    ASSERT_FALSE(is_bishop_move_correct("Kd7-d8"));
    ASSERT_FALSE(is_bishop_move_correct("Ka2-b2"));
    ASSERT_FALSE(is_bishop_move_correct("Kb2-c2"));
    ASSERT_FALSE(is_bishop_move_correct("Kc2-d2"));
    ASSERT_FALSE(is_bishop_move_correct("Kd2-e2"));
    ASSERT_FALSE(is_bishop_move_correct("Ke2-f2"));
    ASSERT_FALSE(is_bishop_move_correct("Kf2-g2"));
    ASSERT_FALSE(is_bishop_move_correct("Kg2-h2"));
    ASSERT_FALSE(is_bishop_move_correct("Kh2-a2"));
    ASSERT_FALSE(is_bishop_move_correct("Kd4-c1"));
    ASSERT_FALSE(is_bishop_move_correct("Kd4-e1"));
    ASSERT_FALSE(is_bishop_move_correct("Kd4-c7"));
    ASSERT_FALSE(is_bishop_move_correct("Kd4-e7"));

    ASSERT_TRUE(is_bishop_move_correct("Kc1-d2"));
    ASSERT_TRUE(is_bishop_move_correct("Kd2-e3"));
    ASSERT_TRUE(is_bishop_move_correct("Ke3-f4"));
    ASSERT_TRUE(is_bishop_move_correct("Kf4-g5"));
    ASSERT_TRUE(is_bishop_move_correct("Kg5-h6"));
}

CTEST(move, is_knight_move_correct)
{
    ASSERT_TRUE(is_knight_move_correct("Nd3-c1"));
    ASSERT_TRUE(is_knight_move_correct("Nd3-b2"));
    ASSERT_TRUE(is_knight_move_correct("Nd3-b4"));
    ASSERT_TRUE(is_knight_move_correct("Nd3-c5"));
    ASSERT_TRUE(is_knight_move_correct("Nd3-e5"));
    ASSERT_TRUE(is_knight_move_correct("Nd3-f4"));
    ASSERT_TRUE(is_knight_move_correct("Nd3-f2"));
    ASSERT_TRUE(is_knight_move_correct("Nd3-e1"));
}
