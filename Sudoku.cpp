

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

void generatePuzzle(
    int solution[9][9],
    int puzzle[9][9],
    int cellsToRemove,
    mt19937& rng
) {

    for (int i = 0; i < 9; i++) {

        for (int j = 0; j < 9; j++) {

            puzzle[i][j] = solution[i][j];
        }
    }

    int removed = 0;

    while (removed < cellsToRemove) {

        int row = rng() % 9;
        int col = rng() % 9;

        if (puzzle[row][col] != 0) {

            puzzle[row][col] = 0;
            removed++;
        }
    }
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

    random_device rd;
    mt19937 rng(rd());

    int solution[9][9] = {};

    if (!solveSudoku(solution, rng)) {

        cout << "Could not generate Sudoku.\n";
        return 0;
    }

    int difficulty;

    cout << "=========================\n";
    cout << "         SUDOKU\n";
    cout << "=========================\n";

    cout << "\nChoose difficulty:\n";
    cout << "1. Easy\n";
    cout << "2. Medium\n";
    cout << "3. Hard\n";
    cout << "\nEnter choice: ";

    cin >> difficulty;

    int cellsToRemove;

    if (difficulty == 1) {
        cellsToRemove = 35;
    }
    else if (difficulty == 2) {
        cellsToRemove = 45;
    }
    else if (difficulty == 3) {
        cellsToRemove = 55;
    }
    else {

        cout << "\nInvalid choice!\n";
        return 0;
    }

    int puzzle[9][9];

    generatePuzzle(
        solution,
        puzzle,
        cellsToRemove,
        rng
    );

    int board[9][9];

    for (int i = 0; i < 9; i++) {

        for (int j = 0; j < 9; j++) {

            board[i][j] = puzzle[i][j];
        }
    }

    cout << "\nYour Sudoku:\n";

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

            cout << "\nInvalid input!\n";
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
