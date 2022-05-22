#include "Pawn.h"
#include <iostream>

Pawn::Pawn(Team team, Position pos, SDL_BaseHandler* handler)
	:Piece(team, pos, m_handler, PAWN), m_enPassant(EnPassant(false, 0))
{
	string filename;
	if (team == BLACK)
	{
		filename = "image\\blackPawn.png";
	}
	else
	{
		filename = "image\\whitePawn.png";
	}
	m_handler = handler;
	m_texture = handler->loadImage(filename);

	if (team == BLACK)
	{
		dy = -1;
	}
	else
	{
		dy = 1;
	}

	render();
}

Pawn::~Pawn()
{

}

void Pawn::calcPossibleMoves(Piece* field[8][8], bool checkCheck)
{
	vector<PositionMoveType> moves;

	if (m_pos.y + dy == 0 || m_pos.y + dy == 7)
	{
		if (field[m_pos.x][m_pos.y + dy] == nullptr)
		{
			moves = pushMove(moves,
				PositionMoveType(m_pos.x, m_pos.y + dy, NEWPIECE),
				getOwnKing(field),
				field,
				checkCheck);
		}
	}
	else
	{
		if (field[m_pos.x][m_pos.y + dy] == nullptr)
		{
			moves = pushMove(moves,
				PositionMoveType(m_pos.x, m_pos.y + dy, NORMAL),
				getOwnKing(field),
				field,
				checkCheck);
		}
	}

	if ((m_pos.y + 2 * dy >= 0) && (m_pos.y + 2 * dy <= 7))
	{
		if (field[m_pos.x][m_pos.y + 2 * dy] == nullptr && field[m_pos.x][m_pos.y + dy] == nullptr && !m_hasMoved)
		{
			moves = pushMove(moves,
				PositionMoveType(m_pos.x, m_pos.y + 2 * dy, NORMAL),
				getOwnKing(field),
				field,
				checkCheck);
		}
	}

	if (m_pos.x + 1 <= 7)
	{
		if (field[m_pos.x + 1][m_pos.y + dy] != nullptr)
		{
			if (field[m_pos.x + 1][m_pos.y + dy]->getTeam() != m_team)
			{
				if (m_pos.y + dy == 0 || m_pos.y + dy == 7)
				{
					moves = pushMove(moves,
						PositionMoveType(m_pos.x + 1, m_pos.y + dy, NEWPIECE),
						getOwnKing(field),
						field,
						checkCheck);
				}
				else
				{
					moves = pushMove(moves,
						PositionMoveType(m_pos.x + 1, m_pos.y + dy, NORMAL),
						getOwnKing(field),
						field,
						checkCheck);
				}
			}
		}
	}
	if (m_pos.x - 1 >= 0)
	{
		if (field[m_pos.x - 1][m_pos.y + dy] != nullptr)
		{
			if (field[m_pos.x - 1][m_pos.y + dy]->getTeam() != m_team)
			{
				if (m_pos.y + dy == 0 || m_pos.y + dy == 7)
				{
					moves = pushMove(moves,
						PositionMoveType(m_pos.x - 1, m_pos.y + dy, NEWPIECE),
						getOwnKing(field),
						field,
						checkCheck);
				}
				else
				{
					moves = pushMove(moves,
						PositionMoveType(m_pos.x - 1, m_pos.y + dy, NORMAL),
						getOwnKing(field),
						field,
						checkCheck);
				}
			}
		}
	}

	if (m_enPassant.check == true && m_enPassant.x == -1)
	{
		moves = pushMove(moves,
			PositionMoveType(m_pos.x + 1, m_pos.y + dy, ENPASSANT),
			getOwnKing(field),
			field,
			checkCheck);
	}
	if (m_enPassant.check == true && m_enPassant.x == 1)
	{
		moves = pushMove(moves,
			PositionMoveType(m_pos.x - 1, m_pos.y + dy, ENPASSANT),
			getOwnKing(field),
			field,
			checkCheck);
	}
	m_possibleMoves = moves;
}






