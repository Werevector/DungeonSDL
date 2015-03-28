#include "TileMap.h"


TileMap::TileMap(void)
	//: mTilePostions(100, std::vector<std::vector<SDL_Rect> >(100, std::vector<SDL_Rect>(100, 0)))
{
	vector<SDL_Rect> tempRectangles;
	tempRectangles.resize(9);
	tempRectangles.reserve(9);
	for(int i = 0; i < 9; i++)
	{
		mTilePostions.push_back(tempRectangles);
	}

	collisionMap = vector<std::vector<bool>>(LEVEL_TILE_WIDTH, std::vector<bool>(LEVEL_TILE_HEIGHT));
}


TileMap::~TileMap(void)
{
}


bool TileMap::LoadAndBuildTileMap(string path)
{
	bool tilesLoaded = true;
	Tile *tile = 0;
	/*vector<SDL_Rect> tempRectangles;*/

	int xCounter = 0;
	int yCounter = 0;

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
		//Initialize the tiles
		for( int i = 0; i < TOTAL_TILES; ++i )
		{
			//Determines what kind of tile will be made
			int tileType = -1;

			//Read tile from map file
			mapStream >> tileType;

			//If the was a problem in reading the map
			if( mapStream.fail() )
			{
				//Stop loading map
				printf( "Error loading map: Unexpected end of file!\n" );
				tilesLoaded = false;
				break;
			}

			//If the number is a valid tile number
			if( ( tileType >= 0 ) && ( tileType < TOTAL_TILE_SPRITES ) )
			{


				SDL_Rect rect = {x + TILE_WIDTH / 2, y + TILE_HEIGHT / 2, 0, 0};
				mTilePostions[xCounter][yCounter] = rect;
				
				if (tileType == TILE_WATER || tileType >= TILE_STATUE)
				{
					collisionMap[xCounter][yCounter] = true;
				}
				
				//tempRectangles.push_back(rect);
				if(xCounter < LEVEL_TILE_WIDTH - 1)
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

				tile = new Tile( x, y, TILE_WIDTH, TILE_HEIGHT, tileType );
				mTileSet.push_back(*tile);
			}
			//If we don't recognize the tile type
			else
			{
				//Stop loading map
				printf( "Error loading map: Invalid tile type at %d!\n", i );
				tilesLoaded = false;
				break;
			}

			//Move to next tile spot
			x += TILE_WIDTH;

			//If we've gone too far
			if( x >= LEVEL_WIDTH )
			{
				//Move back
				x = 0;

				//Move to the next row
				y += TILE_HEIGHT;
			}
		}
		
		//Clip the sprite sheet
		if( tilesLoaded )
		{
			int clipW = 32;
			int clipH = 32;

			mTileTextureClips[ TILE_STONEFLOOR ].x = 0;
			mTileTextureClips[ TILE_STONEFLOOR ].y = 0;
			mTileTextureClips[ TILE_STONEFLOOR ].w = clipW;
			mTileTextureClips[ TILE_STONEFLOOR ].h = clipH;

			mTileTextureClips[ TILE_GRAVELFLOOR ].x = 0;
			mTileTextureClips[ TILE_GRAVELFLOOR ].y = clipH;
			mTileTextureClips[ TILE_GRAVELFLOOR ].w = clipW;
			mTileTextureClips[ TILE_GRAVELFLOOR ].h = clipH;

			mTileTextureClips[ TILE_WATER ].x = 0;
			mTileTextureClips[ TILE_WATER ].y = clipH * 2;
			mTileTextureClips[ TILE_WATER ].w = clipW;
			mTileTextureClips[ TILE_WATER ].h = clipH;

			mTileTextureClips[ TILE_BOARDFLOOR_HORIZONTAL ].x = 0;
			mTileTextureClips[ TILE_BOARDFLOOR_HORIZONTAL ].y = clipH * 3;
			mTileTextureClips[ TILE_BOARDFLOOR_HORIZONTAL ].w = clipW;
			mTileTextureClips[ TILE_BOARDFLOOR_HORIZONTAL ].h = clipH;

			mTileTextureClips[ TILE_BOARDFLOOR_VERTICAL ].x = 0;
			mTileTextureClips[ TILE_BOARDFLOOR_VERTICAL ].y = clipH * 4;
			mTileTextureClips[ TILE_BOARDFLOOR_VERTICAL ].w = clipW;
			mTileTextureClips[ TILE_BOARDFLOOR_VERTICAL ].h = clipH;

			mTileTextureClips[ TILE_STATUE ].x = 0;
			mTileTextureClips[ TILE_STATUE ].y = clipH * 5;
			mTileTextureClips[ TILE_STATUE ].w = clipW;
			mTileTextureClips[ TILE_STATUE ].h = clipH;

			mTileTextureClips[ TILE_WALL_DOWN ].x = clipW;
			mTileTextureClips[ TILE_WALL_DOWN ].y = 0;
			mTileTextureClips[ TILE_WALL_DOWN ].w = clipW;
			mTileTextureClips[ TILE_WALL_DOWN ].h = clipH;

			mTileTextureClips[ TILE_WALL_LEFT ].x = clipW;
			mTileTextureClips[ TILE_WALL_LEFT ].y = clipH;
			mTileTextureClips[ TILE_WALL_LEFT ].w = clipW;
			mTileTextureClips[ TILE_WALL_LEFT ].h = clipH;

			mTileTextureClips[ TILE_WALL_UP ].x = clipW;
			mTileTextureClips[ TILE_WALL_UP ].y = clipH * 2;
			mTileTextureClips[ TILE_WALL_UP ].w = clipW;
			mTileTextureClips[ TILE_WALL_UP ].h = clipH;

			mTileTextureClips[ TILE_WALL_RIGHT ].x = clipW;
			mTileTextureClips[ TILE_WALL_RIGHT ].y = clipH * 3;
			mTileTextureClips[ TILE_WALL_RIGHT ].w = clipW;
			mTileTextureClips[ TILE_WALL_RIGHT ].h = clipH;

		}
	}

    //Close the file
    mapStream.close();

	



    //If the map was loaded fine
    return tilesLoaded;
}


void TileMap::SetTileTexture(Texture &tileTextureAtlas)
{
	mTileTextureAtlas = &tileTextureAtlas;
}


vector< vector<SDL_Rect> > TileMap::GetMapTilePositions()
{
	return mTilePostions;
}

vector< vector<bool> >* TileMap::getCollisionMapP(){
	return &collisionMap;
}


void TileMap::Render()
{
	
	for( int i = 0; i < TOTAL_TILES; ++i )
	{

		//Texture rendTex = &mTileTextureClips[mTileSet[i].getType()];

		SDL_Rect t = mTileSet[i].getBox();
		
		//Coloring un-passable terrain

		/*if (mTileSet[i].getType() == TILE_WATER || mTileSet[i].getType() >= TILE_STATUE){
			
			mTileTextureAtlas->setColor(255, 50, 50);
		}
		else{
			
			mTileTextureAtlas->setColor(255, 255, 255);
		}*/
		
		mTileTextureAtlas->renderBox( &t, &mTileTextureClips[ mTileSet[i].getType() ] );
		
	}

	//SDL_Rect backgroundRect = { 0, 0, mTileTextureAtlas->getWidth(), mTileTextureAtlas->getHeight() };
	//mTileTextureAtlas->renderBox( &backgroundRect, NULL );

}
