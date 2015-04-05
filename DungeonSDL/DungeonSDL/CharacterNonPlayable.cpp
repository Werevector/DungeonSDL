#include "CharacterNonPlayable.h"


CharacterNonPlayable::CharacterNonPlayable()
{
	damageTaken = false;
}


CharacterNonPlayable::~CharacterNonPlayable()
{
}


void CharacterNonPlayable::Render()
{
	if (!IS_DEAD)
	{
		if(!damageTaken)
			SDL_SetRenderDrawColor(Graphics::gRenderer, 0x00, 0xFF, 0x00, 0xFF);
		else
			SDL_SetRenderDrawColor(Graphics::gRenderer, 0xFF, 0x00, 0x00, 0xFF);
		
		SDL_RenderFillRect(Graphics::gRenderer, &mCharacter);
		
		damageTaken = false;
	}

}


void CharacterNonPlayable::Update(vector<Character*>& playerSet)
{
	
	for (vector<actMessage>::iterator message = message_Queue.begin(); message != message_Queue.end(); ++message){

		switch (message->type){
		case ACTION_TAKE_DAMAGE:
			CalcDamage(message->intParam);
			damageTaken = true;
		case REACT_TO_ACTION:
			ReactToPlayerAction(playerSet);
			CalcVision();
		case DEFAULT:
			break;
		}
	}

	SetMapPosition(mMapX, mMapY);

	message_Queue.clear();
	

}


void CharacterNonPlayable::ReactToPlayerAction(vector<Character*> playerChars)
{
	int deltaX = 0;
	int deltaY = 0;
	int newX = mMapX;
	int newY = mMapY;
	int playerX = 0;
	int playerY = 0;

	for (int i = 0; i < playerChars.size(); i++)
	{
		playerX = playerChars[i]->getmMapX();
		playerY = playerChars[i]->getmMapY();

		if (mMapX == playerX)
		{
			deltaY = mMapY - playerY;
			if (abs(deltaY) <= 3)
			{
				if (deltaY > 0)
					newY--;
				else if (deltaY < 0)
					newY++;
			}

		}
		else if (mMapY == playerY)
		{
			deltaX = mMapX - playerX;
			if (abs(deltaX) <= 3)
			{
				if (deltaX > 0)
					newX--;
				else if (deltaX < 0)
					newX++;
			}
		}
	}

	if (!(newX == playerX && newY == playerY))
		SetMapPosition(newX, newY);

}