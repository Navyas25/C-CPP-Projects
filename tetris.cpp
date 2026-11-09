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

int board[ROWS][COLS] = {};

int shapes[7][4][4] = {

    // I
    {
        {0, 0, 0, 0},
        {1, 1, 1, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },

    // O
    {
        {1, 1, 0, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },

    // T
    {
        {0, 1, 0, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },

    // S
    {
        {0, 1, 1, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },

    // Z
    {
        {1, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },

    // J
    {
        {1, 0, 0, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },

    // L
    {
        {0, 0, 1, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    }
};

sf::Color colors[7] = {
    sf::Color::Cyan,
    sf::Color::Yellow,
    sf::Color(180, 70, 255),
    sf::Color::Green,
    sf::Color::Red,
    sf::Color::Blue,
    sf::Color(255, 140, 0)
};

// Background colours for each level
sf::Color backgrounds[6] = {
    sf::Color(15, 15, 35),
    sf::Color(35, 15, 45),
    sf::Color(15, 35, 45),
    sf::Color(45, 20, 20),
    sf::Color(35, 30, 15),
    sf::Color(20, 15, 45)
};

int currentShape;
int currentMatrix[4][4];

int shapeRow;
int shapeCol;

int score = 0;
int level = 1;

float fallDelay = 0.6f;

bool gameOver = false;
bool levelChanged = false;

sf::Clock levelEffectClock;

// --------------------------------------------------
// COLLISION DETECTION
// --------------------------------------------------

bool canPlace(int newRow, int newCol, int matrix[4][4]) {

    for (int row = 0; row < 4; row++) {

        for (int col = 0; col < 4; col++) {

            if (matrix[row][col] == 1) {

                int boardRow = newRow + row;
                int boardCol = newCol + col;

                if (boardRow < 0 || boardRow >= ROWS ||
                    boardCol < 0 || boardCol >= COLS) {
                    return false;
                }

                if (board[boardRow][boardCol] != 0) {
                    return false;
                }
            }
        }
    }

    return true;
}

// --------------------------------------------------
// SPAWN SHAPE
// --------------------------------------------------

void spawnShape() {

    currentShape = rand() % 7;

    for (int row = 0; row < 4; row++) {

        for (int col = 0; col < 4; col++) {

            currentMatrix[row][col] = shapes[currentShape][row][col];
        }
    }

    shapeRow = 0;
    shapeCol = 3;

    if (!canPlace(shapeRow, shapeCol, currentMatrix)) {
        gameOver = true;
    }
}

// --------------------------------------------------
// UPDATE LEVEL
// --------------------------------------------------

void updateLevel() {

    int newLevel = (score / 500) + 1;

    if (newLevel > 6) {
        newLevel = 6;
    }

    if (newLevel != level) {

        level = newLevel;

        fallDelay = 0.6f - (level - 1) * 0.08f;

        if (fallDelay < 0.12f) {
            fallDelay = 0.12f;
        }

        levelChanged = true;
        levelEffectClock.restart();
    }
}

// --------------------------------------------------
// LOCK SHAPE
// --------------------------------------------------

void lockShape() {

    for (int row = 0; row < 4; row++) {

        for (int col = 0; col < 4; col++) {

            if (currentMatrix[row][col] == 1) {

                int boardRow = shapeRow + row;
                int boardCol = shapeCol + col;

                if (boardRow >= 0 && boardRow < ROWS &&
                    boardCol >= 0 && boardCol < COLS) {

                    board[boardRow][boardCol] = currentShape + 1;
                }
            }
        }
    }
}

// --------------------------------------------------
// CLEAR LINES
// --------------------------------------------------

void clearLines() {

    for (int row = ROWS - 1; row >= 0; row--) {

        bool fullLine = true;

        for (int col = 0; col < COLS; col++) {

            if (board[row][col] == 0) {
                fullLine = false;
                break;
            }
        }

        if (fullLine) {

            score += 100;

            for (int moveRow = row; moveRow > 0; moveRow--) {

                for (int col = 0; col < COLS; col++) {

                    board[moveRow][col] = board[moveRow - 1][col];
                }
            }

            for (int col = 0; col < COLS; col++) {
                board[0][col] = 0;
            }

            updateLevel();

            row++;
        }
    }
}

// --------------------------------------------------
// MOVE DOWN
// --------------------------------------------------

void moveDown() {

    if (canPlace(shapeRow + 1, shapeCol, currentMatrix)) {

        shapeRow++;
    }
    else {

        lockShape();
        clearLines();
        spawnShape();
    }
}

// --------------------------------------------------
// ROTATE SHAPE
// --------------------------------------------------

void rotateShape() {

    int rotated[4][4] = {};

    for (int row = 0; row < 4; row++) {

        for (int col = 0; col < 4; col++) {

            rotated[col][3 - row] = currentMatrix[row][col];
        }
    }

    if (canPlace(shapeRow, shapeCol, rotated)) {

        for (int row = 0; row < 4; row++) {

            for (int col = 0; col < 4; col++) {

                currentMatrix[row][col] = rotated[row][col];
            }
        }
    }
}

// --------------------------------------------------
// DRAW CELL
// --------------------------------------------------

void drawCell(sf::RenderWindow& window, int row, int col, sf::Color color) {

    sf::RectangleShape cell(sf::Vector2f(
        CELL_SIZE - 1,
        CELL_SIZE - 1
    ));

    cell.setPosition(sf::Vector2f(
        100 + col * CELL_SIZE,
        20 + row * CELL_SIZE
    ));

    cell.setFillColor(color);

    window.draw(cell);
}

// --------------------------------------------------
// DRAW BOARD
// --------------------------------------------------

void drawBoard(sf::RenderWindow& window) {

    // Draw settled blocks
    for (int row = 0; row < ROWS; row++) {

        for (int col = 0; col < COLS; col++) {

            if (board[row][col] != 0) {

                drawCell(
                    window,
                    row,
                    col,
                    colors[board[row][col] - 1]
                );
            }
        }
    }

    // Draw current falling shape
    for (int row = 0; row < 4; row++) {

        for (int col = 0; col < 4; col++) {

            if (currentMatrix[row][col] == 1) {

                drawCell(
                    window,
                    shapeRow + row,
                    shapeCol + col,
                    colors[currentShape]
                );
            }
        }
    }

    // Draw border
    sf::RectangleShape border(
        sf::Vector2f(COLS * CELL_SIZE, ROWS * CELL_SIZE)
    );

    border.setPosition(sf::Vector2f(100, 20));
    border.setFillColor(sf::Color::Transparent);
    border.setOutlineColor(sf::Color::White);
    border.setOutlineThickness(2);

    window.draw(border);
}

// --------------------------------------------------
// DRAW GRID
// --------------------------------------------------

void drawGrid(sf::RenderWindow& window) {

    sf::RectangleShape line;

    line.setFillColor(sf::Color(55, 55, 65));

    // Vertical lines
    for (int col = 0; col <= COLS; col++) {

        line.setSize(sf::Vector2f(1, ROWS * CELL_SIZE));

        line.setPosition(sf::Vector2f(
            100 + col * CELL_SIZE,
            20
        ));

        window.draw(line);
    }

    // Horizontal lines
    for (int row = 0; row <= ROWS; row++) {

        line.setSize(sf::Vector2f(COLS * CELL_SIZE, 1));

        line.setPosition(sf::Vector2f(
            100,
            20 + row * CELL_SIZE
        ));

        window.draw(line);
    }
}

// --------------------------------------------------
// UPDATE WINDOW TITLE
// --------------------------------------------------

void updateWindowTitle(sf::RenderWindow& window) {

    string title = "TETRIS | Score: " + to_string(score) +
                   " | Level: " + to_string(level);

    if (levelChanged) {

        if (levelEffectClock.getElapsedTime().asSeconds() < 1.5f) {
            title += " | LEVEL UP!";
        }
        else {
            levelChanged = false;
        }
    }

    if (gameOver) {
        title = "GAME OVER | Final Score: " + to_string(score) +
                " | Level: " + to_string(level);
    }

    window.setTitle(title);
}

// --------------------------------------------------
// MAIN
// --------------------------------------------------

int main() {

    srand(static_cast<unsigned int>(time(nullptr)));

    sf::RenderWindow window(
        sf::VideoMode(sf::Vector2u(WINDOW_WIDTH, WINDOW_HEIGHT)),
        "TETRIS - PROGRESSIVE DIFFICULTY"
    );

    window.setFramerateLimit(60);

    spawnShape();

    sf::Clock clock;

    float fallTimer = 0;

    while (window.isOpen()) {

        // Handle events
        while (auto event = window.pollEvent()) {

            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {

                if (!gameOver) {

                    if (key->code == sf::Keyboard::Key::Left) {

                        if (canPlace(shapeRow, shapeCol - 1, currentMatrix)) {
                            shapeCol--;
                        }
                    }

                    else if (key->code == sf::Keyboard::Key::Right) {

                        if (canPlace(shapeRow, shapeCol + 1, currentMatrix)) {
                            shapeCol++;
                        }
                    }

                    else if (key->code == sf::Keyboard::Key::Up) {

                        rotateShape();
                    }

                    else if (key->code == sf::Keyboard::Key::Space) {

                        while (canPlace(shapeRow + 1, shapeCol, currentMatrix)) {
                            shapeRow++;
                        }

                        moveDown();
                    }
                }
            }
        }

        float deltaTime = clock.restart().asSeconds();

        if (!gameOver) {

            fallTimer += deltaTime;

            if (fallTimer >= fallDelay) {

                moveDown();
                fallTimer = 0;
            }

            // Faster falling with down arrow
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {

                if (fallTimer >= 0.05f) {

                    moveDown();
                    fallTimer = 0;
                }
            }
        }

        // Update title
        updateWindowTitle(window);

        // Change background according to level
        window.clear(backgrounds[level - 1]);

        drawGrid(window);
        drawBoard(window);

        window.display();
    }

    return 0;
}
