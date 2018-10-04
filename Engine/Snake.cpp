#include "Snake.h"
#include <assert.h>

void Snake::Draw(Board & board) const
{
	for (int i = 0; i < nSegments; i++)
	{
		segments[i].Draw(board);
	}
}


Snake::Snake(const Location & loc)
{
	// Array for colors in the cell array
	// circulating and changing
	constexpr int nBodyColors = 4;
	constexpr Color bodyColors[nBodyColors] =
	{
		{ 10, 100, 32 },
		{ 10, 130, 48 },
		{ 18, 160, 48 },
		{ 10, 130, 48 }
	};

	for (int i = 0; i < nSegmentsMax; ++i)
	{
		segments[i].InitBody(bodyColors[i % nBodyColors]);
	}

	// Setting inital position of the head
	// the rest of the body follows the head
	segments[0].InitHead(loc);
}


void Snake::Grow()
{
	if (nSegments < nSegmentsMax)
	{
		// No need for the call below as everything
		// is being initialized in the ctor now
		//segments[nSegments].InitBody();
		++nSegments;
	}
}

Location Snake::GetNextHeadLocation(const Location & deltaLoc) const
{
	// Creating a copy of the head location as 
	// the return value requires a Location object
	// This is used to determine if the snake head 
	// collides with the grid corners when checking
	// for collision
	Location loc(segments[0].GetLocation());

	loc.Add(deltaLoc);

	return loc;
}

bool Snake::IsInTileExceptEnd(const Location & selfLoc) const
{
	// Checking segments of the snake to check for 
	// collision with the head and a segment
	// nSegments - 1 checks all segments except the end
	// It allows for the snake to actively chase its tail 
	// without eating it
	for (int i = 0; i < nSegments - 1; ++i)
	{
		if (segments[i].GetLocation() == selfLoc)
		{
			return true;
		} 
	}
	return false;
}

// More suitable to call when doing checks against the 
// consumable goal object
bool Snake::IsInTile(const Location & selfLoc) const
{
	for (int i = 0; i < nSegments; ++i)
	{
		if (segments[i].GetLocation() == selfLoc)
		{
			return true;
		}
	}
	return false;
}


void Snake::MoveBy(const Location & delta_loc)
{
	// iterating backward from the tail/last
	// segment in the snake towards the head
	for (int i = nSegments - 1; i > 0; i--)
	{
		// Follow the segment before you
		segments[i].Follow(segments[i - 1]);
	}

	segments[0].MoveBy(delta_loc);
}

void Snake::SnakeSegment::InitHead(const Location & in_loc)
{
	m_loc = in_loc;
	m_color = Snake::headColor;
}

void Snake::SnakeSegment::InitBody(Color c_in)
{
	m_color = c_in;
}

void Snake::SnakeSegment::Follow(const SnakeSegment & next)
{
	// Sets the location of the following segment in a 
	// container
	m_loc = next.m_loc;
}

void Snake::SnakeSegment::MoveBy(const Location & delta_loc)
{
	assert(abs(delta_loc.x) + abs(delta_loc.y) == 1);
	m_loc.Add(delta_loc);
}

void Snake::SnakeSegment::Draw(Board& board) const
{
	board.DrawCell(m_loc, m_color);
}

const Location& Snake::SnakeSegment::GetLocation() const
{
	return m_loc;
}