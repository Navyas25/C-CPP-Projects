
#include <iostream>
using namespace std;

void initializeBoard(char board[3][3]) {
    char number = '1';

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = number;
            number++;
        }
    }
}

void displayBoard(char board[3][3]) {
    cout << "\n";

    for (int i = 0; i < 3; i++) {
        cout << " " << board[i][0] << " | "
             << board[i][1] << " | "
             << board[i][2] << endl;

        if (i < 2) {
            cout << "---|---|---\n";
        }
    }

    cout << endl;
}

bool makeMove(char board[3][3], int position, char player) {
    int row = (position - 1) / 3;
    int col = (position - 1) % 3;

    if (board[row][col] != 'X' && board[row][col] != 'O') {
        board[row][col] = player;
        return true;
    }

    return false;
}

bool checkWinner(char board[3][3], char player) {

    for (int i = 0; i < 3; i++) {
        if (board[i][0] == player &&
            board[i][1] == player &&
            board[i][2] == player) {
            return true;
        }
    }

    for (int j = 0; j < 3; j++) {
        if (board[0][j] == player &&
            board[1][j] == player &&
            board[2][j] == player) {
            return true;
        }
    }

    if (board[0][0] == player &&
        board[1][1] == player &&
        board[2][2] == player) {
        return true;
    }

    if (board[0][2] == player &&
        board[1][1] == player &&
        board[2][0] == player) {
        return true;
    }

    return false;
}

bool checkDraw(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != 'X' && board[i][j] != 'O') {
                return false;
            }
        }
    }

    return true;
}

int main() {

    char board[3][3];

    initializeBoard(board);

    char player = 'X';
    int position;

    cout << "========================\n";
    cout << "       TIC TAC TOE\n";
    cout << "========================\n";

    while (true) {

        displayBoard(board);

        cout << "Player " << player << ", enter position (1-9): ";
        cin >> position;

        if (position < 1 || position > 9) {
            cout << "Invalid position. Choose between 1 and 9.\n";
            continue;
        }

        if (!makeMove(board, position, player)) {
            cout << "That position is already occupied.\n";
            continue;
        }

        if (checkWinner(board, player)) {
            displayBoard(board);

            cout << "Player " << player << " wins!\n";
            break;
        }

        if (checkDraw(board)) {
            displayBoard(board);

            cout << "It's a draw!\n";
            break;
        }

        if (player == 'X') {
            player = 'O';
        } else {
            player = 'X';
        }
    }

    return 0;
}

