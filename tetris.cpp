#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

const int ROWS = 20;
const int COLS = 10;
const int CELL_SIZE = 30;

const int WINDOW_WIDTH = 500;
const int WINDOW_HEIGHT = 650;

// Piece colors
sf::Color getColor(int index) {
    sf::Color colors[7] = {
        sf::Color::Cyan,
        sf::Color::Blue,
        sf::Color(255, 165, 0),
        sf::Color::Yellow,
        sf::Color::Green,
        sf::Color::Magenta,
        sf::Color::Red
    };

    return colors[index];
}

// Background colors for each level
sf::Color getBackground(int level) {
    sf::Color backgrounds[6] = {
        sf::Color(20, 25, 45),
        sf::Color(35, 25, 55),
        sf::Color(20, 45, 55),
        sf::Color(55, 30, 35),
        sf::Color(45, 45, 20),
        sf::Color(55, 25, 55)
    };

    return backgrounds[level - 1];
}

class Tetromino {

private:

    inline static const int shapes[7][4][4] = {

        {
            {0, 0, 0, 0},
            {1, 1, 1, 1},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        },

        {
            {1, 0, 0, 0},
            {1, 1, 1, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        },

        {
            {0, 0, 1, 0},
            {1, 1, 1, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        },

        {
            {0, 1, 1, 0},
            {0, 1, 1, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        },

        {
            {0, 1, 1, 0},
            {1, 1, 0, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        },

        {
            {0, 1, 0, 0},
            {1, 1, 1, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        },

        {
            {1, 1, 0, 0},
            {0, 1, 1, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        }

    };

    int shape[4][4]{};
    int colorIndex = 0;

    int row = 0;
    int col = 3;

public:

    void setType(int type) {

        colorIndex = type;

        row = 0;
        col = 3;

        for (int r = 0; r < 4; r++) {
            for (int c = 0; c < 4; c++) {
                shape[r][c] = shapes[type][r][c];
            }
        }
    }

    int getCell(int r, int c) const {
        return shape[r][c];
    }

    int getColor() const {
        return colorIndex;
    }

    int getRow() const {
        return row;
    }

    int getCol() const {
        return col;
    }

    void setPosition(int newRow, int newCol) {
        row = newRow;
        col = newCol;
    }

    void move(int rowChange, int colChange) {
        row += rowChange;
        col += colChange;
    }

    void rotate() {

        int rotated[4][4] = {};

        for (int r = 0; r < 4; r++) {
            for (int c = 0; c < 4; c++) {

                rotated[c][3 - r] = shape[r][c];

            }
        }

        for (int r = 0; r < 4; r++) {
            for (int c = 0; c < 4; c++) {

                shape[r][c] = rotated[r][c];

            }
        }
    }

};

class Board {

private:

    int grid[ROWS][COLS] = {};

public:

    bool canPlace(const Tetromino& piece) const {

        for (int r = 0; r < 4; r++) {
            for (int c = 0; c < 4; c++) {

                if (piece.getCell(r, c) == 1) {

                    int newRow = piece.getRow() + r;
                    int newCol = piece.getCol() + c;

                    if (newRow < 0 || newRow >= ROWS ||
                        newCol < 0 || newCol >= COLS) {

                        return false;
                    }

                    if (grid[newRow][newCol] != 0) {
                        return false;
                    }
                }
            }
        }

        return true;
    }

    void lockPiece(const Tetromino& piece) {

        for (int r = 0; r < 4; r++) {
            for (int c = 0; c < 4; c++) {

                if (piece.getCell(r, c) == 1) {

                    int boardRow = piece.getRow() + r;
                    int boardCol = piece.getCol() + c;

                    if (boardRow >= 0 && boardRow < ROWS &&
                        boardCol >= 0 && boardCol < COLS) {

                        grid[boardRow][boardCol] =
                            piece.getColor() + 1;
                    }
                }
            }
        }
    }

    int clearLines() {

        int cleared = 0;
        int writeRow = ROWS - 1;

        for (int r = ROWS - 1; r >= 0; r--) {

            bool full = true;

            for (int c = 0; c < COLS; c++) {

                if (grid[r][c] == 0) {
                    full = false;
                    break;
                }
            }

            if (full) {
                cleared++;
            }
            else {

                for (int c = 0; c < COLS; c++) {
                    grid[writeRow][c] = grid[r][c];
                }

                writeRow--;
            }
        }

        while (writeRow >= 0) {

            for (int c = 0; c < COLS; c++) {
                grid[writeRow][c] = 0;
            }

            writeRow--;
        }

        return cleared;
    }

    void draw(sf::RenderWindow& window) const {

        for (int r = 0; r < ROWS; r++) {
            for (int c = 0; c < COLS; c++) {

                if (grid[r][c] != 0) {

                    sf::RectangleShape cell(
                        sf::Vector2f(CELL_SIZE - 1, CELL_SIZE - 1)
                    );

                    cell.setPosition({
                        100.0f + c * CELL_SIZE,
                        30.0f + r * CELL_SIZE
                    });

                    cell.setFillColor(getColor(grid[r][c] - 1));

                    window.draw(cell);
                }
            }
        }
    }

};

class Game {

private:

    sf::RenderWindow window;

    Board board;
    Tetromino currentPiece;

    int score = 0;
    int level = 1;

    float fallDelay = 0.6f;

    bool gameOver = false;
    bool levelChanged = false;

    sf::Clock fallClock;
    sf::Clock levelClock;

    void spawnPiece() {

        int randomType = rand() % 7;

        currentPiece.setType(randomType);

        if (!board.canPlace(currentPiece)) {
            gameOver = true;
        }
    }

    void updateLevel() {

        int newLevel = score / 500 + 1;

        if (newLevel > 6) {
            newLevel = 6;
        }

        if (newLevel > level) {

            level = newLevel;

            fallDelay = 0.6f - (level - 1) * 0.08f;

            if (fallDelay < 0.12f) {
                fallDelay = 0.12f;
            }

            levelChanged = true;
            levelClock.restart();
        }
    }

    void updateWindowTitle() {

        string title = "Tetris | Score: " +
                       to_string(score) +
                       " | Level: " +
                       to_string(level);

        if (gameOver) {
            title = "GAME OVER | Final Score: " +
                    to_string(score);
        }
        else if (levelChanged &&
                 levelClock.getElapsedTime().asSeconds() < 1.5f) {

            title += " | LEVEL UP!";
        }
        else {
            levelChanged = false;
        }

        window.setTitle(title);
    }

    void lockCurrentPiece() {

        board.lockPiece(currentPiece);

        int lines = board.clearLines();

        score += lines * 100;

        updateLevel();

        spawnPiece();
    }

    void moveDown() {

        currentPiece.move(1, 0);

        if (!board.canPlace(currentPiece)) {

            currentPiece.move(-1, 0);

            lockCurrentPiece();
        }
    }

    void moveHorizontal(int direction) {

        currentPiece.move(0, direction);

        if (!board.canPlace(currentPiece)) {
            currentPiece.move(0, -direction);
        }
    }

    void rotatePiece() {

        currentPiece.rotate();

        if (!board.canPlace(currentPiece)) {

            for (int i = 0; i < 3; i++) {
                currentPiece.rotate();
            }
        }
    }

    void hardDrop() {

        while (true) {

            currentPiece.move(1, 0);

            if (!board.canPlace(currentPiece)) {

                currentPiece.move(-1, 0);
                break;
            }
        }

        lockCurrentPiece();
    }

    void handleEvents() {

        while (auto event = window.pollEvent()) {

            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (auto* key =
                event->getIf<sf::Event::KeyPressed>()) {

                if (gameOver) {
                    continue;
                }

                switch (key->code) {

                    case sf::Keyboard::Key::Left:
                        moveHorizontal(-1);
                        break;

                    case sf::Keyboard::Key::Right:
                        moveHorizontal(1);
                        break;

                    case sf::Keyboard::Key::Up:
                        rotatePiece();
                        break;

                    case sf::Keyboard::Key::Space:
                        hardDrop();
                        break;

                    default:
                        break;
                }
            }
        }
    }

    void update() {

        if (gameOver) {
            return;
        }

        float currentDelay = fallDelay;

        if (sf::Keyboard::isKeyPressed(
                sf::Keyboard::Key::Down)) {

            currentDelay = 0.05f;
        }

        if (fallClock.getElapsedTime().asSeconds()
            >= currentDelay) {

            moveDown();

            fallClock.restart();
        }
    }

    void drawPiece() {

        for (int r = 0; r < 4; r++) {
            for (int c = 0; c < 4; c++) {

                if (currentPiece.getCell(r, c) == 1) {

                    sf::RectangleShape cell(
                        sf::Vector2f(CELL_SIZE - 1, CELL_SIZE - 1)
                    );

                    int x = currentPiece.getCol() + c;
                    int y = currentPiece.getRow() + r;

                    cell.setPosition({
                        100.0f + x * CELL_SIZE,
                        30.0f + y * CELL_SIZE
                    });

                    cell.setFillColor(
                        getColor(currentPiece.getColor())
                    );

                    window.draw(cell);
                }
            }
        }
    }

    void drawGrid() {

        sf::RectangleShape line;

        line.setFillColor(sf::Color(70, 70, 85));

        for (int r = 0; r <= ROWS; r++) {

            line.setSize({
                static_cast<float>(COLS * CELL_SIZE),
                1.0f
            });

            line.setPosition({
                100.0f,
                30.0f + r * CELL_SIZE
            });

            window.draw(line);
        }

        for (int c = 0; c <= COLS; c++) {

            line.setSize({
                1.0f,
                static_cast<float>(ROWS * CELL_SIZE)
            });

            line.setPosition({
                100.0f + c * CELL_SIZE,
                30.0f
            });

            window.draw(line);
        }
    }

public:

    Game() :
        window(
            sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
            "Tetris"
        ) {

        window.setFramerateLimit(60);

        srand(static_cast<unsigned int>(time(nullptr)));

        spawnPiece();
    }

    void run() {

        while (window.isOpen()) {

            handleEvents();

            update();

            updateWindowTitle();

            window.clear(getBackground(level));

            board.draw(window);

            drawPiece();

            drawGrid();

            window.display();
        }
    }

};

int main() {

    Game game;

    game.run();

    return 0;
}

