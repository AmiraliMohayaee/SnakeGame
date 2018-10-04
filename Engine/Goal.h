#pragma once

#include "Snake.h"
#include "Board.h"
#include "Location.h"
#include <random>

class Goal
{
public:
	Goal(std::mt19937& rng, const Board& brd,
		const Snake& snake);

	void Draw(Board& brd) const;
	void Respawn(std::mt19937& rng, const Board& brd,
		const Snake& snake);

	const Location& GetLocation() const;


private:
	static constexpr Color m_color = Colors::Red;
	Location m_location;

};