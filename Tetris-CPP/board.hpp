#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

namespace board {
	class Board {
	public:
		vector<RectangleShape> buildBoard(Vector2i& boardSize, sf::Color color = sf::Color::Cyan, const bool useSpace = false, float spaceSice = 1, float pieceSize = 20, const Vector2f& position = Vector2f(0, 0)) {
			std::vector<RectangleShape>* board = new std::vector<RectangleShape>();
			try
			{
				spaceSice = (useSpace) ? spaceSice : 0;
				for (int i = 0; i < boardSize.x; i++) {
					RectangleShape verticalLine(Vector2f(1, pieceSize * boardSize.y));
					verticalLine.setPosition(position.x + (i * (pieceSize + 0 * spaceSice)), position.y);
					verticalLine.setFillColor(color);
					(*board).push_back(verticalLine);
				}

				for (int j = 0; j <= boardSize.y; j++) {
					RectangleShape horizontalLine(Vector2f(pieceSize * boardSize.x, 1));
					horizontalLine.setPosition(position.x, position.y + (j * (pieceSize + 0 * spaceSice)));
					horizontalLine.setFillColor(color);
					(*board).push_back(horizontalLine);
				}

				bottomLine = board->at(board->size()-2);
			}
			catch (const std::exception&)
			{

			}
			return *board;

		}

		static void drawBoard(RenderWindow& gameWindow, std::vector<RectangleShape>& board) {
			for (RectangleShape& shape : board) {
				gameWindow.draw(shape);
			}
		}

		bool hasReachedBottom(pieces::Piece piece) {

			for (RectangleShape& shape : piece.blocks) {
				if (shape.getGlobalBounds().intersects(bottomLine.getGlobalBounds()))
					return true;
			}

			return false;
		}

	private:
		RectangleShape bottomLine;


	};
}