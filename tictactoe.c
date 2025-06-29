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
    findBestMove(&row, &col);
    board[row][col] = 'O';
    printf("Computer chose: %d %d\n", row + 1, col + 1);

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

// Function to check for a win or a draw
char checkWinner()
{
    // Check rows
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] != ' ' &&
            board[i][0] == board[i][1] &&
            board[i][1] == board[i][2])
            {
                return board[i][0];
            }
    }

    // Check columns
    for (int i = 0; i < 3; i++)
    {
        if (board[0][i] != ' ' &&
            board[0][i] == board[1][i] &&
            board[1][i] == board[2][i])
            {
                return board[0][i];
            }
    }

    // Check diagonals
    if (board[0][0] != ' ' &&
        board[0][0] == board[1][1] &&
        board[1][1] == board[2][2])
        {
            return board[0][0];
        }
    
    if (board[0][2] != ' ' &&
        board[0][2] == board[1][1] &&
        board[1][1] == board[2][0])
        {
            return board[0][2];
        }

    // Check for draw
    int emptyFound = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == ' ')
            {
                emptyFound = 1;
            }
        }
    }
    if (!emptyFound)
    {
        return 'D'; // Draw
    }

    return ' '; // Game still ongoing
}

// Evaluate the board; +10 = Computer win, -10 = Player win, 0 = no win
int evaluate()
{
    // Rows
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] == board[i][1] &&
            board[i][1] == board[i][2])
        {
            if (board[i][0] == 'O') return +10;
            if (board[i][0] == 'X') return -10;
        }
    }

    // Diagonals
    if (board[0][0] == board[1][1] &&
        board[1][1] == board[2][2])
    {
        if (board[0][0] == 'O') return +10;
        if (board[0][0] == 'X') return -10;
    }

    if (board[0][2] == board[1][1] &&
        board[1][1] == board[2][0])
    {
        if (board[0][2] == 'O') return +10;
        if (board[0][2] == 'X') return -10;
    }

    return 0; // No winner
} 

// Minimax algorithm
int minimax(int depth, int isMax)
{
    int score = evaluate();

    // Terminal state: someone won
    if (score == 10 || score == -10)
        return score;

    // Check for draw (no moves left)
    int movesLeft = 0;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ')
                movesLeft = 1;

    if (!movesLeft)
        return 0;

    // Maximizer (Computer)
    if (isMax)
    {
        int best = -1000;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] == ' ')
                {
                    board[i][j] = 'O';
                    int val = minimax(depth + 1, 0);
                    best = (val > best) ? val : best;
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    }

    // Minimizer (Player)
    else
    {
        int best = 1000;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] == ' ')
                {
                    board[i][j] = 'X';
                    int val = minimax(depth + 1, 1);
                    best = (val < best) ? val : best;
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    }
}


// Function for computer's optimal move using Minimax
void findBestMove(int *bestRow, int *bestCol)
{
    int bestVal = -1000;
    *bestRow = -1;
    *bestCol = -1;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == ' ')
            {
                board[i][j] = 'O'; // Computer's move
                int moveVal = minimax(0, 0);
                board[i][j] = ' '; // Undo move

                if (moveVal > bestVal)
                {
                    *bestRow = i;
                    *bestCol = j;
                    bestVal = moveVal;
                }
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

        char result = checkWinner();
        if (result == 'X')
        {
            printBoard();
            printf("You win!\n");
            break;
        } else if (result == 'D')
        {
            printBoard();
            printf("It's a draw!\n");
            break;
        }

        printBoard();
        computerMove();

        result = checkWinner();
        if (result == 'O')
        {
            printBoard();
            printf("Computer wins!\n");
            break;
        } else if (result == 'D')
        {
            printBoard();
            printf("It's a draw!\n");
            break;
        }
    }

    return 0;
}