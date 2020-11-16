#include <SFML/Graphics.hpp>
#include "pieces.hpp"
#include "board.hpp"


using namespace board;



int main()
{
    sf::RenderWindow window(sf::VideoMode(500, 500), "Tetris");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    pieces::TPiece test(Vector2f(60,20));
    cout << sf::Keyboard::Space<<endl<<endl;
    test.setFillColor(sf::Color::Blue);

    sf::Clock clock;
    Vector2i boardSize = { 10, 20 };

    Board board;
    std::vector<RectangleShape> boardShapes = board.buildBoard(boardSize);

    bool touched = false;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyReleased) {
                switch (event.key.code)
                {
                case sf::Keyboard::Space:
                    test.rotate(90);
                    break;
                case sf::Keyboard::Down:
                    test.fall();
                    clock.restart();
                    break;
                case sf::Keyboard::Left:
                case sf::Keyboard::Right:
                    test.move(event.key.code);
                    break;
                default:
                    break;
                }
                    
            }
         
        }

        int elapsedTime = clock.getElapsedTime().asMilliseconds();

        if (elapsedTime > 1000) {
            if(!touched)
                test.fall();
            clock.restart();
        }

        touched = board.hasReachedBottom(test);

        window.clear();
        window.draw(shape);
        
        test.draw(window);
        Board::drawBoard(window, boardShapes);
        window.display();
    }

    return 0;
}


