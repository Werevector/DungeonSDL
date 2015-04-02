#pragma once
#include <SDL.h>
class Graphics
{
public:

	static void InitAll();

	//static const int SCREEN_WIDTH = 640;
	//static const int SCREEN_HEIGHT = 480;
	static const int SCREEN_WIDTH = 288;
	static const int SCREEN_HEIGHT = 288;

	static SDL_Renderer* gRenderer;
	static SDL_Window* gWindow;

};

