#include "Character.h"


Character::Character(void)
{
	mCharacter.x = 0;
	mCharacter.y = 0;
	mCharacter.w = 15;
	mCharacter.h = 15;

	mMapX = 0;
	mMapY = 0;

	/*mPosX = 0;
	mPosY= 0;*/

}


Character::~Character(void)
{

}


// TODO Runar: Skriv om, ser ikkje koffor dan e dar
// Jan: da e for di eg tenkte at input kordinatane ska representera tiles på mappen
// og ikkje screen koordinata, og player rect'n ska ligga midt i tilen og ikkje oppe til venstre
void Character::SetMapPosition(int x, int y)
{
	mMapX = x;
	mMapY = y;

	if(!mMapTilePositions.empty())
	{
		mCurrentTile = mMapTilePositions[x][y];
		mCharacter.x = mCurrentTile.x - mCharacter.w / 2;
		mCharacter.y = mCurrentTile.y - mCharacter.h / 2;
	}
}


void Character::SetMapTilePositions(vector< vector<SDL_Rect> > tilePositions)
{
	mMapTilePositions = tilePositions;
}


SDL_Rect Character::Get_CurrentTile()
{
	return mCurrentTile;
}


void Character::SetCollisionMap(vector< vector<bool> >* collMap){
	c_collisionMap = collMap;
}


void Character::Render()
{
	SDL_SetRenderDrawColor( Graphics::gRenderer, 0xFF, 0x00, 0x00, 0xFF );		
	SDL_RenderFillRect( Graphics::gRenderer, &mCharacter );
}



