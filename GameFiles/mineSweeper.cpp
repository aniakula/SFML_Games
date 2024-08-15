#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <string>

const int gridSize = 10;
const int mineCount = 15;
const int cellSize = 40;
const int windowSize = 500; 

enum State { HIDDEN, OPEN, FLAGGED };

struct Cell {
    sf::RectangleShape tile;
    sf::Text label;
    State state;
    bool isMine;
    int adjMines;

    Cell() : label(), tile(sf::Vector2f((float)windowSize/gridSize, (float)windowSize/gridSize)), state(HIDDEN), isMine(false), adjMines(0) {}
};

// 2D array of Cells
std::vector<std::vector<Cell> > grid(gridSize, std::vector<Cell>(gridSize));

void initializeGrid();
void placeTiles(sf::Font& font);
void explode(std::vector<std::vector<Cell> >& grid, int r, int c);
int main() {
    sf::Font font;
    if (!font.loadFromFile("Arial.ttf"))
        return -1;

    initializeGrid();
    placeTiles(font);

    sf::RenderWindow window(sf::VideoMode(windowSize, windowSize), "MineSweeper", sf::Style::Titlebar | sf::Style::Close);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Mouse::isButtonPressed(sf::Mouse::Right)){
            for (int i = 0; i < gridSize; i++) {
                for (int j = 0; j < gridSize; j++) {
                    Cell* t = &grid[i][j];
                    int Mx = sf::Mouse::getPosition(window).x;
                    int My = sf::Mouse::getPosition(window).y;
                    int Tx = t->tile.getPosition().x;
                    int Ty = t->tile.getPosition().y;
                    if(Mx > Tx+5 && Mx < Tx + 45 && My > Ty+5 && My < Ty + 45 && sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                        explode(grid, i, j);
                    }
                    if(Mx > Tx+5 && Mx < Tx + 45 && My > Ty+5 && My < Ty + 45 && sf::Mouse::isButtonPressed(sf::Mouse::Right) && t -> state != OPEN){
                        t->state = FLAGGED;
                    }
                }
            }
        }
        for (int i = 0; i < gridSize; i++) {
            for (int j = 0; j < gridSize; j++) {
                Cell* t = &grid[i][j];
                window.draw(t->tile);

                if(t->state == OPEN){
                    t->label.setString(std::to_string(t->adjMines));
                    t->tile.setFillColor(sf::Color::Green);
                    window.draw(t->label);
                }
                else if(t->state == FLAGGED){
                    t->tile.setFillColor(sf::Color::Red);
                }


            }
        }
        window.display();
    }

    return 0;
}

void explode(std::vector<std::vector<Cell> >& grid, int r, int c){
    if(grid[r][c].isMine || grid[r][c].state == OPEN)
        return;
    else if(grid[r][c].adjMines > 0){
        grid[r][c].state = OPEN;
        return;
    }
    else{
        grid[r][c].state = OPEN;
        if(r < gridSize-1)
        explode(grid, r+1, c);
        if(r > 0)
        explode(grid, r-1, c);
        if(c < gridSize-1)
        explode(grid, r, c+1);
        if(c > 0)
        explode(grid, r, c-1);

        return;
    }
}

void initializeGrid() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    for (int i = 0; i < mineCount; ++i) {
        int x = std::rand() % gridSize;
        int y = std::rand() % gridSize;

        if (!grid[x][y].isMine) {
            grid[x][y].isMine = true;
            grid[x][y].adjMines = 0;
            if (x > 0) {
                grid[x - 1][y].adjMines++;
                if(y > 0){
                    grid[x-1][y-1].adjMines++;
                }
                if(y < gridSize - 1){
                    grid[x-1][y+1].adjMines++;
                }
            }
            if (x < gridSize - 1){
                grid[x + 1][y].adjMines++;
                if(y > 0){
                    grid[x+1][y-1].adjMines++;
                }
                if(y < gridSize - 1){
                    grid[x+1][y+1].adjMines++;
                }
            } 
            if (y > 0) grid[x][y - 1].adjMines++;
            if (y < gridSize - 1) grid[x][y + 1].adjMines++;
        } else {
            --i;  // Repeat this loop iteration if a mine already exists
        }
    }
}

void placeTiles(sf::Font& font) {
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            grid[i][j].tile.setPosition(j * 50.f, i * 50.f);
            grid[i][j].tile.setFillColor(grid[i][j].isMine ? sf::Color::Red : sf::Color::Blue);
            grid[i][j].tile.setOutlineColor(sf::Color::Black);
            grid[i][j].tile.setOutlineThickness(5.f);
            // Configure the text label for each cell
            grid[i][j].label.setFont(font);
            grid[i][j].label.setCharacterSize(30);
            grid[i][j].label.setFillColor(sf::Color::White);
            grid[i][j].label.setPosition(j * 50.f + 15.f, i * 50.f + 5.f);  // Adjust position for better centering
        }
    }
}
