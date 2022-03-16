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

static int is_last_move(char* move)
{
    return (move[5] == '#' || move[6] == '#');
}

static int is_correct_move(char* move)
{
    unsigned int s = 0;
    if (!is_move_ltr(move[s]))
        return 0;
    s++;
    if (!isdigit(move[s]))
        return 0;
    if (move[s] < '1' || move[s] > '8')
        return 0;
    s++;
    if (!is_move_type(move[s]))
        return 0;
    s++;
    if (!is_move_ltr(move[s]))
        return 0;
    s++;
    if (!isdigit(move[s]))
        return 0;
    if (move[s] < '1' || move[s] > '8')
        return 0;
    s++;
    if (!is_move_eval(move[s]))
        return 0;

    return 1;
}

int read_moves(ChessBoard* b, FILE* src)
{
    int turn = -1;
    char white_move[MOVE_SIZE] = {'\0'};
    char black_move[MOVE_SIZE] = {'\0'};

    fprintf(stdout, "\nEnter a record of turns:\n");

    while (fscanf(src, "%d. %s %s", &turn, white_move, black_move) != EOF) {
        if (turn < 1 || turn != b->turns + 1)
            return 0;

        if (!is_correct_move(white_move))
            return 0;

        strncpy(b->moves[turn - 1][MOVE_WHITE], white_move, MOVE_SIZE);

        b->turns++;

        if (is_last_move(white_move))
            return 1;

        if (!is_correct_move(black_move))
            return 0;

        strncpy(b->moves[turn - 1][MOVE_BLACK], black_move, MOVE_SIZE);

        if (is_last_move(black_move))
            return 1;
    }

    return 1;
}
