#include <iostream>
using namespace std;

bool isValidMove(int board[9][9], int row, int col, int num) {

    // Check row
    for (int j = 0; j < 9; j++) {
        if (board[row][j] == num) {
            return false;
        }
    }

    // Check column
    for (int i = 0; i < 9; i++) {
        if (board[i][col] == num) {
            return false;
        }
    }

    // Find starting position of 3x3 box
    int startRow = row - row % 3;
    int startCol = col - col % 3;

    // Check 3x3 box
    for (int i = startRow; i < startRow + 3; i++) {
        for (int j = startCol; j < startCol + 3; j++) {
            if (board[i][j] == num) {
                return false;
            }
        }
    }

    return true;
}

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

int main() {

    int board[9][9] = {
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

    cout << "=========================\n";
    cout << "         SUDOKU\n";
    cout << "=========================\n";

    displayBoard(board);

    int row, col, num;

    cout << "\nEnter row (1-9): ";
    cin >> row;

    cout << "Enter column (1-9): ";
    cin >> col;

    cout << "Enter number (1-9): ";
    cin >> num;

    row--;
    col--;

    if (board[row][col] != 0) {
        cout << "\nThat cell is already filled!\n";
    }
    else if (isValidMove(board, row, col, num)) {

        board[row][col] = num;

        cout << "\nMove accepted!\n";

    }
    else {
        cout << "\nInvalid move!\n";
    }

    displayBoard(board);

    return 0;
}
