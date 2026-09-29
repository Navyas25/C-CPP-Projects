#include <iostream>
using namespace std;

void displayBoard(int board[9][9])
{
    cout << "\n";

    cout << "    1 2 3   4 5 6   7 8 9\n";
    cout << "  +-------+-------+-------+\n";

    for (int i = 0; i < 9; i++)
    {
        cout << i + 1 << " | ";

        for (int j = 0; j < 9; j++)
        {
            if (board[i][j] == 0)
                cout << ". ";
            else
                cout << board[i][j] << " ";

            if ((j + 1) % 3 == 0)
                cout << "| ";
        }

        cout << endl;

        if ((i + 1) % 3 == 0)
            cout << "  +-------+-------+-------+\n";
    }
}

bool isComplete(int board[9][9])
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (board[i][j] == 0)
                return false;
        }
    }

    return true;
}

int main()
{
    int puzzle[9][9] =
    {
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

    int solution[9][9] =
    {
        {5, 3, 4, 6, 7, 8, 9, 1, 2},
        {6, 7, 2, 1, 9, 5, 3, 4, 8},
        {1, 9, 8, 3, 4, 2, 5, 6, 7},

        {8, 5, 9, 7, 6, 1, 4, 2, 3},
        {4, 2, 6, 8, 5, 3, 7, 9, 1},
        {7, 1, 3, 9, 2, 4, 8, 5, 6},

        {9, 6, 1, 5, 3, 7, 2, 8, 4},
        {2, 8, 7, 4, 1, 9, 6, 3, 5},
        {3, 4, 5, 2, 8, 6, 1, 7, 9}
    };

    cout << "============================\n";
    cout << "          SUDOKU\n";
    cout << "============================\n";

    while (!isComplete(puzzle))
    {
        displayBoard(puzzle);

        int row, col, num;

        cout << "\nEnter row (1-9) or -1 to quit: ";
        cin >> row;

        if (row == -1)
        {
            cout << "\nGame ended.\n";
            return 0;
        }

        cout << "Enter column (1-9): ";
        cin >> col;

        cout << "Enter number (1-9): ";
        cin >> num;

        if (row < 1 || row > 9 ||
            col < 1 || col > 9 ||
            num < 1 || num > 9)
        {
            cout << "\nInvalid input. Try again.\n";
            continue;
        }

        row--;
        col--;

        if (puzzle[row][col] != 0)
        {
            cout << "\nYou cannot change this number.\n";
            continue;
        }

        if (solution[row][col] == num)
        {
            puzzle[row][col] = num;
            cout << "\nCorrect!\n";
        }
        else
        {
            cout << "\nWrong answer. Try again.\n";
        }
    }

    displayBoard(puzzle);

    cout << "\n============================\n";
    cout << "       YOU SOLVED IT!\n";
    cout << "============================\n";

    return 0;
}
