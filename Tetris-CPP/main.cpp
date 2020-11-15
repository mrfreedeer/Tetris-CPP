#include <SFML/Graphics.hpp>
#include "pieces.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(500, 500), "Tetris");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    pieces::TPiece test (sf::Vector2f(50, 50), enums::Orientation::up);
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
             /*   bool pressed = event.KeyPressed== sf::Keyboard::Space;
                auto x = event.KeyPressed;
                auto y = event.KeyReleased;
                auto z = sf::Keyboard::Space;
                cout << pressed<<endl;*/
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