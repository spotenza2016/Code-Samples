#include "Commands.h"
void Commands::StartGame() {
    int columns;
    int rows;
    int mines;
    ifstream file("boards/config.cfg");
    file >> columns;
    file >> rows;
    file >> mines;
    file.close();

    Board* board = new Board(columns, rows, mines);
    delete board;
}

void Commands::Milestone1() {
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
}
