#include <stdio.h>
#include <stdlib.h>

// function that prints the output of each round
void output(char **grid) {
    printf("-------------\n");
    printf("| %c | %c | %c |\n", grid[0][0], grid[0][1], grid[0][2]);
    printf("-------------\n");
    printf("| %c | %c | %c |\n", grid[1][0], grid[1][1], grid[1][2]);
    printf("-------------\n");
    printf("| %c | %c | %c |\n", grid[2][0], grid[2][1], grid[2][2]);
    printf("-------------\n");
}


int playround(char **grid, int player) {
    int row, column;
    char symbol;
    if (player == 1) {
        symbol = 'O';
    } else {
        symbol = 'X';
    }
    
    printf("Player %d:\n", player);
    scanf("%d %d", &row, &column);
    
    if (row == -1 || column == -1) {
        return -1;
    }
    
    if (row > 2 || column > 2 || row < 0 || column < 0 || grid[row][column] != ' ') {
        printf("Incorrect value, try again.\n");
        return 0;
    }
    else {
        printf("Player %d entered %d %d.\n", player, row, column);
        grid[row][column] = symbol;
        return 1;
    }
}

int checkWin(char **grid, char symbol) {
    // rows
    for (int i = 0; i < 3; i++) {
        if (grid[i][0] == symbol && grid[i][1] == symbol && grid[i][2] == symbol)
            return 1;
    }
    
    // columns
    for (int i = 0; i < 3; i++) {
        if (grid[0][i] == symbol && grid[1][i] == symbol && grid[2][i] == symbol)
            return 1;
    }
    
    // diagonals
    if (grid[0][0] == symbol && grid[1][1] == symbol && grid[2][2] == symbol)
        return 1;
    
    if (grid[0][2] == symbol && grid[1][1] == symbol && grid[2][0] == symbol)
        return 1;
    
    return 0;
}

int isBoardFull(char **grid) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i][j] == ' ')
                return 0;
        }
    }
    return 1;
}

int main() {
    // allocate game memory w/ malloc
    char **grid = (char**)malloc(3 * sizeof(char*));
    for (int i = 0; i < 3; i++) {
        grid[i] = (char*)malloc(3 * sizeof(char));
        for (int j = 0; j < 3; j++) {
            grid[i][j] = ' ';
        }
    }

    int gamerunning = 1;
    int currentPlayer = 1;
    int validMove;
    int winner = 0;

    // output play, yes or no.
    char output_play;
    printf("Output Play (y/n):\n");
    scanf(" %c", &output_play);
    printf("You entered %c.\n", output_play);
    printf("Starting game with 3 x 3 board.\n");
    printf("Each player should enter\na row and col num (eg: 2 0).\n");

    // game loop
    while (gamerunning) {
        validMove = playround(grid, currentPlayer);
        
        if (validMove == -1) {
            //quit game
            gamerunning = 0;
        }
        else if (validMove == 1) {
            char symbol;
            if (currentPlayer == 1) {
                symbol = 'O';
            } else {
                symbol = 'X';
            }
            
            // show board is output play ==true
            if (output_play == 'y') {
                output(grid);
            }
            
            // check for win
            if (checkWin(grid, symbol)) {
                printf("Player %d is the winner.\n", currentPlayer);
                output(grid); 
                gamerunning = 0;
                winner = 1;
            }
            // check if board is full
            else if (isBoardFull(grid)) {
                output(grid); 
                gamerunning = 0;
            }
            // switch players
            else {
                if (currentPlayer == 1) {
                    currentPlayer = 2;
                } else {
                    currentPlayer = 1;
                }
            }
        }
    }

    //free memory
    for (int i = 0; i < 3; i++) {
        free(grid[i]);
    }
    free(grid);

    return 0;
}