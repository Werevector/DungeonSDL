#include "Character.h"


Character::Character(void)
{
	mCharacter.x = 0;
	mCharacter.y = 0;
	mCharacter.w = 15;
	mCharacter.h = 15;

	mMapX = 0;
	mMapY = 0;

	health = 5;
	IS_DEAD = false;

	/*mPosX = 0;
	mPosY= 0;*/

}


Character::~Character(void)
{

}


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


void Character::SetCollisionMap(vector< vector<bool> >* collMap){
	c_collisionMap = collMap;
}


//void Character::Render()
//{
//	SDL_SetRenderDrawColor( Graphics::gRenderer, 0xFF, 0x00, 0x00, 0xFF );		
//	SDL_RenderFillRect( Graphics::gRenderer, &mCharacter );
//}


int Character::getmMapX(){
	return mMapX;
}

int Character::getmMapY(){
	return mMapY;
}

void Character::FlipX(){
	mMapX = abs( mMapX - TileMap::LEVEL_TILE_WIDTH + 1 );
}

void Character::FlipY(){
	mMapY = abs( mMapY - TileMap::LEVEL_TILE_HEIGHT + 1 );
}

void Character::CalcDamage(int damage){
	health -= damage;
	if (health < 0){
		IS_DEAD = true;
	}
}

void Character::AddActMessage(actMessage new_msg)
{
	message_Queue.push_back(new_msg);
}

bool Character::IsDead(){
	return IS_DEAD;
}

