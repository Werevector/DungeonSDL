#include "Tile.h"


Tile::Tile( int x, int y, int w, int h, int tileType ) 
{ 
	//Get the offsets 
	mBox.x = x; mBox.y = y; 
	
	//Set the collision box 
	mBox.w = w; 
	mBox.h = h; 
	
	//Get the tile type 
	mType = tileType; 
}


Tile::~Tile(void)
{
}


void Tile::render(SDL_Rect& camera, SDL_Rect clips[], Texture tileTextureAtlas) 
{ 
	//If the tile is on screen 
	//if( checkCollision( camera, mBox ) ) 
	//{ 
		//Show the tile 
		//tileTextureAtlas.render( mBox.x - camera.x, mBox.y - camera.y, &clips[ mType ] );
		tileTextureAtlas.render(mBox.x, mBox.y, &clips[mType]);
	//} 
}


int Tile::getType()
{
    return mType;
}


SDL_Rect Tile::getBox()
{
    return mBox;
}
