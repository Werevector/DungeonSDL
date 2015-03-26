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