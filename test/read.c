#include <libchessviz/chess_board.h>
#include <libchessviz/create_board.h>
#include <libchessviz/free_board.h>
#include <libchessviz/read_board.c>

#include <ctest.h>

CTEST(read, is_move_ltr)
{
    for (char c = 32; c <= 126; c++) {
        if (c >= 'a' && c <= 'h')
            ASSERT_TRUE(is_move_ltr(c));
        else
            ASSERT_FALSE(is_move_ltr(c));
    }
}

CTEST(read, is_move_type)
{
    for (char c = 32; c <= 126; c++) {
        if (c == '-' || c == 'x')
            ASSERT_TRUE(is_move_type(c));
        else
            ASSERT_FALSE(is_move_type(c));
    }
}

CTEST(read, is_move_eval)
{
    for (char c = 32; c <= 126; c++) {
        if (c == '#' || c == '+')
            ASSERT_TRUE(is_move_eval(c));
        else
            ASSERT_FALSE(is_move_eval(c));
    }
}

CTEST(read, is_empty_move)
{
    for (char c = 32; c <= 126; c++)
        ASSERT_FALSE(is_empty_move(c));

    ASSERT_TRUE(is_empty_move('\0'));
}

CTEST(read, is_last_move)
{
    ASSERT_FALSE(is_last_move("Ke2-e4"));
    ASSERT_FALSE(is_last_move("Qe2-e4"));
    ASSERT_FALSE(is_last_move("e2-e4"));
    ASSERT_FALSE(is_last_move("Be2-e4"));
    ASSERT_FALSE(is_last_move("e2-e4"));

    ASSERT_TRUE(is_last_move("Ke2-e4#"));
    ASSERT_TRUE(is_last_move("e2-e4#"));
    ASSERT_TRUE(is_last_move("Ne2-e4#"));
    ASSERT_TRUE(is_last_move("e2-e4#"));
    ASSERT_TRUE(is_last_move("Re2-e4#"));
}

CTEST(read, is_piece_ltr)
{
    for (char c = 32; c <= 126; c++) {
        if (c == 'K' || c == 'Q' || c == 'R' || c == 'B' || c == 'N')
            ASSERT_TRUE(is_piece_ltr(c));
        else
            ASSERT_FALSE(is_piece_ltr(c));
    }
}
