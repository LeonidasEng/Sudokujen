#include <stdio.h>
#include <stdbool.h>

#define N 9

bool is_valid(int grid[N][N], int r, int c, int k) {
    for (int i = 0; i < N; i++) {
        if (grid[r][i] == k || grid[i][c] == k) {
            return false;
        }
    }

    int startRow = r - r % 3, startCol = c - c % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i + startRow][j + startCol] == k) {
                return false;
            }
        }
    }
    return true;
}

bool solve(int grid[N][N], int r, int c) {
    if (r == N - 1 && c == N) {
        return true;
    }
    if (c == N) {
        r++;
        c = 0;
    }
    if (grid[r][c] != 0) {
        return solve(grid, r, c + 1);
    }

    for (int k = 1; k <= N; k++) {
        if (is_valid(grid, r, c, k)) {
            grid[r][c] = k;
            if (solve(grid, r, c + 1)) {
                return true;
            }
            grid[r][c] = 0;
        }
    }
    return false;
}

int main() {
    int grid[N][N] = {
        {0, 0, 0, 8, 0, 5, 4, 2, 7},
        {0, 0, 0, 2, 0, 3, 9, 0, 5},
        {0, 2, 4, 7, 0, 1, 0, 0, 0},
        {7, 4, 0, 0, 8, 6, 1, 0, 0},
        {0, 0, 8, 9, 1, 0, 7, 0, 4},
        {0, 1, 0, 0, 3, 0, 0, 9, 8},
        {0, 0, 0, 0, 0, 0, 0, 0, 1},
        {9, 0, 1, 3, 7, 0, 0, 0, 6},
        {2, 0, 0, 0, 5, 0, 3, 4, 0}
    };

    if (solve(grid, 0, 0)) {
        for (int r = 0; r < N; r++) {
            for (int d = 0; d < N; d++) {
                printf("%d ", grid[r][d]);
            }
            printf("\n");
        }
    } else {
        printf("no solution exists\n");
    }

    return 0;
}
