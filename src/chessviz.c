#include <stdio.h>
#define SIZE 8

void print_board(int size, char array[][size + 1])
{
    for (int i = SIZE - 1; i >= 0; i--) {
        // Row number
        printf("%d | ", i + 1);

        // Board rows
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", array[i][j]);
        }
        printf("\n");
    }

    // Border
    printf("    - - - - - - - -\n");

    // Column chars
    printf("    a b c d e f g h\n");
}

int main(void)
{
    char board[SIZE][SIZE + 1]
            = {"RNBQKBNR", "PPPPPPPP", "", "", "", "", "pppppppp", "rnbqkbnrp"};

    print_board(SIZE, board);

    return 0;
}
