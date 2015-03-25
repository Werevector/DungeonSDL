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

//Skriv om, ser ikkje koffor dan e dar
void Character::SetMapPosition(int x, int y)
{
	mMapX = x;
	mMapY = y;

	if(!mMapTilePositions.empty())
	{
		SDL_Rect tile = mMapTilePositions[x][y];
		mCharacter.x = tile.x - mCharacter.w / 2;
		mCharacter.y = tile.y - mCharacter.h / 2;



	}
}


void Character::SetMapTilePositions(vector< vector<SDL_Rect> > tilePositions)
{
	mMapTilePositions = tilePositions;
}

void Character::AddActMessage(actMessage new_msg){

	message_Queue.push_back(new_msg);

}

void Character::SetCollisionMap(vector< vector<bool> >* collMap){
	c_collisionMap = collMap;
}


void Character::Render()
{
	SDL_SetRenderDrawColor( Graphics::gRenderer, 0xFF, 0x00, 0x00, 0xFF );		
	SDL_RenderFillRect( Graphics::gRenderer, &mCharacter );
}


void Character::Update(){

	//Switch moves through message types, and acts accordingly
	for (vector<actMessage>::iterator message = message_Queue.begin(); message != message_Queue.end(); ++message){

		switch (message->type){
			
		case MOVE_UPP:
			if (! Utils::CoordsOutOfBounds(mMapX, mMapY - 1) && !(*c_collisionMap)[mMapX][mMapY-1]){
				mMapY--;
				cout << "UP";
			}
			break;
		case MOVE_DOWN:
			if (!Utils::CoordsOutOfBounds(mMapX, mMapY + 1) && !(*c_collisionMap)[mMapX][mMapY + 1]){
				mMapY++;
				cout << "DOWN";
			}
			break;
		case MOVE_LEFT:
			if (!Utils::CoordsOutOfBounds(mMapX - 1, mMapY) && !(*c_collisionMap)[mMapX - 1][mMapY]){
				mMapX--;
				cout << "LEFT";
			}
			break;
		case MOVE_RIGHT:
			if (!Utils::CoordsOutOfBounds(mMapX + 1, mMapY) && !(*c_collisionMap)[mMapX + 1][mMapY]){
				mMapX++;
				cout << "RIGHT";
			}
			break;
		case DEFAULT:
			break;
		}

	}

	SetMapPosition(mMapX, mMapY);

	message_Queue.clear();

}
