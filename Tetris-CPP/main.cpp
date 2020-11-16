#include <SFML/Graphics.hpp>
#include "pieces.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(500, 500), "Tetris");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    pieces::SPiece test (sf::Vector2f(50, 50));
    cout << sf::Keyboard::Space<<endl<<endl;
    test.setFillColor(sf::Color::Blue);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyReleased) {
                 if(event.key.code == sf::Keyboard::Space)
                    test.rotate(90);   
            }
         
        }

        window.clear();
        window.draw(shape);
        test.draw(window);
        window.display();
    }

    return 0;
}