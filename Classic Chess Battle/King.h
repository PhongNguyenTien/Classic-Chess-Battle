#pragma once
#include "Piece.h"

class King : public Piece
{
public:

    King(Team team, Position pos, SDL_BaseHandler* m_handler);

    ~King();
    
    void calcPossibleMoves(Piece* field[8][8], bool checkCheck);

    void setCheck(Piece* field[8][8], int x, int y);

    bool getCheck() { return m_check; };

private:
    
    bool m_check;
};

