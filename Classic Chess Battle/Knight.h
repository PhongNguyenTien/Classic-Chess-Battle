#pragma once
#include "Piece.h"

class Knight : public Piece
{
public:
    Knight(Team team, Position pos, SDL_BaseHandler* m_handler);

    ~Knight();
    
    void calcPossibleMoves(Piece* field[8][8], bool checkCheck);

};

