#include "TileMap.h"


TileMap::TileMap(void)
	//: mTilePostions(100, std::vector<std::vector<SDL_Rect> >(100, std::vector<SDL_Rect>(100, 0)))
{
	/*vector<SDL_Rect> tempRectangles;
	tempRectangles.resize(100);
	tempRectangles.reserve(100);
	for(int i = 0; i < 100; i++)
	{
		mTilePostions.push_back(tempRectangles);
	}*/
}


TileMap::~TileMap(void)
{

}


bool TileMap::LoadAndBuildTileMap(string path)
{
	bool tilesLoaded = true;
	
	/*vector<SDL_Rect> tempRectangles;*/

	
	string fileLine;

	int totalX = 0;
	int totalY = 0;

    //The tile offsets
    int x = 0, y = 0;

    ifstream mapStream( path );
    if( !mapStream.is_open())
    {
		printf( "Unable to load map file!\n" );
		tilesLoaded = false;
    }
	else
	{

		while (mapStream >> fileLine){
			
			if (fileLine.compare("WIDTH") == 0)
				mapStream >> LEVEL_TILE_WIDTH;

			if (fileLine.compare("HEIGHT") == 0)
				mapStream >> LEVEL_TILE_HEIGHT;

			if (fileLine.compare("MAP") == 0){
				
				LEVEL_WIDTH = TILE_WIDTH * LEVEL_TILE_WIDTH;
				LEVEL_HEIGHT = TILE_HEIGHT * LEVEL_TILE_HEIGHT;

				ReservePositions(LEVEL_TILE_WIDTH, LEVEL_TILE_HEIGHT);
				tilesLoaded = ReadTypeMap(&mapStream);
				
				
				
			}
		}

		if (tilesLoaded)
			ClipSheet();
		else
			cout << "Problem reading Map";

	}

    //Close the file
    mapStream.close();

	

	gTileTextures.LoadTextures();
	SetTileTexture();

	WINDOW_CENTER_OFFSET_X = (WINDOW_WIDTH / 2) - (LEVEL_WIDTH / 2);
	WINDOW_CENTER_OFFSET_Y = (WINDOW_HEIGHT / 2) - (LEVEL_HEIGHT / 2);
	

    //If the map was loaded fine
    return tilesLoaded;
}


void TileMap::SetTileTexture()
{
	//mTileTextureAtlas = &tileTextureAtlas;
	mTileTextureAtlas = gTileTextures.GetTexture(Textures::DUNGEON_MAP_TEST_32);
}


vector< vector<SDL_Rect> > TileMap::GetMapTilePositions()
{
	return mTilePostions;
}

void TileMap::Render(vector< vector<bool> >* playerVision)
{
	
	WINDOW_CENTER_OFFSET_X = (WINDOW_WIDTH / 2) - (LEVEL_WIDTH / 2);
	WINDOW_CENTER_OFFSET_Y = (WINDOW_HEIGHT / 2) - (LEVEL_HEIGHT / 2);

	for( int i = 0; i < TOTAL_TILES; ++i )
	{

		//Texture rendTex = &mTileTextureClips[mTileSet[i].getType()];

		SDL_Rect t = mTileSet[i].getBox();

		t.x += WINDOW_CENTER_OFFSET_X;
		t.y += WINDOW_CENTER_OFFSET_Y;

		int x = (i) % LEVEL_TILE_HEIGHT;
		int y = floor(i / LEVEL_TILE_HEIGHT);

		//adding playervision "shadow"
		if ( (*playerVision)[x][y]){	
			
			mTileTextureAtlas->setColor(200, 200, 200);
		}
		else{
			mTileTextureAtlas->setColor(100, 100, 100);
		}

		//Color NPC vision
		
		/*for (int i = 0; i < NPCList.size(); i++){
			if ( (*NPCList[i]->getVisionMapP())[x][y] )
				mTileTextureAtlas->setColor(200, 100, 100);
		}
		*/
		if (mTileSet[i].getType() != TILE_EMPTY)
		mTileTextureAtlas->renderBox( &t, &mTileTextureClips[ mTileSet[i].getType() ] );
		
	}

}

bool TileMap::ReadTypeMap(ifstream* mapStream){
	

	bool tilesLoaded = true;
	int tileType = -1;
	Tile *tile = 0;

	int xCounter = 0;
	int yCounter = 0;

	int tileNumber = 0;

	//The tile offsets
	int x = 0, y = 0;

	//Initialize the tiles
	while ((*mapStream) >> tileType)
	{


		//If the was a problem in reading the map
		if (mapStream->fail())
		{
			//Stop loading map
			printf("Error loading map: Unexpected end of file!\n");
			tilesLoaded = false;
			break;
		}

		//If the number is a valid tile number
		if ((tileType >= 0) && (tileType < TOTAL_TILE_SPRITES))
		{


			SDL_Rect rect = { x + TILE_WIDTH / 2, y + TILE_HEIGHT / 2, 0, 0 };
			mTilePostions[xCounter][yCounter] = rect;

			//tempRectangles.push_back(rect);
			if (xCounter < LEVEL_TILE_WIDTH - 1)
			{
				xCounter++;
			}
			else
			{
				//mTilePostions.push_back(tempRectangles);
				//tempRectangles.clear();
				xCounter = 0;
				yCounter++;
			}

			//mTilePostions.push_back(rect);

			tile = new Tile(x, y, TILE_WIDTH, TILE_HEIGHT, tileType);
			mTileSet.push_back(*tile);
			tileNumber++;
		}
		//If we don't recognize the tile type
		else
		{
			//Stop loading map
			printf("Error loading map: Invalid tile type %d!\n", tileType);
			tilesLoaded = false;
			break;
		}

		//Move to next tile spot
		x += TILE_WIDTH;

		//If we've gone too far
		if (x >= LEVEL_WIDTH)
		{
			//Move back
			x = 0;

			//Move to the next row
			y += TILE_HEIGHT;
		}
	}

	TOTAL_TILES = tileNumber;

	return tilesLoaded;

}

void TileMap::ReservePositions(int width, int height){

	vector<SDL_Rect> tempRectangles;
	tempRectangles.resize(width);
	tempRectangles.reserve(height);

	for (int i = 0; i < width; i++)
	{
		mTilePostions.push_back(tempRectangles);
	}

}

void TileMap::ClipSheet(){

	int clipW = 32;
	int clipH = 32;

	mTileTextureClips[TILE_STONEFLOOR].x = 0;
	mTileTextureClips[TILE_STONEFLOOR].y = 0;
	mTileTextureClips[TILE_STONEFLOOR].w = clipW;
	mTileTextureClips[TILE_STONEFLOOR].h = clipH;

	mTileTextureClips[TILE_GRAVELFLOOR].x = 0;
	mTileTextureClips[TILE_GRAVELFLOOR].y = clipH;
	mTileTextureClips[TILE_GRAVELFLOOR].w = clipW;
	mTileTextureClips[TILE_GRAVELFLOOR].h = clipH;

	mTileTextureClips[TILE_WATER].x = 0;
	mTileTextureClips[TILE_WATER].y = clipH * 2;
	mTileTextureClips[TILE_WATER].w = clipW;
	mTileTextureClips[TILE_WATER].h = clipH;

	mTileTextureClips[TILE_BOARDFLOOR_HORIZONTAL].x = 0;
	mTileTextureClips[TILE_BOARDFLOOR_HORIZONTAL].y = clipH * 3;
	mTileTextureClips[TILE_BOARDFLOOR_HORIZONTAL].w = clipW;
	mTileTextureClips[TILE_BOARDFLOOR_HORIZONTAL].h = clipH;

	mTileTextureClips[TILE_BOARDFLOOR_VERTICAL].x = 0;
	mTileTextureClips[TILE_BOARDFLOOR_VERTICAL].y = clipH * 4;
	mTileTextureClips[TILE_BOARDFLOOR_VERTICAL].w = clipW;
	mTileTextureClips[TILE_BOARDFLOOR_VERTICAL].h = clipH;

	mTileTextureClips[TILE_STATUE].x = 0;
	mTileTextureClips[TILE_STATUE].y = clipH * 5;
	mTileTextureClips[TILE_STATUE].w = clipW;
	mTileTextureClips[TILE_STATUE].h = clipH;

	mTileTextureClips[TILE_WALL_DOWN].x = clipW;
	mTileTextureClips[TILE_WALL_DOWN].y = 0;
	mTileTextureClips[TILE_WALL_DOWN].w = clipW;
	mTileTextureClips[TILE_WALL_DOWN].h = clipH;

	mTileTextureClips[TILE_WALL_LEFT].x = clipW;
	mTileTextureClips[TILE_WALL_LEFT].y = clipH;
	mTileTextureClips[TILE_WALL_LEFT].w = clipW;
	mTileTextureClips[TILE_WALL_LEFT].h = clipH;

	mTileTextureClips[TILE_WALL_UP].x = clipW;
	mTileTextureClips[TILE_WALL_UP].y = clipH * 2;
	mTileTextureClips[TILE_WALL_UP].w = clipW;
	mTileTextureClips[TILE_WALL_UP].h = clipH;

	mTileTextureClips[TILE_WALL_RIGHT].x = clipW;
	mTileTextureClips[TILE_WALL_RIGHT].y = clipH * 3;
	mTileTextureClips[TILE_WALL_RIGHT].w = clipW;
	mTileTextureClips[TILE_WALL_RIGHT].h = clipH;
}

vector<Tile> TileMap::getTileSet(){
	return mTileSet;
}