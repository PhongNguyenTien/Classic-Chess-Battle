#include "Game.h"
#include <string>

Game::Game(SDL_BaseHandler* handler)
    :   WhitePawn1(new Pawn(WHITE, Position(0, 1), handler)),
        WhitePawn2(new Pawn(WHITE, Position(1, 1), handler)),
        WhitePawn3(new Pawn(WHITE, Position(2, 1), handler)),
        WhitePawn4(new Pawn(WHITE, Position(3, 1), handler)),
        WhitePawn5(new Pawn(WHITE, Position(4, 1), handler)),
        WhitePawn6(new Pawn(WHITE, Position(5, 1), handler)),
        WhitePawn7(new Pawn(WHITE, Position(6, 1), handler)),
        WhitePawn8(new Pawn(WHITE, Position(7, 1), handler)),
        BlackPawn1(new Pawn(BLACK, Position(0, 6), handler)),
        BlackPawn2(new Pawn(BLACK, Position(1, 6), handler)),
        BlackPawn3(new Pawn(BLACK, Position(2, 6), handler)),
        BlackPawn4(new Pawn(BLACK, Position(3, 6), handler)),
        BlackPawn5(new Pawn(BLACK, Position(4, 6), handler)),
        BlackPawn6(new Pawn(BLACK, Position(5, 6), handler)),
        BlackPawn7(new Pawn(BLACK, Position(6, 6), handler)),
        BlackPawn8(new Pawn(BLACK, Position(7, 6), handler)),
        BlackRook1(new Rook(BLACK, Position(0, 7), handler)),
        BlackRook2(new Rook(BLACK, Position(7, 7), handler)),
        WhiteRook1(new Rook(WHITE, Position(0, 0), handler)),
        WhiteRook2(new Rook(WHITE, Position(7, 0), handler)),
        BlackKnight1(new Knight(BLACK, Position(1, 7), handler)),
        BlackKnight2(new Knight(BLACK, Position(6, 7), handler)),
        WhiteKnight1(new Knight(WHITE, Position(1, 0), handler)),
        WhiteKnight2(new Knight(WHITE, Position(6, 0), handler)),
        BlackBishop1(new Bishop(BLACK, Position(2, 7), handler)),
        BlackBishop2(new Bishop(BLACK, Position(5, 7), handler)),
        WhiteBishop1(new Bishop(WHITE, Position(2, 0), handler)),
        WhiteBishop2(new Bishop(WHITE, Position(5, 0), handler)),
        BlackKing(new King(BLACK, Position(4, 7), handler)),
        WhiteKing(new King(WHITE, Position(4, 0), handler)),
        BlackQueen(new Queen(BLACK, Position(3, 7), handler)),
        WhiteQueen(new Queen(WHITE, Position(3, 0), handler)),

    turn(WHITE),
    m_handler(handler),
    checkEnPassant(true)

{
    m_field[0][7] = BlackRook1;
    m_field[7][7] = BlackRook2;
    m_field[0][0] = WhiteRook1;
    m_field[7][0] = WhiteRook2;

    m_field[1][7] = BlackKnight1;
    m_field[6][7] = BlackKnight2;
    m_field[1][0] = WhiteKnight1;
    m_field[6][0] = WhiteKnight2;

    m_field[2][7] = BlackBishop1;
    m_field[5][7] = BlackBishop2;
    m_field[2][0] = WhiteBishop1;
    m_field[5][0] = WhiteBishop2;

    m_field[4][7] = BlackKing;
    m_field[4][0] = WhiteKing;

    m_field[3][7] = BlackQueen;
    m_field[3][0] = WhiteQueen;

    m_field[0][1] = WhitePawn1;
    m_field[1][1] = WhitePawn2;
    m_field[2][1] = WhitePawn3;
    m_field[3][1] = WhitePawn4;
    m_field[4][1] = WhitePawn5;
    m_field[5][1] = WhitePawn6;
    m_field[6][1] = WhitePawn7;
    m_field[7][1] = WhitePawn8;

    m_field[0][6] = BlackPawn1;
    m_field[1][6] = BlackPawn2;
    m_field[2][6] = BlackPawn3;
    m_field[3][6] = BlackPawn4;
    m_field[4][6] = BlackPawn5;
    m_field[5][6] = BlackPawn6;
    m_field[6][6] = BlackPawn7;
    m_field[7][6] = BlackPawn8;

    for (int i = 2; i < 6; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            m_field[j][i] = nullptr;
        }
    }

    calcAllMoves();
}

Piece* Game::getFieldPos(int row, int col)
{
    return m_field[row][col];
}


Game::~Game()
{
    m_handler->cleanUp();
}

int Game::move(Piece* start, PositionMoveType move)
{

    if (checkEnPassant)
    {
        disableEnPassant();
    }
    else
    {
        checkEnPassant = true;
    }

    switch (move.moveType)
    {
    case NORMAL:
        normal(start->getPos().x, start->getPos().y, move.x, move.y);
        break;
    case CASTLE:
        castles(start->getPos().x, start->getPos().y, move.x, move.y);
        break;
    case ENPASSANT:
        enPassant(start->getPos().x, start->getPos().y, move.x, move.y);
        break;
    case NEWPIECE:
        exchange(start->getPos().x, start->getPos().y, move.x, move.y);
        break;
    default:
        break;
    }

    return gameState();
}


void Game::normal(int xStart, int yStart, int xEnd, int yEnd)
{
    m_field[xEnd][yEnd] = getFieldPos(xStart, yStart);
    m_field[xEnd][yEnd]->m_hasMoved = true;
    m_field[xStart][yStart] = nullptr;
    m_handler->undoPieceRender(xStart, yStart);
    m_field[xEnd][yEnd]->setPosition(Position(xEnd, yEnd));
    if (m_field[xEnd][yEnd] != nullptr)
    {
        m_handler->undoPieceRender(xEnd, yEnd);
    }
    m_field[xEnd][yEnd]->render();

    if (m_field[xEnd][yEnd]->getType() == PAWN)
    {
        if (abs(yEnd - yStart) == 2)
        {
            if (xEnd - 1 >= 0)
            {
                if (m_field[xEnd - 1][yEnd] != nullptr)
                {
                    if (m_field[xEnd - 1][yEnd]->getType() == PAWN)
                    {
                        Pawn* pwn = static_cast<Pawn*>(m_field[xEnd - 1][yEnd]);
                        pwn->setEnPassant(EnPassant(true, -1));
                        checkEnPassant = false;
                    }
                }
            }

            if (xEnd + 1 <= 7)
            {
                if (m_field[xEnd + 1][yEnd] != nullptr)
                {
                    if (m_field[xEnd + 1][yEnd]->getType() == PAWN)
                    {
                        Pawn* pwn = static_cast<Pawn*>(m_field[xEnd + 1][yEnd]);
                        pwn->setEnPassant(EnPassant(true, 1));
                        checkEnPassant = false;
                    }
                }
            }
        }
    }
}


void Game::enPassant(int xStart, int yStart, int xEnd, int yEnd)
{
    Pawn* pawn_start = static_cast<Pawn*>(m_field[xStart][yStart]);
    m_field[xEnd][yEnd - pawn_start->dy] = nullptr;
    m_field[xEnd][yEnd] = getFieldPos(xStart, yStart);
    m_field[xEnd][yEnd]->m_hasMoved = true;
    m_field[xStart][yStart] = nullptr;
    m_handler->undoPieceRender(xStart, yStart);
    m_handler->undoPieceRender(xEnd, yEnd - pawn_start->dy);
    m_field[xEnd][yEnd]->setPosition(Position(xEnd, yEnd));
    m_field[xEnd][yEnd]->render();
}


void Game::exchange(int xStart, int yStart, int xEnd, int yEnd)
{
    SDL_Texture* text_rook = m_handler->loadImage("image\\whiteRook.png");
    SDL_Texture* text_knight = m_handler->loadImage("image\\whiteKnight.png");
    SDL_Texture* text_bishop = m_handler->loadImage("image\\whiteBishop.png");
    SDL_Texture* text_queen = m_handler->loadImage("image\\whiteQueen.png");
    int y_draw = 0;
    Team team = WHITE;

    if (m_field[xStart][yStart]->getTeam() == BLACK)
    {
        text_rook = m_handler->loadImage("image\\blackRook.png");
        text_knight = m_handler->loadImage("image\\blackKnight.png");
        text_bishop = m_handler->loadImage("image\\blackBishop.png");
        text_queen = m_handler->loadImage("image\\blackQueen.png");
        y_draw = 3 * m_handler->SCREEN_HEIGHT / 4;
        team = BLACK;
    }

    SDL_SetRenderDrawColor(m_handler->m_renderer, 128, 64, 0, 255);
    SDL_Rect rectangle = { 0,
                          y_draw,
                          m_handler->SCREEN_WIDTH / 4,
                          m_handler->SCREEN_HEIGHT / 4 };
    SDL_RenderFillRect(m_handler->m_renderer, &rectangle);
    SDL_Rect src = { 0, 0, 60, 60 };
    m_handler->DrawRectangle(src, rectangle, text_rook);

    SDL_SetRenderDrawColor(m_handler->m_renderer, 255, 255, 255, 255);
    rectangle.x = m_handler->SCREEN_WIDTH / 4;
    SDL_RenderFillRect(m_handler->m_renderer, &rectangle);
    m_handler->DrawRectangle(src, rectangle, text_knight);

    SDL_SetRenderDrawColor(m_handler->m_renderer, 128, 64, 0, 255);
    rectangle.x = 2 * m_handler->SCREEN_WIDTH / 4;
    SDL_RenderFillRect(m_handler->m_renderer, &rectangle);
    m_handler->DrawRectangle(src, rectangle, text_bishop);

    SDL_SetRenderDrawColor(m_handler->m_renderer, 255, 255, 255, 255);
    rectangle.x = 3 * m_handler->SCREEN_WIDTH / 4;
    SDL_RenderFillRect(m_handler->m_renderer, &rectangle);
    m_handler->DrawRectangle(src, rectangle, text_queen);

    bool quit = false;
    int x = -1;
    int y = -1;

    Piece* clickedOn = nullptr;

    while (quit == false)
    {
        while (SDL_PollEvent(&m_handler->m_event))
        {
            if (m_handler->m_event.type == SDL_QUIT)
            {
                quit = true;
            }

            if (m_handler->m_event.type == SDL_MOUSEBUTTONDOWN)
            {
                x = m_handler->m_event.button.x / 160;
                y = m_handler->m_event.button.y / 160;

                if (y >= y_draw / 160 && y < y_draw / 160 + 1)
                {
                    if (x < m_handler->SCREEN_WIDTH / 640)
                    {
                        clickedOn = new Rook(team, Position(xEnd, yEnd), m_handler);
                    }
                    else if (x < 2 * m_handler->SCREEN_WIDTH / 640)
                    {
                        clickedOn = new Knight(team, Position(xEnd, yEnd), m_handler);
                    }
                    else if (x < 3 * m_handler->SCREEN_WIDTH / 640)
                    {
                        clickedOn = new Bishop(team, Position(xEnd, yEnd), m_handler);
                    }
                    else if (x <= 4 * m_handler->SCREEN_WIDTH / 640)
                    {
                        clickedOn = new Queen(team, Position(xEnd, yEnd), m_handler);
                    }

                }
            }

            if (m_handler->m_event.type == SDL_MOUSEBUTTONUP && clickedOn != nullptr)
            {
                quit = true;
            }
        }
    }

    m_field[xEnd][yEnd] = clickedOn;
    m_field[xStart][yStart] = nullptr;
    m_handler->undoPieceRender(xStart, yStart);
    m_handler->renderBackground();

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (m_field[i][j] != nullptr)
            {
                m_field[i][j]->render();
            }
        }
    }

    SDL_DestroyTexture(text_rook);
    SDL_DestroyTexture(text_bishop);
    SDL_DestroyTexture(text_knight);
    SDL_DestroyTexture(text_queen);
}


void Game::castles(int xStart, int yStart, int xEnd, int yEnd)
{
    if (xEnd == 0)
    {
        m_field[2][yEnd] = m_field[4][yEnd];
        m_field[3][yEnd] = m_field[0][yEnd];
        m_field[2][yEnd]->m_hasMoved = true;
        m_field[3][yEnd]->m_hasMoved = true;
        m_field[2][yEnd]->setPosition(Position(2, yEnd));
        m_field[3][yEnd]->setPosition(Position(3, yEnd));
        m_field[4][yEnd] = nullptr;
        m_field[0][yEnd] = nullptr;
        m_handler->undoPieceRender(4, yEnd);
        m_handler->undoPieceRender(0, yEnd);
        m_field[2][yEnd]->render();
        m_field[3][yEnd]->render();
    }
    else
    {
        m_field[6][yEnd] = m_field[4][yEnd];
        m_field[5][yEnd] = m_field[7][yEnd];
        m_field[6][yEnd]->m_hasMoved = true;
        m_field[5][yEnd]->m_hasMoved = true;
        m_field[6][yEnd]->setPosition(Position(6, yEnd));
        m_field[5][yEnd]->setPosition(Position(5, yEnd));
        m_field[4][yEnd] = nullptr;
        m_field[7][yEnd] = nullptr;
        m_handler->undoPieceRender(4, yEnd);
        m_handler->undoPieceRender(7, yEnd);
        m_field[6][yEnd]->render();
        m_field[5][yEnd]->render();
    }
}

int Game::gameState()
{
    bool lost = true;
    King* pivot = BlackKing;

    if (turn == BLACK)
    {
        pivot = WhiteKing;
    }

    pivot->setCheck(m_field, WhiteKing->getPos().x, WhiteKing->getPos().y);
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (m_field[i][j] != nullptr)
            {
                if (m_field[i][j]->getTeam() != turn)
                {
                    m_field[i][j]->calcPossibleMoves(m_field, true);
                    if (!m_field[i][j]->getPossibleMoves().empty())
                    {
                        lost = false;
                    }
                }
            }
        }
    }


    if (pivot->getCheck() && lost)
    {
        SDL_Delay(2000);
        SDL_Rect src = { 0, 0, m_handler->SCREEN_WIDTH, m_handler->SCREEN_HEIGHT };
        SDL_Rect rectangle = { 0, 0, m_handler->SCREEN_WIDTH, m_handler->SCREEN_HEIGHT };
        SDL_RenderFillRect(m_handler->m_renderer, &rectangle);

        if (turn == BLACK)
        {
            return 1;
        }
        else
        {
            return 2;
        }
    }
    else if (lost)
    {
        if (turn == BLACK || turn == WHITE)
        {

            SDL_Delay(2000);
            SDL_Rect src = { 0, 0, m_handler->SCREEN_WIDTH, m_handler->SCREEN_HEIGHT };
            SDL_Rect rectangle = { 0, 0, m_handler->SCREEN_WIDTH, m_handler->SCREEN_HEIGHT };
            SDL_RenderFillRect(m_handler->m_renderer, &rectangle);
            SDL_Texture* result = m_handler->loadImage("image\\draw.png");
            m_handler->DrawRectangle(src, rectangle, result);
            return 3;
        }

    }
    if (turn == BLACK)
    {
        turn = WHITE;
    }
    else
    {
        turn = BLACK;
    }
    return 0;
}

void Game::disableEnPassant()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (m_field[i][j] != nullptr)
            {
                if (m_field[i][j]->getType() == PAWN)
                {
                    Pawn* pwn = static_cast<Pawn*>(m_field[i][j]);
                    pwn->setEnPassant(EnPassant(false, 0));
                }
            }
        }
    }
}

void Game::renderPossibleMoves(Piece* piece)
{
    piece->calcPossibleMoves(m_field, true);
    vector<PositionMoveType> possible = piece->getPossibleMoves();
    SDL_Rect rectangle;
    for (const auto& value : possible) {
        if ((value.x + value.y) % 2 != 0)
        {
            SDL_SetRenderDrawColor(m_handler->m_renderer, 0, 134, 139, 255);
        }
        else
        {
            SDL_SetRenderDrawColor(m_handler->m_renderer, 164, 211, 238, 255);
        }
        rectangle = { value.x * m_handler->SCREEN_WIDTH / 8,
                      value.y * m_handler->SCREEN_HEIGHT / 8,
                      m_handler->SCREEN_WIDTH / 8,
                      m_handler->SCREEN_HEIGHT / 8 };
        SDL_RenderFillRect(m_handler->m_renderer, &rectangle);

        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (m_field[i][j] != nullptr)
                {
                    m_field[i][j]->render();
                }
            }
        }
    }
}

void Game::undoRenderPossibleMoves(Piece* piece)
{
    vector<PositionMoveType> possible = piece->getPossibleMoves();
    for (const auto& value : possible) {
        if ((value.x + value.y) % 2 == 0)
        {
            SDL_SetRenderDrawColor(m_handler->m_renderer, 128, 64, 0, 255);

        }
        else
        {
            SDL_SetRenderDrawColor(m_handler->m_renderer, 255, 255, 255, 255);
        }
        SDL_Rect rectangle = { value.x * m_handler->SCREEN_WIDTH / 8,
                                  value.y * m_handler->SCREEN_HEIGHT / 8,
                                  m_handler->SCREEN_WIDTH / 8,
                                  m_handler->SCREEN_HEIGHT / 8 };
        SDL_RenderFillRect(m_handler->m_renderer, &rectangle);

        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (m_field[i][j] != nullptr)
                {
                    m_field[i][j]->render();
                }
            }
        }
    }
}

void Game::calcAllMoves()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (m_field[i][j] != nullptr)
            {
                m_field[i][j]->calcPossibleMoves(m_field, true);
            }
        }
    }
}

bool Game::isValidMove(int x, int y, Piece* piece)
{
    vector<PositionMoveType> list = piece->getPossibleMoves();
    for (const auto& value : list) {
        if (value.x == x && value.y == y)
        {
            return true;
        }
    }
    return false;
}

