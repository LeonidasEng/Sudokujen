#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define SIZE 9

int board[SIZE][SIZE];
bool firstCall = true;  // Static variable to track if it's the top-level call

// Functions to solve the board
bool isSafe(int board[SIZE][SIZE], int row, int col, int num);
bool solveBoard(int board[SIZE][SIZE]);
bool findUnassigned(int board[SIZE][SIZE], int *row, int *col);

void printBoard(int board[SIZE][SIZE]) {
    printf("+---------+---------+---------+\n");
    for (int row = 0; row < SIZE; row++) {
        if (row % 3 == 0 && row != 0) {
            printf("+---------+---------+---------+\n");
        }
        for (int col = 0; col < SIZE; col++) {
            if (col % 3 == 0) {
                printf("|");
            }
            printf("%2d ", board[row][col]);
        }
        printf("|\n");
    }
    printf("+---------+---------+---------+\n");
}

// Shuffle the 2D array using variant of Fisher-Yates algorithm
void shuffle(int array[SIZE*SIZE][2]) {
    for (int i = SIZE*SIZE - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp[2] = {array[i][0], array[i][1]};
        array[i][0] = array[j][0];
        array[i][1] = array[j][1];
        array[j][0] = temp[0];
        array[j][1] = temp[1];
    }
    /* 
    
    Explanation:
    Create an array to reduce complexity of 9x9 grid to an array of less dimension making it easier to shuffle.
    Start at the end of the array and work backwards (preference) each element is shuffled with the current position.
    For every iteration (i) a random number (j) is selected from range [0, i]
    First, the element at position i is stored in a temporary variable temp.
    Then, the element at position i is overwritten with the element at position j.
    Finally, the element at position j is overwritten with the value from temp, effectively completing the swap.

    */
}

bool solveBoardCount(int board[SIZE][SIZE], int *count) {
    
    int row, col;

    if (!findUnassigned(board, &row, &col)) {
        (*count)++;
        return true; // Found a solution
    }
    /* For current empty cell loop iterates through trying numbers from 1-9. If it is safe to use the number
    the function is recursively called to solve the next cells. If a solution is not found it backtracks by 
    resetting the current cell to zero (unassigned) */
    for (int num = 1; num <= SIZE; num++) {
        if (isSafe(board, row, col, num)) {
            board[row][col] = num;
            solveBoardCount(board, count);
            board[row][col] = 0;
        }
    }

    if (firstCall) {
        if (*count == 0) {
            printf("No solution.\n");
        } else {
            printf("Total valid solutions: %d\n", *count);
        }
        firstCall = false;  // Ensure this block doesn't execute again in subsequent calls
    }

    return false;
}

void prepareSolver() {
    firstCall = true; // Ensures validation is sought for every new puzzle generated
}

int main() {
    srand(time(0));

    printf("***********************************************************************************************************************\n");
    printf("|-------------------------------------------   Sudokujen Puzzle Generator   ------------------------------------------|\n");
    printf("|*******************************************         By LeonidasEng         ******************************************|\n");
    printf("|-------------------------------------------           Version 1.0          ------------------------------------------|\n");
    printf("**********************************************************************************************************************\n");

    // Adding menu
    int flag, sflag, count = 0;
    char choice;
    // Valid predefined grid (filled with 81 numbers).
    int predefinedBoard[SIZE][SIZE] = {
        {5, 3, 4, 6, 7, 8, 9, 1, 2},
        {6, 7, 2, 1, 9, 5, 3, 4, 8},
        {1, 9, 8, 3, 4, 2, 5, 6, 7},
        {8, 5, 9, 7, 6, 1, 4, 2, 3},
        {4, 2, 6, 8, 5, 3, 7, 9, 1},
        {7, 1, 3, 9, 2, 4, 8, 5, 6},
        {9, 6, 1, 5, 3, 7, 2, 8, 4},
        {2, 8, 7, 4, 1, 9, 6, 3, 5},
        {3, 4, 5, 2, 8, 6, 1, 7, 9}
    };
    do 
    {
        printf("\nPress 'y' to generate a puzzle or 'x' to exit.\n");
        scanf(" %c", &choice);

        if (choice == 'x')  // Main Menu selector
            flag = 1;
        if (choice == 'y')
        {
            // Submenu for selecting difficulty
            do {
                printf("\nSelect difficulty:\n");
                printf("1. Easy\n");
                printf("2. Intermediate\n");
                printf("3. Hard\n");
                scanf("%d", &sflag);

            if (sflag >= 1 && sflag <= 3) {
                break;  // exit submenu loop
            } else {
                printf("\nInvalid choice. Please select again.\n");
            }
        } while (1);

            // Setting the removal count based on difficulty choice.
            int removalCount;
            if (sflag == 1) {
                removalCount = 40;
            } else if (sflag == 2) {
                removalCount = 50;
            } else if (sflag == 3) {
                removalCount = 60;
            }

            prepareSolver(); // check validity
            printf("New puzzle generating...\n");

            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    board[i][j] = predefinedBoard[i][j];
                }
            }

            // Make list of 81 cells and shuffle randomly.
            int positions[SIZE*SIZE][2];
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    positions[i * SIZE + j][0] = i;
                    positions[i * SIZE + j][1] = j;
                }
            }

            shuffle(positions);

            // While there are still positions left in the list, take the next one and clear the corresponding cell.
            for (int i = 0; i < SIZE*SIZE; i++) {
                int x = positions[i][0];
                int y = positions[i][1];
                int temp = board[x][y];
                board[x][y] = 0;

                // Use fast backtracking solver to check if the solution is unique.
                int count = 0;
                solveBoardCount(board, &count);

                // If there are multiple solutions for the current board, revert the last cell that was cleared
                if (count > 1) {
                    board[x][y] = temp;
                }

                if (i >= removalCount - 1)
                {
                    break;
                }
                
                // // Print progress to prevent hanging program
                // printf("Tested removing from position (%d, %d). Current removal count: %d\n", x, y, i + 1);
                // printBoard(board);  // Optionally print the board state
                // printf("\n\n");
            }
            printBoard(board);

            // Ask the user if they want to see the solution
            printf("Print solution? (y/n): ");
            scanf(" %c", &choice);  // Notice the space before %c to consume any leftover newline character
            if (choice == 'y') {
                solveBoard(board);
                printBoard(board);  // Assuming you want to print the solved board for the user to see
            } else if (choice == 'n') {
                break;
            }
        }
    } while (flag == 0);

    return 0;
}

/* isSafe is used to determine the 3 rules of Sudoku */
bool isSafe(int board[SIZE][SIZE], int row, int col, int num) {
    for (int x = 0; x < SIZE; x++) {
        if (board[row][x] == num) {
            return false; // checks specified row all columns if number is safe to place
        }
    }

    for (int x = 0; x < SIZE; x++) {
        if (board[x][col] == num) {
            return false; // checks specified column all rows if number is safe to place
        }
    }

    // The below code checks each sub-grid that numbers do not repeat
    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }
    return true; // If no false returned the number can safely be placed in the cell
}

bool solveBoard(int board[SIZE][SIZE]) {
    int row, col;
    if (!findUnassigned(board, &row, &col))
        return true;

    for (int num = 1; num <= SIZE; num++) {
        if (isSafe(board, row, col, num)) {
            board[row][col] = num;
            if (solveBoard(board))
                return true;
            board[row][col] = 0;
        }
    }

    return false;
}

bool findUnassigned(int board[SIZE][SIZE], int *row, int *col) {
    for (*row = 0; *row < SIZE; (*row)++)
        for (*col = 0; *col < SIZE; (*col)++)
            if (board[*row][*col] == 0)
                return true;
    return false;
}
