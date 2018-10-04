/* ----------------------------------------------------------
** This is simply the translator between the grid-based loacion
** system and the coord-based location system of the renderer
** ---------------------------------------------------------*/

#pragma once


class Location
{
public:
	void Add(const Location& val)
	{
		x += val.x;
		y += val.y;
	}

	bool operator==(const Location& rhs) const
	{
		return x == rhs.x && y == rhs.y;
	}

	int x;
	int y;
};