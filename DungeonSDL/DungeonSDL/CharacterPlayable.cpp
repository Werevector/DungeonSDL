#include "CharacterPlayable.h"


CharacterPlayable::CharacterPlayable()
{
	strength = 2;
}


CharacterPlayable::~CharacterPlayable()
{
}


void CharacterPlayable::Render()
{
	SDL_SetRenderDrawColor( Graphics::gRenderer, 0xFF, 0x33, 0x33, 0xFF );		
	SDL_RenderFillRect( Graphics::gRenderer, &mCharacter );
}


void CharacterPlayable::Update(vector<CharacterNonPlayable*>& npcSet)
{


	actMessage actorMessage;

	for (vector<actMessage>::iterator message = message_Queue.begin(); message != message_Queue.end(); ++message){

		switch (message->type){

		case MOVE_UPP:
			if (!EnemyPresent(mMapX, (mMapY - 1), npcSet))
			{
				if (!Utils::CoordsOutOfBounds(mMapX, mMapY - 1) && !(*c_collisionMap)[mMapX][mMapY - 1]){
					mMapY--;
					cout << "UP";
				}
			}
			else{
				actorMessage.intParam = strength;
				actorMessage.type = messageType::ACTION_TAKE_DAMAGE;
				mTargetNPC->AddActMessage(actorMessage);
				cout << "PlayerAttackUp \n";
			}
			break;
		case MOVE_DOWN:
			if (!EnemyPresent(mMapX, (mMapY + 1), npcSet))
			{
				if (!Utils::CoordsOutOfBounds(mMapX, mMapY + 1) && !(*c_collisionMap)[mMapX][mMapY + 1]){
					mMapY++;
					cout << "DOWN";
				}
			}else{
				actorMessage.intParam = strength;
				actorMessage.type = messageType::ACTION_TAKE_DAMAGE;
				mTargetNPC->AddActMessage(actorMessage);
				cout << "PlayerAttackDown \n";
			}
			break;
		case MOVE_LEFT:
			if (!EnemyPresent(mMapX - 1 , mMapY, npcSet))
			{
				if (!Utils::CoordsOutOfBounds(mMapX - 1, mMapY) && !(*c_collisionMap)[mMapX - 1][mMapY]){
					mMapX--;
					cout << "LEFT";
				}
			}else{
				actorMessage.intParam = strength;
				actorMessage.type = messageType::ACTION_TAKE_DAMAGE;
				mTargetNPC->AddActMessage(actorMessage);
				cout << "PlayerAttackLeft \n";
			}
			break;
		case MOVE_RIGHT:
			if (!EnemyPresent(mMapX + 1, mMapY, npcSet))
			{
				if (!Utils::CoordsOutOfBounds(mMapX + 1, mMapY) && !(*c_collisionMap)[mMapX + 1][mMapY]){
					mMapX++;
					cout << "RIGHT";
				}
			}else{
				actorMessage.intParam = strength;
				actorMessage.type = messageType::ACTION_TAKE_DAMAGE;
				mTargetNPC->AddActMessage(actorMessage);
				cout << "PlayerAttackRight \n";
			}
			break;
		case DEFAULT:
			break;
		}

	}
	
	SetMapPosition(mMapX, mMapY);
	
	message_Queue.clear();
	
}




bool CharacterPlayable::EnemyPresent(int x, int y, vector<CharacterNonPlayable*> npcSet){
	
	for (auto npc = npcSet.begin(); npc != npcSet.end(); ++npc){
		
		int npcX = (*npc)->getmMapX();
		int npcY = (*npc)->getmMapY();

		if (npcX == x && npcY == y){
			mTargetNPC = (*npc);
			return true;
		}
	}

	return false;

}

