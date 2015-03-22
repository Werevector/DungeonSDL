#pragma once
#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Texture.h"


class Tile
{
public:
	//Initializes position and type
	Tile( int x, int y, int w, int h, int tileType ); 
	~Tile();

	//Shows the tile 
	void render(SDL_Rect& camera, SDL_Rect clips[], Texture tileTextureAtlas); 
	
	//Get the tile type 
	int getType(); 
	
	//Get the collision box 
	SDL_Rect getBox(); 

private: 
	//The attributes of the tile 
	SDL_Rect mBox; 
	
	//The tile type 
	int mType;
};

