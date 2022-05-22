#include "Knight.h"
#include <iostream>

Knight::Knight(Team team, Position pos, SDL_BaseHandler* handler)
	:Piece(team, pos, m_handler, KNIGHT)
{
	string filename;
	if (team == BLACK)
	{
		filename = "image\\blackKnight.png";
	}
	else
	{
		filename = "image\\whiteKnight.png";
	}
	m_handler = handler;
	m_texture = handler->loadImage(filename);
	render();
}

Knight::~Knight()
{

}

void Knight::calcPossibleMoves(Piece* field[8][8], bool checkCheck)
{
	vector<PositionMoveType> moves;

	for (int dx = -2; dx <= 2; dx += 4)
	{
		for (int dy = -1; dy <= 1; dy += 2)
		{
			if (m_pos.x + dx >= 0 && m_pos.x + dx <= 7 && m_pos.y + dy >= 0 && m_pos.y + dy <= 7)
			{
				if (field[m_pos.x + dx][m_pos.y + dy] == nullptr)
				{
					moves = pushMove(moves,
						PositionMoveType(m_pos.x + dx, m_pos.y + dy, NORMAL),
						getOwnKing(field),
						field,
						checkCheck);
				}
				else if (field[m_pos.x + dx][m_pos.y + dy] != nullptr)
				{
					if (field[m_pos.x + dx][m_pos.y + dy]->getTeam() != m_team)
					{
						moves = pushMove(moves,
							PositionMoveType(m_pos.x + dx, m_pos.y + dy, NORMAL),
							getOwnKing(field),
							field,
							checkCheck);
					}
				}
			}
		}
	}

	for (int dy = -2; dy <= 2; dy += 4)
	{
		for (int dx = -1; dx <= 1; dx += 2)
		{
			if (m_pos.x + dx >= 0 && m_pos.x + dx <= 7 && m_pos.y + dy >= 0 && m_pos.y + dy <= 7)
			{
				if (field[m_pos.x + dx][m_pos.y + dy] == nullptr)
				{
					moves = pushMove(moves,
						PositionMoveType(m_pos.x + dx, m_pos.y + dy, NORMAL),
						getOwnKing(field),
						field,
						checkCheck);
				}
				else if (field[m_pos.x + dx][m_pos.y + dy] != nullptr)
				{
					if (field[m_pos.x + dx][m_pos.y + dy]->getTeam() != m_team)
					{
						moves = pushMove(moves,
							PositionMoveType(m_pos.x + dx, m_pos.y + dy, NORMAL),
							getOwnKing(field),
							field,
							checkCheck);
					}
				}
			}
		}
	}

	m_possibleMoves = moves;
}