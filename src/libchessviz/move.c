#include <libchessviz/chess_board.h>
#include <libchessviz/move.h>
#include <libchessviz/read_board.h>

#include <ctype.h>

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

    int moved = FALSE;
    if (is_positive_pos && is_within_board) {
        b->board[to_row][to_col] = b->board[from_row][from_col];
        b->board[from_row][from_col] = ' ';
        moved = TRUE;
    }

    return moved;
}

static int is_pawn_move_correct(ChessBoard* b, char* move)
{
    int correct = TRUE;

    int step_size = move[1] - move[4]; // e2-e4 -> -2
    if (step_size < 0)
        step_size *= -1;

    if (step_size > 2 || step_size == 0)
        return FALSE;

    if (step_size == 2 && b->turn > 1)
        return FALSE;

    if (move[0] != move[3])
        return FALSE;

    char target_cell = b->board[move[4] - '0' - 1][move[3] - 'a'];

    if (move[2] == 'x' && target_cell == ' ')
        correct = FALSE;
    else if (move[2] == '-' && target_cell != ' ')
        correct = FALSE;

    return correct;
}

static int is_king_move_correct(char* move)
{
    int rows_step_size = move[2] - move[5]; // Kd5-c4 -> -1
    if (rows_step_size < 0)
        rows_step_size *= -1;

    int cols_step_size = move[1] - move[4]; // Kd5-c4 -> -1
    if (cols_step_size < 0)
        cols_step_size *= -1;

    if (cols_step_size + rows_step_size == 0)
        return FALSE;

    return ((rows_step_size + cols_step_size) == 1
            || (rows_step_size + cols_step_size) == 2);
}

static int is_queen_move_correct(char* move)
{
    int rows_step_size = move[2] - move[5]; // Qd3-f5 -> -2
    if (rows_step_size < 0)
        rows_step_size *= -1;

    int cols_step_size = move[1] - move[4]; // Qd3-f5 -> -2
    if (cols_step_size < 0)
        cols_step_size *= -1;

    return (cols_step_size + rows_step_size > 0);
}

static int is_rook_move_correct(char* move)
{
    int rows_step_size = move[2] - move[5]; // Rh6-h1 -> 5
    if (rows_step_size < 0)
        rows_step_size *= -1;

    int cols_step_size = move[1] - move[4]; // Rh6-h1 -> 0
    if (cols_step_size < 0)
        cols_step_size *= -1;

    if (cols_step_size + rows_step_size == 0)
        return FALSE;

    return ((cols_step_size == 0 && rows_step_size > 0)
            || (cols_step_size > 0 && rows_step_size == 0));
}

static int is_bishop_move_correct(char* move)
{
    int rows_step_size = move[2] - move[5]; // Bf3-d5 -> -2
    if (rows_step_size < 0)
        rows_step_size *= -1;

    int cols_step_size = move[1] - move[4]; // Bf3-d5 -> -2
    if (cols_step_size < 0)
        cols_step_size *= -1;

    if (cols_step_size + rows_step_size == 0)
        return FALSE;

    return (rows_step_size == cols_step_size);
}

static int is_knight_move_correct(char* move)
{
    int rows_step_size = move[2] - move[5]; // Ne4-c3 -> -1
    if (rows_step_size < 0)
        rows_step_size *= -1;

    int cols_step_size = move[1] - move[4]; // Ne4-c3 -> -2
    if (cols_step_size < 0)
        cols_step_size *= -1;

    return (cols_step_size + rows_step_size > 0);
}

static int is_piece_move_correct(ChessBoard* b, char* move)
{
    int correct = TRUE;

    switch (tolower(move[0])) {
    case 'k':
        if (!is_king_move_correct(move))
            return FALSE;
        break;
    case 'q':
        if (!is_queen_move_correct(move))
            return FALSE;
        break;
    case 'r':
        if (!is_rook_move_correct(move))
            return FALSE;
        break;
    case 'b':
        if (!is_bishop_move_correct(move))
            return FALSE;
        break;
    case 'n':
        if (!is_knight_move_correct(move))
            return FALSE;
        break;
    default:
        correct = FALSE;
    }

    char source_cell = b->board[move[2] - '0' - 1][move[1] - 'a'];

    if (tolower(source_cell) != tolower(move[0]))
        return FALSE;

    char target_cell = b->board[move[5] - '0' - 1][move[4] - 'a'];

    if (move[3] == 'x' && target_cell == ' ')
        correct = FALSE;
    else if (move[3] == '-' && target_cell != ' ')
        correct = FALSE;

    return correct;
}

static int check_move(ChessBoard* b, char* move)
{
    int status = IS_PAWN;

    if (is_piece_ltr(move[0]))
        status = IS_NOT_PAWN;

    if (status == IS_PAWN)
        status = is_pawn_move_correct(b, move) ? IS_PAWN : MOVE_ERR;
    else if (status == IS_NOT_PAWN)
        status = is_piece_move_correct(b, move) ? IS_NOT_PAWN : MOVE_ERR;

    return status;
}

void make_moves(ChessBoard* b)
{
    int s = 0;
    int status = MOVE_ERR;
    for (int i = 0; i < b->turns; i++) {
        b->turn++;
        for (int j = 0, m = 0; j < MOVES_IN_TURN; j++) {
            s = 0;
            status = check_move(b, b->moves[i][j]);
            if (status == IS_NOT_PAWN)
                s++;
            else if (status == MOVE_ERR) {
                if (b->turn != b->turns)
                    fprintf(stdout,
                            "Turn %d: incorrect move %s\n",
                            b->turn,
                            b->moves[i][j]);
                return;
            }

            m = move_piece(
                    b,
                    b->moves[i][j][s],
                    b->moves[i][j][s + 1],
                    b->moves[i][j][s + 3],
                    b->moves[i][j][s + 4]);
            if (m)
                print_board(b, stdout, j);
        }
    }
}
