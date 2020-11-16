#ifndef PIECES_H
#define PIECES_H 
#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>


using namespace sf;
using namespace std;

namespace pieces {
	class Piece
	{
	public:
		
		/// <summary>
		/// Name of the piece, for debugging purposes
		/// </summary>
		const char* name;

		/// <summary>
		/// Size of the piece, in pixels. Default: 20
		/// </summary>
		float pieceSize;

		float spaceSize;

		/// <summary>
		/// Array where each rectangle of the piece is stored
		/// </summary>
		RectangleShape blocks[4];


		RectangleShape* begin() { return &blocks[0];  }
		RectangleShape* end() { return &blocks[3]; }

		Piece(const char* name, float pieceSize = 20, bool useSpace = false) :name{ name }, pieceSize{ pieceSize }, spaceSize{ 1 }
		{
			spaceSize = (useSpace) ? spaceSize : 0;
		}
		~Piece()
		{

		}

		/// <summary>
		/// Draws each rectangle stored in the RectangleShape blocks Array
		/// </summary>
		/// <param name="gameWindow"> Window where the game is drawn </param>
		const void draw(RenderWindow& gameWindow) {
			for (RectangleShape& shape : blocks)
			{
				gameWindow.draw(shape);
			}
		}

		/// <summary>
		/// Fills Color of every rectangle of the piece
		/// </summary>
		/// <param name="color"> Colors to be filled into the pieces' rectangles </param>
		/// <returns></returns>
		const void setFillColor(const sf::Color color) {
			for (RectangleShape& shape : blocks)
			{
				shape.setFillColor(color);
			}
		}

		const void rotate(const float angle, Vector2f* center = nullptr) {
			center = (center == nullptr) ? this->pieceCenter : center;
			Transform t;
			t.rotate(angle, *center);

			for (RectangleShape& shape : blocks) {
				shape.setPosition(t.transformPoint(shape.getPosition()));
			}
		}

		const void controlledRotate(float angle, Vector2f* center = nullptr) {
			center = (center == nullptr) ? this->pieceCenter : center;
			Transform t;

			if (rotation == 0) {
				angle = rotation = 90;
			}
			else {
				angle = -90;
				rotation = 0;
			}
			t.rotate(angle, *center);

			for (RectangleShape& shape : blocks) {
				shape.setPosition(t.transformPoint(shape.getPosition()));
			}
		}

		const void fall() {
			for (RectangleShape& shape : blocks) {
				const Vector2f currentPosition = shape.getPosition();
				Vector2f newPosition = { currentPosition.x, currentPosition.y + pieceSize };
				shape.setPosition(newPosition);
			}
			this->pieceCenter->y += 20;
		}

		const void move(sf::Keyboard::Key direction) {
			
			float movement = 0;
			switch (direction)
			{
			case sf::Keyboard::Right:
				movement += pieceSize;
				break;
			case sf::Keyboard::Left:
				movement -= pieceSize;
				break;
			default:
				break;
			}

			for (RectangleShape& shape : blocks) {
				const Vector2f previousPosition = shape.getPosition();
				Vector2f newPosition(previousPosition.x + movement, previousPosition.y);
				shape.setPosition(newPosition);
			}

			this->pieceCenter->x += movement;

		}

		const bool isTouching(Piece otherPiece) {
			Piece touchingBottom = otherPiece;
			touchingBottom.fall();

			for (int i = 0; i < 4; i++) {
				for (RectangleShape& shape : touchingBottom) {
					if (shape.getGlobalBounds().intersects(this->blocks[i].getGlobalBounds()))
						return true;
				}
			}

			Piece* touchingTop = new Piece(*this);

			touchingTop->fall();
			for (int i = 0; i < 4; i++) {
				for (RectangleShape& shape : otherPiece) {
					if (shape.getGlobalBounds().intersects(touchingTop->blocks[i].getGlobalBounds()))
						return true;
				}
			}

			return false;

		}

	protected:
		Vector2f* pieceCenter;
		float rotation;

	};


	class TPiece : public Piece {
	public:
		TPiece(Vector2<float> position, const float size = 20, const char* name = "Tpiece", const bool useSpace = false) : Piece{ name, size, useSpace } {
			try
			{
				for (int i = 0; i < 3; i++) {
					blocks[i] = RectangleShape(Vector2f(size, size));
					blocks[i].setPosition(position.x + (size + spaceSize) * i, position.y);
				}
				blocks[3] = RectangleShape(Vector2f(size, size));
				blocks[3].setPosition(position.x + (size + spaceSize), position.y + (size + spaceSize));
				this->pieceCenter = new Vector2f(position.x + (size + spaceSize), position.y);
			}
			catch (const std::exception& ex)
			{
				cout << "Error initializing: " << name << ": " << ex.what() << endl;
			}
		}

	};

	class LPiece : public Piece {
	public:
		LPiece(Vector2<float> position, const float size = 20, const char* name = "Lpiece", const bool useSpace = false) : Piece{ name, size, useSpace } {
			try
			{
				for (int i = 0; i < 3; i++) {
					blocks[i] = RectangleShape(Vector2f(size, size));
					blocks[i].setPosition(position.x, position.y + (size + spaceSize) * i);
				}
				blocks[3] = RectangleShape(Vector2f(size, size));
				blocks[3].setPosition(position.x + (size + spaceSize), position.y + (size + spaceSize) * 2);
				this->pieceCenter = new Vector2f(position.x, position.y + (size + spaceSize) * 1);
			}
			catch (const std::exception& ex)
			{
				cout << "Error initializing: " << name << ": " << ex.what() << endl;
			}
		}
	};

	class JPiece : public Piece {
	public:
		JPiece(Vector2<float> position, const float size = 20, const char* name = "Jpiece", const bool useSpace = false) : Piece{ name, size, useSpace } {
			try
			{
				for (int i = 0; i < 3; i++) {
					blocks[i] = RectangleShape(Vector2f(size, size));
					blocks[i].setPosition(position.x, position.y + (size + spaceSize) * i);
				}
				blocks[3] = RectangleShape(Vector2f(size, size));
				blocks[3].setPosition(position.x - (size + spaceSize), position.y + (size + spaceSize) * 2);
				this->pieceCenter = new Vector2f(position.x, position.y + (size + spaceSize) * 1);
			}
			catch (const std::exception& ex)
			{
				cout << "Error initializing: " << name << ": " << ex.what() << endl;
			}
		}
	};

	class OPiece : public Piece {
	public:
		OPiece(Vector2<float> position, const float size = 20, const char* name = "OPiece", const bool useSpace = false) : Piece{ name, pieceSize, useSpace } {
			try
			{
				for (int i = 0; i < 2; i++) {
					blocks[i] = RectangleShape(Vector2f(size, size));
					blocks[i].setPosition(position.x, position.y + (size + spaceSize) * i);
				}
				for (int i = 2; i < 4; i++) {
					blocks[i] = RectangleShape(Vector2f(size, size));
					blocks[i].setPosition(position.x + (size + spaceSize), position.y + (size + spaceSize) * (i % 2));
				}


			}
			catch (const std::exception& ex)
			{
				cout << "Error initializing: " << name << ": " << ex.what() << endl;
			}
		}

		const void rotate(float angle) {
			;
		}
	};

	class IPiece : public Piece {
	public:
		IPiece(Vector2<float> position, const float size = 20, const char* name = "IPiece", const bool useSpace = false) : Piece{ name, pieceSize, useSpace } {
			try
			{
				for (int i = 0; i < 4; i++) {
					blocks[i] = RectangleShape(Vector2f(size, size));
					blocks[i].setPosition(position.x, position.y + (size + spaceSize) * i);
				}
				this->pieceCenter = new Vector2f(position.x, position.y + (size + spaceSize) * 2);
				rotation = 0;
			}
			catch (const std::exception& ex)
			{
				cout << "Error initializing: " << name << ": " << ex.what() << endl;
			}
		}

		const void rotate(float angle, Vector2f* center = nullptr) {
			controlledRotate(angle, center);
		}

	
	};

	class SPiece : public Piece {
	public:
		SPiece(Vector2<float> position, const float size = 20, const char* name = "SPiece", const bool useSpace = false) : Piece{ name, pieceSize, useSpace } {
			try
			{
				for (int i = 0; i < 2; i++) {
					blocks[i] = RectangleShape(Vector2f(size, size));
					blocks[i].setPosition(position.x + (size + spaceSize) * i, position.y);
				}

				for (int i = 2; i < 4; i++) {
					blocks[i] = RectangleShape(Vector2f(size, size));
					blocks[i].setPosition(position.x + (size + spaceSize) * (i - 1), position.y - (size + spaceSize));
				}

				this->pieceCenter = new Vector2f(position.x + (size + spaceSize), position.y);
				rotation = 0;
			}
			catch (const std::exception& ex)
			{
				cout << "Error initializing: " << name << ": " << ex.what() << endl;
			}
		}

		const void rotate(float angle, Vector2f* center = nullptr) {
			controlledRotate(angle, center);
		}

	};

	class ZPiece : public Piece {
	public:
		ZPiece(Vector2<float> position, const float size = 20, const char* name = "ZPiece", const bool useSpace = false) : Piece{ name, pieceSize, useSpace } {
			try
			{
				for (int i = 0; i < 2; i++) {
					blocks[i] = RectangleShape(Vector2f(size, size));
					blocks[i].setPosition(position.x + (size + spaceSize) * i, position.y);
				}

				for (int i = 2; i < 4; i++) {
					blocks[i] = RectangleShape(Vector2f(size, size));
					blocks[i].setPosition(position.x + (size + spaceSize) * (i - 1), position.y + (size + spaceSize));
				}

				this->pieceCenter = new Vector2f(position.x + (size + spaceSize), position.y);
			}
			catch (const std::exception& ex)
			{
				cout << "Error initializing: " << name << ": " << ex.what() << endl;
			}
		}
		const void rotate(float angle, Vector2f* center = nullptr) {
			controlledRotate(angle, center);
		}
	};

}

#endif