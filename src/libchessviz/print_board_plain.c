#include <libchessviz/print_board_plain.h>

#include <stdio.h>

void print_board(char array[][BOARD_SIZE + 1])
{
    for (int i = BOARD_SIZE - 1; i >= 0; i--) {
        // Row number
        printf("%d | ", i + 1);

        // Board rows
        for (int j = 0; j < BOARD_SIZE; j++) {
            printf("%c ", array[i][j]);
        }
        printf("\n");
    }

    // Border
    printf("    - - - - - - - -\n");

    // Column chars
    printf("    a b c d e f g h\n");
}
