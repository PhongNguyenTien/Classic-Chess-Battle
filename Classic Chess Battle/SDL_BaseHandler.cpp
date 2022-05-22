#include "SDL_BaseHandler.h"
#include <iostream>


SDL_Texture* SDL_BaseHandler::loadImage(string filename)
{
	SDL_Surface* loadedImage = nullptr;

	loadedImage = IMG_Load(filename.c_str());

	if (loadedImage == nullptr)
	{
		cout << "Couldn't load " << filename << endl;
	}

	SDL_SetColorKey(loadedImage, SDL_TRUE, SDL_MapRGB(loadedImage->format, 0, 0xFF, 0));

	SDL_Texture* text = SDL_CreateTextureFromSurface(m_renderer, loadedImage);

	return text;
}

void SDL_BaseHandler::renderBackground()
{
	bool white = true;
	SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (white)
			{
				SDL_SetRenderDrawColor(m_renderer, 128, 64, 0, 255);
			}
			else
			{
				SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
			}
			white = !white;
			SDL_Rect rectangle = { i * SCREEN_WIDTH / 8,
									j * SCREEN_HEIGHT / 8,
								  SCREEN_WIDTH / 8,
								  SCREEN_HEIGHT / 8 };
			SDL_RenderFillRect(m_renderer, &rectangle);
		}
		white = !white;
	}
}

void SDL_BaseHandler::undoPieceRender(int x, int y)
{
	if ((x + y) % 2 == 0)
	{
		SDL_SetRenderDrawColor(m_renderer, 128, 64, 0, 255);
	}
	else
	{
		SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
	}
	SDL_Rect rectangle = { x * SCREEN_WIDTH / 8,
						  y * SCREEN_HEIGHT / 8,
						  SCREEN_WIDTH / 8,
						  SCREEN_HEIGHT / 8 };
	SDL_RenderFillRect(m_renderer, &rectangle);
}

void SDL_BaseHandler::cleanUp()
{

	SDL_DestroyWindow(m_window);
	SDL_DestroyRenderer(m_renderer);
	SDL_Quit();
}


void SDL_BaseHandler::DrawRectangle(SDL_Rect source, SDL_Rect dest, SDL_Texture* text)
{
	if (text != nullptr)
	{
		SDL_RenderCopy(m_renderer, text, &source, &dest);
		//SDL_RenderPresent(m_renderer);

		//SDL_UpdateWindowSurface(m_window);
	}
	else
	{
		cout << "DrawRectangle: text was nullptr" << endl;
	}
}



SDL_BaseHandler::~SDL_BaseHandler()
{
	cleanUp();
}


SDL_BaseHandler::SDL_BaseHandler()
{

}

bool SDL_BaseHandler::init()
{
	m_window = nullptr;
	//m_gameSurface = nullptr;

	bool quit = false;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		cleanUp();
		return false;
	}
	else
	{
		//Create window
		m_window = SDL_CreateWindow("Classic Chess", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (m_window == nullptr)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else
		{
			m_renderer = SDL_CreateRenderer(m_window, -1, 0);
		}
	}
	return true;
}



