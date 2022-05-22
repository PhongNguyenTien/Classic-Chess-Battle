#pragma once

#include "Button.h"
#include <vector>

class Menu
{
    SDL_Texture* m_texture;
    vector < Button* > button;
    SDL_BaseHandler* m_handler;
public:
    Menu(string pathToBackground, SDL_BaseHandler* handler);
    ~Menu();
    string handleEvent(SDL_Event* e);
    void render();
    void AddButton(Button *newButton);
};
