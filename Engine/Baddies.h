#pragma once

#include "Board.h"
#include "Snake.h"
#include <random>


class Baddies
{
public:
	Baddies(std::mt19937& rng, const Board& brd,
		const Snake& snake);

	void Draw(const Location& loc, Color c);
	void CollideWithSnake(const Location& loc);

	const Location& GetLocation() const;


private:
	static constexpr Color m_color = Colors::Gray;
	Location m_location;

};