#include <SFML/Graphics.hpp>
#include "pieces.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(500, 500), "Tetris");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    pieces::TPiece test (sf::Vector2f(50, 50), enums::Orientation::up);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        test.draw(window);
        window.display();
    }

    return 0;
}