/* ----------------------------------------------------------
** The Snake object and the individual segments which also 
** count and seperate objects. These segments render seperately
** and are stored in the container for the snake segements
** ---------------------------------------------------------*/
#pragma once

#include "Board.h"


class Snake
{
private:
	// An instance of each snake segment
	class SnakeSegment
	{
	public:
		void InitHead(const Location& in_loc);
		void InitBody(Color c_in);
		void Follow(const SnakeSegment& next);
		void MoveBy(const Location& delta_loc);
		void Draw(Board& board) const;

		// Getter for a single location in 
		// a snake segment
		const Location& GetLocation() const;

	private:
		Location m_loc;
		Color m_color;
	};

public:
	Snake(const Location& loc);
	
	void Draw(Board& board) const;

	// Sets the next positions for the snake
	// elements to move 
	void MoveBy(const Location& delta_loc);
	void Grow();

	Location GetNextHeadLocation(const Location& deltaLoc) const;

	bool IsInTileExceptEnd(const Location& selfLoc) const;
	bool IsInTile(const Location& selfLoc) const;

private:
	static constexpr Color headColor = Colors::Yellow;
	static constexpr Color bodyColor = Colors::Green;

	// Contaner for the snake segments on screen
	static constexpr int nSegmentsMax = 100;
	SnakeSegment segments[nSegmentsMax];
	int nSegments = 1;	// Starting initial number of segs
}; 