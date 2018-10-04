/* ----------------------------------------------------------
** The board is the grid game object
** which the snake is drawn on top of.
** ---------------------------------------------------------*/
#pragma once

#include "Graphics.h"
#include "Location.h"


class Board
{
public:
	Board(Graphics& gfx);

	void DrawCell(const Location& loc, Color c);

	int GetGridHeight() const;
	int GetGridWidth() const;

	void DrawBorder();

	// For when checking if snake collided with the
	// grid board edges
	bool IsInsideBoard(const Location& loc) const;

private:
	// Offset
	static constexpr int offSet = 20;

	// Dimention of the cells on the board
	// Cells will be 20x20 each
	static constexpr int dimention = 10;

	// Width and Height of the entire 
	// playing field/grid
	static constexpr int width = 50;
	static constexpr int height = 50;

	static constexpr int borderWidth = 4;
	static constexpr int borderPadding = 2;

	// Creates a padding of a pixel wide between
	// each cell on board
	static constexpr int cellPadding = 1;

	static constexpr int x = 30;
	static constexpr int y = 30;

	static constexpr Color borderColor = Colors::LightGray;

	// cache of the Graphics object
	Graphics& gfx;
};