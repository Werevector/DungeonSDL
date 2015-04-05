#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <fstream>
#include "Tile.h"
#include "Texture.h"
#include "Textures.h"
#include "TileTypeCodes.h"
#include "GameState.h"

class Character;
#include "Character.h"

//class CharacterNonPlayable;
//#include "CharacterNonPlayable.h"


using namespace std;

class TileMap
{
public:

	//Tile constants 
	static const int TILE_WIDTH = 32; 
	static const int TILE_HEIGHT = 32; 

	//static const int TILE_WIDTH = 64;
	//static const int TILE_HEIGHT = 64;

	//static const int TILE_WIDTH = 16;
	//static const int TILE_HEIGHT = 16;

	int TOTAL_TILES; 
	static const int TOTAL_TILE_SPRITES = 100; 

	//The dimensions of the level 
	int LEVEL_TILE_WIDTH; 
	int LEVEL_TILE_HEIGHT; 
	int LEVEL_WIDTH; 
	int LEVEL_HEIGHT; 

	//Constructor Destructor
	TileMap(void);
	~TileMap(void);

	void SetTileTexture();
	bool LoadAndBuildTileMap(string appPath);
	vector< vector<SDL_Rect> > GetMapTilePositions();

	void Render(vector< vector<bool> >*);

	vector<Character*>* getNPCListP();
	vector<Tile> getTileSet();

	void addNPC(Character*);

private:
	
	SDL_Rect mTileTextureClips[ TOTAL_TILE_SPRITES ];
	vector<Tile> mTileSet;

	Textures gTileTextures;
	
	Texture *mTileTextureAtlas;

	void ClipSheet();
	bool ReadTypeMap(ifstream*);
	void ReservePositions(int, int);

	vector< vector<SDL_Rect> > mTilePostions;
};

