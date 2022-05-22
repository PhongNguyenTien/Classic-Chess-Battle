#include "Menu.h"

#include <iostream>

using namespace std;
Menu::Menu(string pathToBackground, SDL_BaseHandler* handler)
{
    m_handler = handler;

    m_texture = m_handler->loadImage(pathToBackground.c_str());

    button.clear();
}

Menu::~Menu()
{

}

string Menu::handleEvent(SDL_Event *e)
{
    for(int i = 0; i < button.size(); i++)
    {
        string response = button[i]->handleEvent(e);
        if(response != "none")
        {
            return response;
        }
    }
    return "none";
}

void Menu::render()
{
    SDL_Rect src = {0, 0, 640, 640};

    SDL_Rect dest = {0, 0, 640, 640};

    m_handler->DrawRectangle(src, dest, m_texture);
    
    for(int i = 0;i < button.size(); i++)
    {
        button[i]->render();
    }
}

void Menu::AddButton(Button* newButton)
{
    button.push_back(newButton);
}
