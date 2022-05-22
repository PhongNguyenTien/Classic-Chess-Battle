#pragma once
#include "SDL_BaseHandler.h"

using namespace std;

class Button
{
    SDL_Rect mBox;
    SDL_BaseHandler* m_handler;
    SDL_Texture *mTexture;
    string m_response;
public:
    Button(int posX, int posY, string pathToButton, SDL_BaseHandler *handler, string response);
    ~Button();
    string handleEvent(SDL_Event* e);
    void render();
};

