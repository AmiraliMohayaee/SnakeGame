#include "Board.h"
#include <assert.h>


Board::Board(Graphics & gfx)
	:gfx(gfx)
{

}


void Board::DrawCell(const Location & loc, Color c)
{
	assert(loc.x >= 0);
	assert(loc.x < width);
	assert(loc.y >= 0);
	assert(loc.y < height);

	// Setting the offset by starting pos
	const int off_x = x + borderWidth + borderPadding; 
	const int off_y = y + borderWidth + borderPadding;

	gfx.DrawRectDim(loc.x * dimention + off_x + cellPadding, 
		loc.y * dimention + off_y + cellPadding, 
		dimention - cellPadding * 2, 
		dimention - cellPadding * 2,
		c);
}

int Board::GetGridHeight() const
{
	return height;
}

int Board::GetGridWidth() const
{
	return width;
}

void Board::DrawBorder()
{
	// The four dimentions surrounding the playing area
	const int top = y;
	const int left = x;

	const int bottom = top + (borderWidth + borderPadding)
		* 2 + height * dimention;
	const int right = left + (borderWidth + borderPadding)
		* 2 + width * dimention;

	// The four rectangles making up the borders
	// Top
	gfx.DrawRect(left, top, right, top + borderWidth, borderColor);

	// Left
	gfx.DrawRect(left, top + borderWidth, left + borderWidth,
		bottom - borderWidth, borderColor);

	// Right
	gfx.DrawRect(right - borderWidth, top + borderWidth,
		right, bottom - borderWidth, borderColor);

	// Bottom
	gfx.DrawRect(left, bottom - borderWidth, right,
		bottom, borderColor);
}

bool Board::IsInsideBoard(const Location & loc) const
{
	return loc.x >= 0 && loc.x < width &&
		loc.y >= 0 && loc.y < height;
}