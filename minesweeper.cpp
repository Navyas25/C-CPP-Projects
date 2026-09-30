
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int SIZE = 9;
const int MINES = 10;

void createBoard(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = '#';
        }
    }
}

void placeMines(char mineBoard[SIZE][SIZE]) {
    int minesPlaced = 0;

    while (minesPlaced < MINES) {
        int row = rand() % SIZE;
        int col = rand() % SIZE;

        if (mineBoard[row][col] != '*') {
            mineBoard[row][col] = '*';
            minesPlaced++;
        }
    }
}

int countMines(char mineBoard[SIZE][SIZE], int row, int col) {
    int count = 0;

    for (int i = row - 1; i <= row + 1; i++) {
        for (int j = col - 1; j <= col + 1; j++) {

            if (i >= 0 && i < SIZE && j >= 0 && j < SIZE) {
                if (mineBoard[i][j] == '*') {
                    count++;
                }
            }
        }
    }

    return count;
}

void showBoard(char board[SIZE][SIZE]) {
    cout << "\n   ";

    for (int j = 0; j < SIZE; j++) {
        cout << j << " ";
    }

    cout << endl;

    for (int i = 0; i < SIZE; i++) {
        cout << i << "  ";

        for (int j = 0; j < SIZE; j++) {
            cout << board[i][j] << " ";
        }

        cout << endl;
    }
}

void showMines(char mineBoard[SIZE][SIZE]) {
    cout << "\nMines were located here:\n";

    cout << "   ";

    for (int j = 0; j < SIZE; j++) {
        cout << j << " ";
    }

    cout << endl;

    for (int i = 0; i < SIZE; i++) {
        cout << i << "  ";

        for (int j = 0; j < SIZE; j++) {
            cout << mineBoard[i][j] << " ";
        }

        cout << endl;
    }
}

bool checkWin(char board[SIZE][SIZE], char mineBoard[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {

            if (mineBoard[i][j] != '*' && board[i][j] == '#') {
                return false;
            }
        }
    }

    return true;
}

int main() {
    srand(time(0));

    char mineBoard[SIZE][SIZE];
    char board[SIZE][SIZE];

    createBoard(mineBoard);
    createBoard(board);

    placeMines(mineBoard);

    int row, col;

    cout << "============================\n";
    cout << "       MINESWEEPER\n";
    cout << "============================\n";
    cout << "Board: 9 x 9\n";
    cout << "Mines: 10\n";

    while (true) {

        showBoard(board);

        cout << "\nEnter row: ";
        cin >> row;

        cout << "Enter column: ";
        cin >> col;

        if (row < 0 || row >= SIZE || col < 0 || col >= SIZE) {
            cout << "\nInvalid position. Enter values from 0 to 8.\n";
            continue;
        }

        if (board[row][col] != '#') {
            cout << "\nYou already opened this cell.\n";
            continue;
        }

        if (mineBoard[row][col] == '*') {
            board[row][col] = '*';

            cout << "\nBOOM! You hit a mine!\n";

            showMines(mineBoard);

            cout << "\nGAME OVER!\n";
            break;
        }

        int mines = countMines(mineBoard, row, col);

        board[row][col] = '0' + mines;

        if (checkWin(board, mineBoard)) {
            showBoard(board);

            cout << "\nCongratulations!\n";
            cout << "You found all the safe cells!\n";
            break;
        }
    }

    return 0;
}
