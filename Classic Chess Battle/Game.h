#pragma once
#include "Piece.h"
#include "SDL_BaseHandler.h"
#include "Piece.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "King.h"
#include "Queen.h"
#include "Menu.h"

using namespace std;

class Game
{
public:

    Game(SDL_BaseHandler* m_handler);

    ~Game();

    Piece* getFieldPos(int row, int col);

    int move(Piece* piece, PositionMoveType move);

    Team getTurn() { return turn; };

    bool isValidMove(int x, int y, Piece* piece);

    void calcAllMoves();

    void renderPossibleMoves(Piece* piece);

    void undoRenderPossibleMoves(Piece* piece);

    Piece* m_field[8][8];

    void disableEnPassant();

    void normal(int xStart, int yStart, int xEnd, int yEnd);

    void enPassant(int xStart, int yStart, int xEnd, int yEnd);

    void exchange(int xStart, int yStart, int xEnd, int yEnd);

    void castles(int xStart, int yStart, int xEnd, int yEnd);

    int gameState();

private:

    string backgroundFilename;

    Team turn;

    SDL_BaseHandler* m_handler;

    bool checkEnPassant;

    Pawn* WhitePawn1;
    Pawn* WhitePawn2;
    Pawn* WhitePawn3;
    Pawn* WhitePawn4;
    Pawn* WhitePawn5;
    Pawn* WhitePawn6;
    Pawn* WhitePawn7;
    Pawn* WhitePawn8;
    Pawn* BlackPawn1;
    Pawn* BlackPawn2;
    Pawn* BlackPawn3;
    Pawn* BlackPawn4;
    Pawn* BlackPawn5;
    Pawn* BlackPawn6;
    Pawn* BlackPawn7;
    Pawn* BlackPawn8;
    Rook* BlackRook1;
    Rook* BlackRook2;
    Rook* WhiteRook1;
    Rook* WhiteRook2;
    Knight* BlackKnight1;
    Knight* BlackKnight2;
    Knight* WhiteKnight1;
    Knight* WhiteKnight2;
    Bishop* BlackBishop1;
    Bishop* BlackBishop2;
    Bishop* WhiteBishop1;
    Bishop* WhiteBishop2;
    King* BlackKing;
    King* WhiteKing;
    Queen* BlackQueen;
    Queen* WhiteQueen;
};

