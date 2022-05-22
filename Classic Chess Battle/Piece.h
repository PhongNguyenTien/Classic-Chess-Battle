#pragma once
#include <vector>
#include "SDL_BaseHandler.h"
#include <SDL.h>

using namespace std;

enum Team { BLACK, WHITE, NONE };

enum PieceType { PAWN, ROOK, KNIGHT, BISHOP, KING, QUEEN };

enum MoveType { NORMAL, CASTLE, ENPASSANT, NEWPIECE };

struct Position
{
	int x;
	int y;

	Position()
	{

	}

	Position(int _x, int _y)
	{
		x = _x;
		y = _y;
	}
};

struct PositionMoveType
{
	int x;
	int y;
	MoveType moveType;

	PositionMoveType()
	{

	}

	PositionMoveType(int _x, int _y, MoveType _moveType)
	{
		x = _x;
		y = _y;
		moveType = _moveType;
	}
};

struct PositionPieceType
{
	int x;
	int y;
	PieceType pieceType;

	PositionPieceType()
	{

	}

	PositionPieceType(int _x, int _y, PieceType _pieceType)
	{
		x = _x;
		y = _y;
		pieceType = _pieceType;
	}
};

struct EnPassant
{
	bool check;
	int x;

	EnPassant()
	{
		
	}

	EnPassant(bool _check, int _x)
	{
		check = _check;
		x = _x;
	}
};
class King;

class Piece
{
public:

	vector<PositionMoveType> getPossibleMoves() { return m_possibleMoves; };

	Team getTeam() { return m_team; }
	
	void setPosition(Position newPos) { m_pos = newPos; }
	
	Position getPos() { return m_pos; };
	
	Piece(Team team, Position pos, SDL_BaseHandler* m_handler, PieceType type);
	
	Piece(const Piece& piece);
	
	~Piece();
	
	void render();
	
	virtual void calcPossibleMoves(Piece* field[8][8], bool checkCheck) = 0;
	
	bool m_hasMoved;
	
	PieceType getType() { return m_type; };

protected:
	
	SDL_Texture* m_texture;

	SDL_BaseHandler* m_handler;
	
	Team m_team;

	PieceType m_type;
	
	vector<PositionMoveType> m_possibleMoves;
	
	Position m_pos;

	vector<PositionMoveType> pushMove(vector<PositionMoveType> moveList,
		PositionMoveType move,
		King* king,
		Piece* field[8][8],
		bool checkCheck);

	King* getOwnKing(Piece* field[8][8]);
};

