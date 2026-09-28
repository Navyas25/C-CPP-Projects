#include <iostream>
using namespace std;

void displayBoard(int board[9][9]) {

    cout << "\n+-------+-------+-------+\n";

    for (int i = 0; i < 9; i++) {

        cout << "| ";

        for (int j = 0; j < 9; j++) {

            if (board[i][j] == 0) {
                cout << ". ";
            }
            else {
                cout << board[i][j] << " ";
            }

            if ((j + 1) % 3 == 0) {
                cout << "| ";
            }
        }

        cout << "\n";

        if ((i + 1) % 3 == 0) {
            cout << "+-------+-------+-------+\n";
        }
    }
}

bool isSafe(int board[9][9], int row, int col, int num) {

    for (int j = 0; j < 9; j++) {

        if (board[row][j] == num) {
            return false;
        }
    }

    for (int i = 0; i < 9; i++) {

        if (board[i][col] == num) {
            return false;
        }
    }

    int startRow = row - row % 3;
    int startCol = col - col % 3;

    for (int i = startRow; i < startRow + 3; i++) {

        for (int j = startCol; j < startCol + 3; j++) {

            if (board[i][j] == num) {
                return false;
            }
        }
    }

    return true;
}

bool solveSudoku(int board[9][9]) {

    int row = -1;
    int col = -1;

    bool emptyFound = false;

    for (int i = 0; i < 9; i++) {

        for (int j = 0; j < 9; j++) {

            if (board[i][j] == 0) {

                row = i;
                col = j;

                emptyFound = true;

                break;
            }
        }

        if (emptyFound) {
            break;
        }
    }

    if (!emptyFound) {
        return true;
    }

    for (int num = 1; num <= 9; num++) {

        if (isSafe(board, row, col, num)) {

            board[row][col] = num;

            if (solveSudoku(board)) {
                return true;
            }

            board[row][col] = 0;
        }
    }

    return false;
}

bool isComplete(int board[9][9]) {

    for (int i = 0; i < 9; i++) {

        for (int j = 0; j < 9; j++) {

            if (board[i][j] == 0) {
                return false;
            }
        }
    }

    return true;
}

int main() {

    int puzzle[9][9] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},

        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},

        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    int solution[9][9];

    // Copy puzzle into solution
    for (int i = 0; i < 9; i++) {

        for (int j = 0; j < 9; j++) {

            solution[i][j] = puzzle[i][j];
        }
    }

    // Solve the copied board
    if (!solveSudoku(solution)) {

        cout << "This puzzle has no solution.\n";
        return 0;
    }

    int board[9][9];

    // Copy puzzle into player's board
    for (int i = 0; i < 9; i++) {

        for (int j = 0; j < 9; j++) {

            board[i][j] = puzzle[i][j];
        }
    }

    cout << "=========================\n";
    cout << "         SUDOKU\n";
    cout << "=========================\n";

    while (!isComplete(board)) {

        displayBoard(board);

        int row;
        int col;
        int num;

        cout << "\nEnter row (1-9) or -1 to quit: ";
        cin >> row;

        if (row == -1) {

            cout << "\nGame exited.\n";
            return 0;
        }

        cout << "Enter column (1-9): ";
        cin >> col;

        cout << "Enter number (1-9): ";
        cin >> num;

        if (row < 1 || row > 9 ||
            col < 1 || col > 9 ||
            num < 1 || num > 9) {

            cout << "\nInvalid input! Try again.\n";
            continue;
        }

        row--;
        col--;

        if (puzzle[row][col] != 0) {

            cout << "\nYou cannot change an original number!\n";
            continue;
        }

        if (solution[row][col] == num) {

            board[row][col] = num;

            cout << "\nCorrect!\n";
        }
        else {

            cout << "\nWrong number! Try again.\n";
        }
    }

    displayBoard(board);

    cout << "\n=========================\n";
    cout << "     SUDOKU COMPLETED!\n";
    cout << "=========================\n";

    return 0;
}
