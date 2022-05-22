#pragma once
#include "Piece.h"
#include "King.h"
class Bishop : public Piece
{
public:
   
    Bishop(Team team, Position pos, SDL_BaseHandler* m_handler);

    ~Bishop();
    
    void calcPossibleMoves(Piece* field[8][8], bool checkCheck);

};

