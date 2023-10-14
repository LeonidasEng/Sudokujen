/***********************************************************************************************************************************\
|*                                                Sudokujen - A Sudoku Generator & Solver                                          *|
|*                                                           Rules of Sudoku                                                       *|
|*                                                                                                                                 *|
|*                           Rule 1 - Each row must contain the numbers from 1 to 9, without repetitions                           *|
|*                           Rule 2 - Each column must contain the numbers from 1 to 9, without repetitions                        *|
|*                           Rule 3 - The digits can only occur once per block (nonet)                                             *|
|*                           Rule 4 - The sum of every single row, column and nonet must equal 45                                  *|
|*                                                                                                                                 *|
\***********************************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


/* Prototyping of Variables and Functions */
#define GRID_SIZE 9
int grid[GRID_SIZE][GRID_SIZE];
int originalGrid[GRID_SIZE][GRID_SIZE];
int validateSudokuGrid(int row, int column, int number); 
void generateSudokuGrid(void);
void replace_random_numbers();
void printSudoku(void);
void int_to_char_sudoku(int grid[GRID_SIZE][GRID_SIZE], char charGrid[GRID_SIZE][GRID_SIZE]);



int main() 
{
    /* Main Menu - User can select the option to generate a puzzle */
    // If user struggles with the problem they can print the answer
    int flag = 0, flag2 = 0;
    char choice, charGrid[GRID_SIZE][GRID_SIZE];
    printf("***********************************************************************************************************************\n");
    printf("|-------------------------------------------   Sudokujen Puzzle Generator   ------------------------------------------|\n");
    printf("|*******************************************         By LeonidasEng         ******************************************|\n");
    printf("|-------------------------------------------           Version 1.0          ------------------------------------------|\n");
    printf("**********************************************************************************************************************\n");
    do {        
        printf("\nPress 'y' to generate a puzzle or 'x' to exit.\n");
        scanf(" %c", &choice);
        
        if (choice == 'x')  // Main Menu selector
            flag = 1;
        if (choice == 'y')
        {
            do
            {
                generateSudokuGrid();                     // Generate the grid and enter
                memcpy(originalGrid, grid, sizeof(grid)); // To copy origianl grid 
                replace_random_numbers();                 // Replaces random numbers with ASCII character
                int_to_char_sudoku(grid, charGrid);       // Converts Int 2D Array to Char 2D Array
                printf("\n Show Answer? press 'a'\n");
                printf("\n Return to Menu? press 'x'\n");
                scanf(" %c", &choice);                    // User enters choice
                if (choice == 'x') {
                    printf("\n"); 
                    flag2 = 1;
                } else 
                {
                    printf("\n");
                    printSudoku();           // Supposed to print the original answer as all numbers currently it prints ASCII values which I don't want.
                    flag2 = 1;

                }
            } while (flag2 == 0);
            flag = 0;
        }   
    } while (flag == 0);
    
    return 0;  
}

/* Check if number can be placed in the row or column position */
int validateSudokuGrid(int row, int column, int number) {
    int i, j;
    // Check row and column of entire grid
    for (i = 0; i < GRID_SIZE; i++) 
    {
        if (grid[row][i] == number || grid[i][column] == number)
            return 0;
    }
    // Check each block in the grid
    int row_start = (row / 3) * 3;
    int col_start = (column / 3) * 3;
    // Nested for loop checks rows & columns
    for (i = row_start; i < row_start + 3; i++) {
        for (j = col_start; j < col_start + 3; j++) {
            if (grid[i][j] == number)
                return 0;
        }
    }
    return 1;
}

// Generate a random Sudoku puzzle
void generateSudokuGrid() {
    srand(time(NULL));
    int i, j, k, number;
    for (i = 0; i < GRID_SIZE; i++) 
    {
        for (j = 0; j < GRID_SIZE; j++) 
        {
            // Try a random number up to 10 times
            for (k = 0; k < 10; k++) 
            {
                // If no valid number was found, use backtracking algorithm
                if (k == 10) 
                {
                    grid[i][j] = (rand() % 9 + 1);
                    if (j == 0) 
                    {
                        i = i - 2;
                        j = GRID_SIZE - 1;
                    } else 
                        j = j - 2;
                }
                number = (rand() % GRID_SIZE + 1); // generate a number between 1 and 9

                if (validateSudokuGrid(i, j, number)) 
                {
                    grid[i][j] = number;
                    break;
                }
            }
        }
    }
    printf("\nSudoku is valid!\n\n");
}

// Print the Sudoku grid answer
void printSudoku() {
    int i, j;
    for (i = 0; i < GRID_SIZE; i++) {
        for (j = 0; j < GRID_SIZE; j++) {
            printf("%d ", originalGrid[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

/* Replaces random places in grid with blanks */
void replace_random_numbers() 
{
    int i, j, randNumber = 1;
    srand(time(NULL));      // seed the random number generator to produce random output


    while (randNumber < 36) {     // repeat until 36 numbers are replaced (considered an easy Sudoku)
        i = rand() % 9;           // generate random row index
        j = rand() % 9;           // generate random column index
        if (grid[i][j] != 0)      // check if cell is non-zero - using "== 0" doesn't work 
        {    
            grid[i][j] = '/';     // replace with "_" why is it 48 characters out of sync?
            randNumber++;         // increment randNumber of replaced numbers
        }
    }
}


/* To convert Integer Grid to Char Grid so underscores can be used for blank spaces */
void int_to_char_sudoku(int grid[GRID_SIZE][GRID_SIZE], char charGrid[GRID_SIZE][GRID_SIZE]) {
    int i, j;
    for (i = 0; i < GRID_SIZE; i++) {
        for (j = 0; j < GRID_SIZE; j++) {
            charGrid[i][j] = (char) (grid[i][j] + '0'); // convert int to char
            printf("%c ", charGrid[i][j]);
        }
        printf("\n");
    }   
}

