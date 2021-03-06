#include <libchessviz/chess_board.h>
#include <libchessviz/read_board.h>

#include <ctype.h>
#include <string.h>

static int is_move_ltr(char s)
{
    return (s >= 'a' && s <= 'h');
}

static int is_move_type(char s)
{
    return (s == '-' || s == 'x');
}

static int is_move_eval(char s)
{
    return (s == '#' || s == '+' || s == '\0');
}

static int is_empty_move(char s)
{
    return (s == '\0');
}

static int is_last_move(char* move)
{
    return (move[MOVE_SIZE - 2] == '#' || move[MOVE_SIZE - 1] == '#');
}

int is_piece_ltr(char s)
{
    return (s == 'K' || s == 'Q' || s == 'R' || s == 'B' || s == 'N');
}

static int is_correct_move(char* move)
{
    unsigned int s = 0;
    if (is_piece_ltr(move[0]))
        s++;
    if (!is_move_ltr(move[s]) || is_empty_move(move[s]))
        return WRONG_MOVE;
    s++;
    if (!isdigit(move[s]))
        return WRONG_MOVE;
    if (move[s] < '1' || move[s] > '8')
        return WRONG_MOVE;
    s++;
    if (!is_move_type(move[s]))
        return WRONG_MOVE;
    s++;
    if (!is_move_ltr(move[s]))
        return WRONG_MOVE;
    s++;
    if (!isdigit(move[s]))
        return WRONG_MOVE;
    if (move[s] < '1' || move[s] > '8')
        return WRONG_MOVE;
    s++;
    if (!is_move_eval(move[s]))
        return WRONG_MOVE;

    return CORRECT_MOVE;
}

int read_moves(ChessBoard* b, FILE* src)
{
    int turn = -1, is_end = TRUE;
    char white_move[MOVE_SIZE] = {'\0'};
    char black_move[MOVE_SIZE] = {'\0'};

    fprintf(stdout, "\nEnter the full record of turns (CTRL+C to quit)\n");
    fprintf(stdout,
            "Example:\n1. e2-e4 e7-e5\n2. Bf1-c4 Nb8-c6\n3. Qd1-h5 Ng8-f6\n4. "
            "Qh5xf7#\n\n");

    while (is_end != EOF) {
        is_end = fscanf(src, "%d. %s", &turn, white_move);

        if (turn < 1 || turn != b->turns + 1) {
            fprintf(stderr,
                    "Turn %d: incorrect number, expected %d\n",
                    turn,
                    b->turns + 1);
            return READ_ERR;
        }

        if (!is_correct_move(white_move)) {
            fprintf(stderr,
                    "Turn %d: incorrect white move %s\n",
                    turn,
                    white_move);
            return READ_ERR;
        }

        strncpy(b->moves[turn - 1][MOVE_WHITE], white_move, MOVE_SIZE);

        b->turns++;

        if (is_last_move(white_move))
            return READ_END;

        is_end = fscanf(src, "%s", black_move);

        if (!is_correct_move(black_move)) {
            fprintf(stderr,
                    "Turn %d: incorrect black move %s\n",
                    turn,
                    black_move);
            return READ_ERR;
        }

        strncpy(b->moves[turn - 1][MOVE_BLACK], black_move, MOVE_SIZE);

        if (is_last_move(black_move))
            return READ_END;
    }

    return READ_END;
}
