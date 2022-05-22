#include "Bishop.h"

Bishop::Bishop(Team team, Position pos, SDL_BaseHandler* handler)
	:Piece(team, pos, handler, BISHOP)
{
	string filename;
	if (team == BLACK)
	{
		filename = "image\\blackBishop.png";
	}
	else
	{
		filename = "image\\whiteBishop.png";
	}
	m_handler = handler;
	m_texture = handler->loadImage(filename);
	render();
}

Bishop::~Bishop()
{

}

void Bishop::calcPossibleMoves(Piece* field[8][8], bool checkCheck)
{
	vector<PositionMoveType> moves;
	int dx_copy;
	int dy_copy;
	for (int dx = -1; dx <= 1; dx += 2)
	{
		for (int dy = -1; dy <= 1; dy += 2)
		{
			dx_copy = dx;
			dy_copy = dy;

			while (field[m_pos.x + dx_copy][m_pos.y + dy_copy] == nullptr
				&& (m_pos.x + dx_copy >= 0 && m_pos.x + dx_copy <= 7 && m_pos.y + dy_copy >= 0 && m_pos.y + dy_copy <= 7))
			{
				moves = pushMove(moves,
					PositionMoveType(m_pos.x + dx_copy, m_pos.y + dy_copy, NORMAL),
					getOwnKing(field),
					field,
					checkCheck);
				if (dx_copy < 0)
				{
					dx_copy -= 1;
				}
				else
				{
					dx_copy += 1;
				}
				if (dy_copy < 0)
				{
					dy_copy -= 1;
				}
				else
				{
					dy_copy += 1;
				}
			}

			if (field[m_pos.x + dx_copy][m_pos.y + dy_copy] != nullptr
				&& (m_pos.x + dx_copy >= 0 && m_pos.x + dx_copy <= 7 && m_pos.y + dy_copy >= 0 && m_pos.y + dy_copy <= 7))
			{
				if (field[m_pos.x + dx_copy][m_pos.y + dy_copy]->getTeam() != m_team)
				{
					moves = pushMove(moves,
						PositionMoveType(m_pos.x + dx_copy, m_pos.y + dy_copy, NORMAL),
						getOwnKing(field),
						field,
						checkCheck);
				}
			}
		}
	}

	m_possibleMoves = moves;
}



