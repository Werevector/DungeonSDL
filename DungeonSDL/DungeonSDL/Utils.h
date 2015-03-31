#pragma once
#include <string>
#include "SDL.h"
#include <windows.h>
//#include "TileMap.h"
#include <vector>
using namespace std;

class Utils
{
public:
	//Utils(void);
	//~Utils(void);

	static string GetApplicationPath();

	static bool CoordsOutOfBounds(int,int);

	static vector<SDL_Point> Bresenham(int, int, int const, int const);
	

};

