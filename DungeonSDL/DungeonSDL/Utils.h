#pragma once
#include <string>
#include "SDL.h"
#include <windows.h>
#include <SDL_ttf.h>
#include "Texture.h"
#include "GameState.h"
//#include "TileMap.h"
#include <vector>
#include "GameTimer.h"

using namespace std;

class Utils
{
public:
	//Utils(void);
	//~Utils(void);

	static string GetApplicationPath();

	static bool CoordsOutOfBounds(int,int);

	static vector<SDL_Point> Bresenham(int, int, int const, int const);
	
	static vector<SDL_Point*> A_Star_PathCalc(int, int, int, int, vector< vector<bool> >);

	//static void RenderGameInfo(SDL_Rect*, TTF_Font*);

	static void CalculateFrameStats(GameTimer timer, float &fps, float &mspf);
	//static float GetFramePerSecond();
	//static float GetFrameCount();

private:
	//static int frameCnt;
	//static float timeElapsed;

	//float fps;
	//float mspf;

};

