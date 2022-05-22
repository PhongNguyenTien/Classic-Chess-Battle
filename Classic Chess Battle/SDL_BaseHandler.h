#pragma once
#include <SDL.h>
#include <SDL_Image.h>
#include <string>
#include "sdl_ttf.h"

using namespace std;

class SDL_BaseHandler
{
public:

	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 640;

	SDL_Window* m_window = nullptr;

	SDL_Renderer* m_renderer = nullptr;

	SDL_Event m_event;

	SDL_BaseHandler();

	bool init();

	void cleanUp();

	~SDL_BaseHandler();

	void DrawRectangle(SDL_Rect source, SDL_Rect dest, SDL_Texture* text);

	void undoPieceRender(int x, int y);

	SDL_Texture* loadImage(string filename);

	void renderBackground();

};

