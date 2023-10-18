#include <stdio.h>
#include <stdbool.h>

#define N 8

int board[N][N];

bool isSafe(int x, int y) {
    int i, j;
    
    for (i = 0; i < y; i++) {
        if (board[x][i])
            return false;
    }

    for (i = x, j = y; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j])
            return false;
    }

    for (i = x, j = y; j >= 0 && i < N; i++, j--) {
        if (board[i][j])
            return false;
    }

    return true;
}

bool solveEightQueens(int col) {
    if (col >= N)
        return true;

    for (int i = 0; i < N; i++) {
        if (isSafe(i, col)) {
            board[i][col] = 1;

            if (solveEightQueens(col + 1))
                return true;

            board[i][col] = 0; // backtracking
        }
    }

    return false;
}

void printSolution() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf(" %d ", board[i][j]);
        }
        printf("\n");
    }
}

int main() {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            board[i][j] = 0;

    if (solveEightQueens(0) == false) {
        printf("Solution does not exist");
        return 0;
    }

    printSolution();
    return 0;
}
