#include <SFML/Graphics.hpp>
#include "pieces.hpp"
#include "board.hpp"
#include <time.h>

using namespace board;



int main()
{
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(500, 500), "Tetris");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    std::vector<pieces::Piece> allpieces;
    pieces::TPiece test(Vector2f(60,20));
    cout << sf::Keyboard::Space<<endl<<endl;
    test.setFillColor(sf::Color::Blue);

    pieces::Piece* activePiece = &test;

    sf::Color colors[6] = {Color::Blue, Color::Cyan, Color::Magenta, Color::Green, Color::Red };

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
                     activePiece->rotate(90);
                    break;
                case sf::Keyboard::Down:
                    activePiece->fall();
                    clock.restart();
                    break;
                case sf::Keyboard::Left:
                case sf::Keyboard::Right:
                    activePiece->move(event.key.code);
                    break;
                default:
                    break;
                }
                    
            }
         
        }

        int elapsedTime = clock.getElapsedTime().asMilliseconds();

        if (elapsedTime > 1000) {
            if(!touched)
                activePiece->fall();
            clock.restart();
        }

        touched = board.hasReachedBottom(*activePiece);
        if (!touched) {
            for (pieces::Piece& p : allpieces) {
                if (activePiece->isTouching(p)) {
                    touched = true;
                    break;
                }
            }
        }

        if (touched) {
            allpieces.push_back(*activePiece);
            activePiece = nullptr;
            activePiece = new pieces::TPiece(Vector2f(0, 0));
            activePiece->setFillColor(colors[rand() % 4]);
        }
        window.clear();
        window.draw(shape);
        
        for(pieces::Piece& stoppedPiece : allpieces) {
            stoppedPiece.draw(window);
        }

        activePiece->draw(window);
        Board::drawBoard(window, boardShapes);
        window.display();
    }

    return 0;
}


