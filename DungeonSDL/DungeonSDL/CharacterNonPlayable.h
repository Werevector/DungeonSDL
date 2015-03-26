#pragma once

class CharacterPlayable;

#include "Character.h"
#include "CharacterPlayable.h"

class CharacterNonPlayable :
	public Character
{
public:
	CharacterNonPlayable();
	~CharacterNonPlayable();

	void Render();
	void Update(vector<CharacterPlayable*>&);

	void ReactToPlayerAction(vector<CharacterPlayable*>);

};
