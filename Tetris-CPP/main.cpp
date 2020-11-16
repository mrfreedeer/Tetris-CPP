#include <SFML/Graphics.hpp>
#include "pieces.hpp"
#include <vector>



vector<RectangleShape> buildBoard(Vector2i& boardSize, sf::Color color = sf::Color::Cyan, const bool useSpace = false, float spaceSice = 1, float pieceSize = 20, const Vector2f& position = Vector2f(0, 0)) {
    try
    {
        spaceSice = (useSpace) ? spaceSice : 0;
        std::vector<RectangleShape>* board = new std::vector<RectangleShape>();
        for (int i = 0; i < boardSize.x; i++) {
            RectangleShape verticalLine(Vector2f(1, pieceSize * boardSize.y));
            verticalLine.setPosition(position.x + (i * (pieceSize + 0*spaceSice)), position.y);
            verticalLine.setFillColor(color);
            (*board).push_back(verticalLine);
        }

        for (int j = 0; j < boardSize.y; j++) {
            RectangleShape horizontalLine(Vector2f(pieceSize * boardSize.x, 1));
            horizontalLine.setPosition(position.x, position.y + (j * (pieceSize + 0*spaceSice)));
            horizontalLine.setFillColor(color);
            (*board).push_back(horizontalLine);
        }

        return *board;
    }
    catch (const std::exception&)
    {

    }
}

void drawBoard(RenderWindow& gameWindow, std::vector<RectangleShape>& board) {
    for (RectangleShape& shape : board) {
        gameWindow.draw(shape);
    }
}



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

    std::vector<RectangleShape> board = buildBoard(boardSize);

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
             test.fall();
            clock.restart();
        }

        window.clear();
        window.draw(shape);
        
        test.draw(window);
        drawBoard(window, board);
        window.display();
    }

    return 0;
}


