#include "CharacterPlayable.h"


CharacterPlayable::CharacterPlayable()
{
}


CharacterPlayable::~CharacterPlayable()
{
}


void CharacterPlayable::Render()
{
	SDL_SetRenderDrawColor( Graphics::gRenderer, 0xFF, 0x00, 0x00, 0xFF );		
	SDL_RenderFillRect( Graphics::gRenderer, &mCharacter );
}


void CharacterPlayable::Update()
{

	for (vector<actMessage>::iterator message = message_Queue.begin(); message != message_Queue.end(); ++message){

		switch (message->type){

		case MOVE_UPP:
			if (!Utils::CoordsOutOfBounds(mMapX, mMapY - 1) && !(*c_collisionMap)[mMapX][mMapY - 1]){
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


void CharacterPlayable::AddActMessage(actMessage new_msg)
{
	message_Queue.push_back(new_msg);
}
