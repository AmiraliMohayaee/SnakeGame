#include "Goal.h"


Goal::Goal(std::mt19937 & rng, const Board & brd, const Snake & snake)
{
	Respawn(rng, brd, snake);
}

void Goal::Draw(Board & brd) const
{
	brd.DrawCell(m_location, m_color);
}

void Goal::Respawn(std::mt19937 & rng, 
	const Board & brd, const Snake & snake)
{
	// Random seeding 
	std::uniform_int_distribution<int> xDist
		(0, brd.GetGridWidth() - 1);
	std::uniform_int_distribution<int> yDist
		(0, brd.GetGridHeight() - 1);

	Location newLoc;	// Not const since constantly changing

	// While the snake occupies the location of the tile
	// the goal generated, the goal will continue to 
	// regenerate to create new random locations
	do 
	{
		newLoc.x = xDist(rng);
		newLoc.y = yDist(rng);
	} 
	while (snake.IsInTile(newLoc));

	m_location = newLoc;
}

const Location & Goal::GetLocation() const
{
	return m_location;
}