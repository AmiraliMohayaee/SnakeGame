/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"


Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	board( gfx ),
	rng ( std::random_device()() ),
	snake({ 2, 2 }),
	goal(rng, board, snake)
{

}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if (!m_gameStart)
	{
		if (!m_gameOver)
		{
			if (wnd.kbd.KeyIsPressed(VK_UP))
			{
				m_deltaLocation = { 0, -1 };
			}
			else if (wnd.kbd.KeyIsPressed(VK_DOWN))
			{
				m_deltaLocation = { 0, 1 };
			}
			else if (wnd.kbd.KeyIsPressed(VK_LEFT))
			{
				m_deltaLocation = { -1, 0 };
			}
			else if (wnd.kbd.KeyIsPressed(VK_RIGHT))
			{
				m_deltaLocation = { 1, 0 };
			}
			//else if (wnd.kbd.KeyIsPressed(VK_ESCAPE))
			//{
			//	wnd.Kill();
			//}


			++m_snakeMoveCounter;

			// Dampening snake movement speed
			if (m_snakeMoveCounter >= m_snakeMovePerFrame)
			{
				m_snakeMoveCounter = 0;

				const Location nextHeadLocation =
					snake.GetNextHeadLocation(m_deltaLocation);

				if (!board.IsInsideBoard(nextHeadLocation) ||
					snake.IsInTileExceptEnd(nextHeadLocation))
				{
					m_gameOver = true;
				}
				else
				{
					// The goal will respawn after the snake moves 
					// because the updated position of the snake is
					// used to test the respawn pos
					const bool eating =
						nextHeadLocation == goal.GetLocation();

					if (eating)
					{
						snake.Grow();
					}

					snake.MoveBy(m_deltaLocation);

					if (eating)
					{
						goal.Respawn(rng, board, snake);
					}
				}
				// Setting up speedup counter and speed cap
				++m_snakeSpeedupCounter;
				if (m_snakeSpeedupCounter >= m_snakeSpeedupPeriod)
				{
					m_snakeSpeedupCounter = 0;
					m_snakeMovePerFrame = std::max(m_snakeMovePerFrame - 1,
						m_snakeMovePeriodMin);
				}
			}
		}
	}
	else
	{
		m_gameStart = wnd.kbd.KeyIsPressed(VK_RETURN);
	}
}

void Game::ComposeFrame()
{
	if (!m_gameStart)
	{
		snake.Draw(board);
		goal.Draw(board);
		board.DrawBorder();


		if (m_gameOver)
		{
			SpriteCodex::DrawGameOver(350, 265, gfx);
		}
	}
	else
	{
		SpriteCodex::DrawTitle(290, 225, gfx);
	}

	// Test Attempt

}



//// Random color generator
//std::uniform_int_distribution<int> colorDist(0, 255);

//// Drawing the grid
//for (int y = 0; y < board.GetGridHeight(); y++)
//{
//	for (int x = 0; x < board.GetGridWidth(); x++)
//	{
//		Location loc = { x, y };
//		Color c(colorDist(rng), colorDist(rng), colorDist(rng));
//		board.DrawCell(loc, c);
//	}
//}