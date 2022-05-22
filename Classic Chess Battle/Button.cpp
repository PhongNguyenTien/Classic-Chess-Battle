#include "Button.h"

using namespace std;

Button::Button(int posX, int posY, string pathToButton, SDL_BaseHandler* handler, string response)
{
    m_handler = handler;

    mTexture = m_handler->loadImage(pathToButton.c_str());

    mBox = {posX, posY, 200, 100};

    m_response = response;
}

Button::~Button()
{

}

string Button::handleEvent(SDL_Event* e)
{
    if((e->type) == SDL_MOUSEBUTTONDOWN || (e->type) == SDL_MOUSEBUTTONUP || (e->type) == SDL_MOUSEMOTION)
    {
        bool inside = true;
        int mousePosX, mousePosY;
        SDL_GetMouseState(&mousePosX, &mousePosY);

        if(mousePosX < mBox.x || mousePosX > mBox.x + mBox.w || mousePosY < mBox.y || mousePosY > mBox.y + mBox.h)
        {
            inside = false;
        }

        if(inside)
        {
            switch(e->type)
            {
            case SDL_MOUSEBUTTONDOWN:
                break;
            case SDL_MOUSEMOTION:
                break;
            case SDL_MOUSEBUTTONUP:
                return m_response;
                break;
            }
        }
    }
    return "none";
}

void Button::render()
{
    SDL_Rect src = {0, 0, 200, 100};

    SDL_Rect dest = mBox;

    m_handler->DrawRectangle(src, dest, mTexture);
}
