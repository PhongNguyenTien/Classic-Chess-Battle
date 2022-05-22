#include "MainLoop.h"
#include <iostream>

using namespace std;

int startGame(SDL_BaseHandler* m_handler)
{
    m_handler->renderBackground();
    Game* game = new Game(m_handler);
    bool quit = false;

    int xStart = -1;
    int yStart = -1;
    int xEnd = -1;
    int yEnd = -1;
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
                xStart = m_handler->m_event.button.x / 80;
                yStart = m_handler->m_event.button.y / 80;
                clickedOn = game->getFieldPos(xStart, yStart);
                if (clickedOn != nullptr)
                {
                    if (clickedOn->getTeam() == game->getTurn())
                    {
                        game->renderPossibleMoves(clickedOn);
                    }
                }
            }

            if (m_handler->m_event.type == SDL_MOUSEBUTTONUP)
            {
                if (clickedOn != nullptr)
                {
                    if (clickedOn->getTeam() == game->getTurn())
                    {
                        game->undoRenderPossibleMoves(clickedOn);
                    }
                }
                xEnd = m_handler->m_event.button.x / 80;
                yEnd = m_handler->m_event.button.y / 80;
                if (clickedOn != nullptr)
                {
                    if ((xStart != -1 && yStart != -1 && xEnd != -1 && yEnd != -1)
                            && (clickedOn->getTeam() == game->getTurn())
                            && (game->isValidMove(xEnd, yEnd, clickedOn)))
                    {
                        vector<PositionMoveType> list = game->getFieldPos(xStart, yStart)->getPossibleMoves();
                        for (const auto& value : list)
                        {
                            if (value.x == xEnd && value.y == yEnd)
                            {
                                int state = game->move(clickedOn, PositionMoveType(xEnd, yEnd, value.moveType));
                                if(state != 0)
                                {
                                    return state;
                                }
                            }
                        }
                        xStart = -1;
                        yStart = -1;
                        yEnd = -1;
                        game->calcAllMoves();
                        clickedOn = nullptr;
                    }
                }
            }
        }
        SDL_RenderPresent(m_handler->m_renderer);
    }
    return 0;
}
void runGameLoop()
{
    SDL_BaseHandler* m_handler = new SDL_BaseHandler();
    m_handler->init();

    Menu *mainMenu = new Menu("image/background.png", m_handler);

    Menu *whiteWinMenu = new Menu("image/whitewin.png", m_handler);

    Menu *blackWinMenu = new Menu("image/blackwin.png", m_handler);

    Menu *drawMenu = new Menu("image/draw.png", m_handler);

    Button *playGameButton = new Button(220, 210, "image/playbutton.png", m_handler, "PlayGame");

    Button *exitGameButton = new Button(220, 330, "image/exitbutton.png", m_handler, "ExitGame");

    Button *backGameButton = new Button(220, 210, "image/backbutton.png", m_handler, "PlayAgain");

    mainMenu->AddButton(playGameButton);

    mainMenu->AddButton(exitGameButton);

    whiteWinMenu->AddButton(backGameButton);

    whiteWinMenu->AddButton(exitGameButton);

    blackWinMenu->AddButton(backGameButton);

    blackWinMenu->AddButton(exitGameButton);

    drawMenu->AddButton(backGameButton);

    drawMenu->AddButton(exitGameButton);

    bool quit = false;

    SDL_Event e;

    SDL_Renderer* renderer = m_handler->m_renderer;

    int menu_id = 0;

    while(!quit)
    {
        while(SDL_PollEvent(&e) != 0)
        {
            if(e.type == SDL_QUIT)
            {
                quit = true;
            }
            else
            {
                string response;
                if(menu_id == 0)
                {
                    response = mainMenu->handleEvent(&e);
                }

                if(menu_id == 1)
                {
                    response = blackWinMenu->handleEvent(&e);
                }

                if(menu_id == 2)
                {
                    response = whiteWinMenu->handleEvent(&e);
                }

                if(menu_id == 3)
                {
                    response = drawMenu->handleEvent(&e);
                }

                if(response == "PlayGame")
                {
                    int state = startGame(m_handler);
                    menu_id = state;
                }

                if(response == "PlayAgain")
                {
                    int state = startGame(m_handler);
                    menu_id = state;
                }

                if(response == "ExitGame")
                {
                    quit = true;
                }
            }
        }
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);

        if(menu_id == 0)mainMenu->render();
        if(menu_id == 1)blackWinMenu->render();
        if(menu_id == 2)whiteWinMenu->render();
        if(menu_id == 3)drawMenu->render();

        SDL_RenderPresent(renderer);
    }

    m_handler->cleanUp();

}
