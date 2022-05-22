#pragma once
#include "Piece.h"
class Queen : public Piece
{
public:
    Queen(Team team, Position pos, SDL_BaseHandler* m_handler);

    ~Queen();

    void calcPossibleMoves(Piece* field[8][8], bool checkCheck);


};

