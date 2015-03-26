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


void CharacterNonPlayable::Update(vector<CharacterNonPlayable*>& npcSet)
{
	for (vector<actMessage>::iterator message = message_Queue.begin(); message != message_Queue.end(); ++message){

		switch (message->type){
		case ACTION_TAKE_DAMAGE:
			CalcDamage(message->intParam);
			damageTaken = true;
		case DEFAULT:
			break;
		}
	}

	message_Queue.clear();

}


void CharacterNonPlayable::ReactToPlayerAction(vector<CharacterPlayable*> playerChars)
{
	int deltaX = 0;
	int deltaY = 0;

	for (int i = 0; i < playerChars.size(); i++)
	{
		SDL_Rect playerTile = playerChars[i]->Get_CurrentTile();

		if (mCurrentTile.x == playerTile.x)
		{
			deltaY = mCurrentTile.y - playerTile.y;
			if (abs(deltaY) > 2)
			{
				cout << endl << "X in range" << endl;
			}

		}
		else if (mCurrentTile.y == playerTile.y)
		{
			deltaX = mCurrentTile.x - playerTile.x;
			if (abs(deltaX) > 2)
			{
				cout << endl << "Y in range" << endl;
			}
		}

		//int deltaX = mCurrentTile.x - playerTile.x;
		//int deltaY = mCurrentTile.y - playerTile.y;

		//h 8 2
		//e 2 6
		// -6 4
	}


}