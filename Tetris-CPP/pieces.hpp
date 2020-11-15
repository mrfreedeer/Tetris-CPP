#ifndef PIECES_H
#define PIECES_H 
#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Enums.cpp";


using namespace sf;
using namespace enums;
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
		
		Piece(const char* name, float pieceSize = 20, bool useSpace = true) :name{ name }, pieceSize{ pieceSize }, spaceSize{1}
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
		const void draw(RenderWindow &gameWindow) {
			for (RectangleShape &shape: blocks)
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
			center = (center == nullptr) ? this->pieceCenter: center;
			Transform t;
			t.rotate(angle, *center);
			
			for (RectangleShape& shape : blocks) {
				shape.setPosition(t.transformPoint(shape.getPosition()));
			}
		}

	protected:
		Vector2f* pieceCenter;
	};


	class TPiece : public Piece {
	public:
		TPiece(Vector2<float> position, enums::Orientation orient, const float size = 20, const char* name = "Tpiece", const bool useSpace = true) : Piece{ name, pieceSize } {
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
				cout << "Error initializing Tpiece: " << ex.what() << endl;
			}
		}

	};
}

#endif