#pragma once
#include "Piece.h"

class Pawn : public Piece
{
public:
   
    Pawn(Team team, Position pos, SDL_BaseHandler* m_handler);

    ~Pawn();
   
    void calcPossibleMoves(Piece* field[8][8], bool checkCheck);
   
    int dy;

    EnPassant getEnPassant() { return m_enPassant; };
   
    void setEnPassant(EnPassant modifi) { m_enPassant = modifi; };

private:
    
    EnPassant m_enPassant;
};

