#pragma once
#include "Piece.h"

class Rook : public Piece
{
public:
   
    Rook(Team team, Position pos, SDL_BaseHandler* m_handler);

    ~Rook();
  
    void calcPossibleMoves(Piece* field[8][8], bool checkCheck);

};



