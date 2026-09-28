#include <iostream>
using namespace std;

bool isValidMove(int board[9][9], int row, int col, int num) {

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

    while (!isComplete(board)) {

        displayBoard(board);

        int row, col, num;

        cout << "\nEnter row (1-9) or -1 to quit: ";
        cin >> row;

        if (row == -1) {
            cout << "\nGame exited.\n";
            break;
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

        if (board[row][col] != 0) {

            cout << "\nThat cell is already filled!\n";
            continue;
        }

        if (isValidMove(board, row, col, num)) {

            board[row][col] = num;
            cout << "\nMove accepted!\n";

        }
        else {

            cout << "\nInvalid move! That number already exists in "
                 << "the row, column, or 3x3 box.\n";
        }
    }

    if (isComplete(board)) {

        displayBoard(board);

        cout << "\n=========================\n";
        cout << "     SUDOKU COMPLETED!\n";
        cout << "=========================\n";
    }

    return 0;
}
