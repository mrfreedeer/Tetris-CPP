#pragma once
#include <SFML/Graphics.hpp>
#include "Enums.cpp";
using namespace sf;
using namespace enums;
int pieceSize = 20;
namespace pieces {
	class Piece
	{
	public:
		Piece(const char* name):name{name}
		{
			
		}
		~Piece()
		{
		}
		const char* name;
		RectangleShape blocks [4];

	private:

	};


	class TPiece:Piece {
	public:
		TPiece(Vector2<int> position, enums::Orientation o, int size=pieceSize,const char* name="Tpiece") : Piece{ name } {
			switch (o)
			{
			case right:
			case left:
				for (int i = 0; i < 3; i++) {
					blocks[i] = RectangleShape(Vector2f(size, size));
					blocks[i].setPosition(position.x, position.y + size * i);
				}
					blocks[3] = RectangleShape(Vector2f(size, size));
				if (o == left) {
					blocks[3].setPosition(position.x - size, position.y + size);
				}
				else {
					blocks[3].setPosition(position.x + size, position.y + size);
				}
				break;

			case up:
			case down:
				break;

			default:
				break;
			}
		}

	private:
		
	};





	int main() {
		const char* j = "Hello";
		TPiece test(j);

		return 0;
	}
}

