#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <fstream>
#include "Tile.h"
#include "Texture.h"

class CharacterNonPlayable;
//#include "CharacterNonPlayable.h"

using namespace std;

class TileMap
{
public:

	//Tile constants 
	static const int TILE_WIDTH = 32; 
	static const int TILE_HEIGHT = 32; 

	static const int TOTAL_TILES = 81; 
	static const int TOTAL_TILE_SPRITES = 10; 

	//The dimensions of the level 
	static const int LEVEL_TILE_WIDTH = 9; 
	static const int LEVEL_TILE_HEIGHT = 9; 
	static const int LEVEL_WIDTH = TILE_WIDTH * 9; 
	static const int LEVEL_HEIGHT = TILE_HEIGHT * 9; 

	//Type codes
	static const int TILE_STONEFLOOR = 0; 
	static const int TILE_GRAVELFLOOR = 1; 
	static const int TILE_WATER = 2; 
	static const int TILE_BOARDFLOOR_HORIZONTAL = 3; 
	static const int TILE_BOARDFLOOR_VERTICAL = 4; 
	static const int TILE_STATUE = 5; 
	static const int TILE_WALL_DOWN = 6; 
	static const int TILE_WALL_LEFT = 7; 
	static const int TILE_WALL_UP = 8; 
	static const int TILE_WALL_RIGHT = 9; 

	//Constructor Destructor
	TileMap(void);
	~TileMap(void);

	void SetTileTexture(Texture &tileTextureAtlas);
	bool LoadAndBuildTileMap(string appPath);
	vector< vector<SDL_Rect> > GetMapTilePositions();

	vector< vector<bool> >* getCollisionMapP();
	vector< vector<bool> >* getLightPassageMapP();

	void Render(vector< vector<bool> >*);

	//Links
	int up;
	int down;
	int left;
	int right;

	vector<CharacterNonPlayable*>* getNPCListP();
	void addNPC(CharacterNonPlayable*);

private:
	SDL_Rect mTileTextureClips[ TOTAL_TILE_SPRITES ];
	vector<Tile> mTileSet;
	
	Texture *mTileTextureAtlas;

	vector< vector<SDL_Rect> > mTilePostions;
	vector< vector<bool> > collisionMap;
	vector< vector<bool> > mLightPassageMap;
	
	vector<CharacterNonPlayable*> NPCList;

};

