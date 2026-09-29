#include <iostream>
#include <algorithm>
#include <random>
#include <limits>

using namespace std;

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

bool solveSudoku(int board[9][9], mt19937& rng) {

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

    int numbers[9] = {
        1, 2, 3, 4, 5, 6, 7, 8, 9
    };

    shuffle(numbers, numbers + 9, rng);

    for (int i = 0; i < 9; i++) {

        int num = numbers[i];

        if (isSafe(board, row, col, num)) {

            board[row][col] = num;

            if (solveSudoku(board, rng)) {
                return true;
            }

            board[row][col] = 0;
        }
    }

    return false;
}

int countSolutions(int board[9][9]) {

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
        return 1;
    }

    int totalSolutions = 0;

    for (int num = 1; num <= 9; num++) {

        if (isSafe(board, row, col, num)) {

            board[row][col] = num;

            totalSolutions += countSolutions(board);

            board[row][col] = 0;

            if (totalSolutions > 1) {
                return totalSolutions;
            }
        }
    }

    return totalSolutions;
}

void copyBoard(int source[9][9], int destination[9][9]) {

    for (int i = 0; i < 9; i++) {

        for (int j = 0; j < 9; j++) {
            destination[i][j] = source[i][j];
        }
    }
}

void generatePuzzle(
    int solution[9][9],
    int puzzle[9][9],
    int cellsToRemove,
    mt19937& rng
) {

    copyBoard(solution, puzzle);

    int removed = 0;

    while (removed < cellsToRemove) {

        int row = rng() % 9;
        int col = rng() % 9;

        if (puzzle[row][col] == 0) {
            continue;
        }

        int originalValue = puzzle[row][col];

        puzzle[row][col] = 0;

        int testBoard[9][9];

        copyBoard(puzzle, testBoard);

        int solutions = countSolutions(testBoard);

        if (solutions == 1) {
            removed++;
        }
        else {
            puzzle[row][col] = originalValue;
        }
    }
}

void displayBoard(int board[9][9]) {

    cout << "\n";

    cout << "       1 2 3   4 5 6   7 8 9\n";
    cout << "     +-------+-------+-------+\n";

    for (int i = 0; i < 9; i++) {

        cout << "  " << i + 1 << "  | ";

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
            cout << "     +-------+-------+-------+\n";
        }
    }
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

void resetBoard(int puzzle[9][9], int board[9][9]) {
    copyBoard(puzzle, board);
}

void showTitle() {

    cout << "\n";
    cout << "=====================================\n";
    cout << "              SUDOKU\n";
    cout << "=====================================\n";
}

int chooseDifficulty() {

    int choice;

    while (true) {

        cout << "\nChoose Difficulty\n";
        cout << "-----------------\n";
        cout << "1. Easy\n";
        cout << "2. Medium\n";
        cout << "3. Hard\n";
        cout << "4. Exit\n";
        cout << "\nEnter choice: ";

        cin >> choice;

        if (cin.fail()) {

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "\nInvalid input.\n";
            continue;
        }

        if (choice >= 1 && choice <= 4) {
            return choice;
        }

        cout << "\nPlease enter a number between 1 and 4.\n";
    }
}

int getCellsToRemove(int difficulty) {

    if (difficulty == 1) {
        return 35;
    }

    if (difficulty == 2) {
        return 45;
    }

    return 50;
}

void playGame(
    int puzzle[9][9],
    int solution[9][9],
    int board[9][9]
) {

    int mistakes = 0;
    int hints = 0;

    while (true) {

        showTitle();

        displayBoard(board);

        cout << "\nMistakes: " << mistakes;
        cout << "    Hints used: " << hints;

        cout << "\n\n";
        cout << "1. Enter Move\n";
        cout << "2. Hint\n";
        cout << "3. Restart\n";
        cout << "4. Show Solution\n";
        cout << "5. Quit to Main Menu\n";

        cout << "\nChoose option: ";

        int choice;
        cin >> choice;

        if (cin.fail()) {

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "\nInvalid input.";
            continue;
        }

        if (choice == 1) {

            int row;
            int col;
            int num;

            cout << "\nEnter row (1-9): ";
            cin >> row;

            cout << "Enter column (1-9): ";
            cin >> col;

            cout << "Enter number (1-9): ";
            cin >> num;

            if (cin.fail()) {

                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "\nInvalid input.";
                continue;
            }

            if (row < 1 || row > 9 ||
                col < 1 || col > 9 ||
                num < 1 || num > 9) {

                cout << "\nInvalid row, column, or number.";
                continue;
            }

            row--;
            col--;

            if (puzzle[row][col] != 0) {

                cout << "\nThis is an original number and cannot be changed.";
                continue;
            }

            if (board[row][col] != 0) {

                cout << "\nThis cell is already filled.";
                continue;
            }

            if (solution[row][col] == num) {

                board[row][col] = num;

                cout << "\nCorrect!";

                if (isComplete(board)) {

                    showTitle();
                    displayBoard(board);

                    cout << "\n=====================================\n";
                    cout << "          SUDOKU COMPLETED!\n";
                    cout << "=====================================\n";

                    cout << "\nTotal mistakes: " << mistakes;
                    cout << "\nHints used: " << hints;
                    cout << "\n";

                    cout << "\nPress Enter to continue...";

                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cin.get();

                    return;
                }
            }
            else {

                mistakes++;

                cout << "\nWrong number!";
                cout << "\nMistakes: " << mistakes;
            }
        }

        else if (choice == 2) {

            bool hintAvailable = false;

            for (int i = 0; i < 9; i++) {

                for (int j = 0; j < 9; j++) {

                    if (board[i][j] == 0) {

                        board[i][j] = solution[i][j];

                        hints++;

                        cout << "\nHint added at row "
                             << i + 1
                             << ", column "
                             << j + 1
                             << ".";

                        hintAvailable = true;

                        break;
                    }
                }

                if (hintAvailable) {
                    break;
                }
            }

            if (!hintAvailable) {
                cout << "\nNo hints available.";
            }
        }

        else if (choice == 3) {

            resetBoard(puzzle, board);

            mistakes = 0;
            hints = 0;

            cout << "\nGame restarted.";
        }

        else if (choice == 4) {

            cout << "\nSolution:\n";

            displayBoard(solution);

            cout << "\nPress Enter to continue...";

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }

        else if (choice == 5) {

            cout << "\nReturning to main menu...\n";

            return;
        }

        else {

            cout << "\nInvalid option.";
        }

        cout << "\n";
    }
}

int main() {

    random_device rd;
    mt19937 rng(rd());

    while (true) {

        showTitle();

        int difficulty = chooseDifficulty();

        if (difficulty == 4) {

            cout << "\nThank you for playing Sudoku!\n";
            break;
        }

        int cellsToRemove = getCellsToRemove(difficulty);

        int solution[9][9] = {};

        cout << "\nGenerating Sudoku...\n";

        if (!solveSudoku(solution, rng)) {

            cout << "Could not generate Sudoku.\n";
            return 1;
        }

        int puzzle[9][9];

        generatePuzzle(
            solution,
            puzzle,
            cellsToRemove,
            rng
        );

        int board[9][9];

        copyBoard(puzzle, board);

        playGame(
            puzzle,
            solution,
            board
        );
    }

    return 0;
}
