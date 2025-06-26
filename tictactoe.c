#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Define a 3x3 Tic Tac Toe board
char board[3][3];

// Function to initialize the board
void initializeBoard()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = ' ';
        }
    }
}

// Function to print the current board state
void printBoard()
{
    printf("\n");
    for (int i = 0; i < 3; i++)
    {
        printf(" %c | %c | %c ", board[i][0], board[i][1], board[i][2]);
        if (i < 2) printf("\n---|---|---\n");
    }
    printf("\n");
}

// Function to handle the player's move
void playerMove()
{
    int row, col;

    // Loop until a valid move is made
    while (1)
    {
        printf("Enter your move (row and column: 1 1 is top-left): ");
        scanf("%d %d", & row, &col);

        // Adjust for 0-based indexing
        row--;
        col--;

        // Check if the move is valid
        if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ')
        {
            board[row][col] = 'X'; // Player is always 'X'
            break;
        } else
        {
            printf("Invalid move. Try again.\n");
        }
    }
}

// Function for computer's random move
void computerMove()
{
    int row, col;

    // Find the first available empty spot
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j <3; j++)
        {
            if (board[i][j] == ' ')
            {
                board[i][j] = 'O'; // Computer is 'O'
                printf("Computer chose: %d %d\n", i + 1, j + 1);
                return;
            }
        }
    }
}
// Test functions in main for now
int main()
{
    initializeBoard();

    while (1)
    {
        printBoard();
        playerMove();

        printBoard();
        computerMove();
    }

    return 0;
}