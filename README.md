# Sudokujen
This is a repo for all files pertaining to Sudokujen program


# Sudokujen - A Sudoku Generator in C
This repo is so far a test bed to improve my knowledge, and I have been experimenting with different algorithms to understand how to solve this game.


# Rules of Sudoku
- Rule 1 - Each row must contain the numbers from 1 to 9, without repetitions
- Rule 2 - Each column must contain the numbers from 1 to 9, without repetitions
- Rule 3 - The digits can only occur once per block (nonet)
- Rule 4 - The sum of every single row, column and nonet must equal 45

## Generator program
This program is designed to generate new Sudoku puzzles using bruteforce method.

## Sudoku generator - New
Instead of trying to generate a Sudoku puzzle from scratch, I have used an existing Sudoku puzzle, made removals randomly from the grid and shuffled it in order to make a random sudoku problem. I can then use a backtracking algorithm to test its validity.

With the new version, I know that if I could just reverse the steps I may be able to start from a blank puzzle and generate valid Sudokus from there.


## Sudoku solver - Simpler
The first program proved too complicated at first, the Sudokujen program has been altered to do a simpler problem, trying to solve a specific Sudoku proved easier than trying to generate entirely new problems. I used a backtracking algorithm to resolve the predefined Sudoku puzzle.

