#include <stdio.h>

#define BLOCK_SIZE 17

void displayBlock(char block[BLOCK_SIZE][BLOCK_SIZE]) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        for (int j = 0; j < BLOCK_SIZE; j++) {
            printf("%c ", block[i][j]);
        }
        printf("\n");
    }
}

int main() {
    // Define a 16x16 block with a red '*' in the left top corner and border
    char block[BLOCK_SIZE][BLOCK_SIZE] = {0}; // Initialize the block with zeros

    // Place a red '*' in the left top corner
    block[1][1] = '*';  // ANSI escape codes for red color

    // Add border around the block
    for (int i = 0; i < BLOCK_SIZE; i++) {
        block[i][0] = block[i][BLOCK_SIZE - 1] = '+';
        block[0][i] = block[BLOCK_SIZE - 1][i] = '+';
    }

    // Display the block on the screen
    displayBlock(block);

    return 0;
}

