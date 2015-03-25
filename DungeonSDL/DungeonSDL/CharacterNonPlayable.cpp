#include "CharacterNonPlayable.h"


CharacterNonPlayable::CharacterNonPlayable()
{
}


CharacterNonPlayable::~CharacterNonPlayable()
{
}


void CharacterNonPlayable::Render()
{
	SDL_SetRenderDrawColor(Graphics::gRenderer, 0x00, 0xFF, 0x00, 0xFF);
	SDL_RenderFillRect(Graphics::gRenderer, &mCharacter);

}


void CharacterNonPlayable::Update()
{


}