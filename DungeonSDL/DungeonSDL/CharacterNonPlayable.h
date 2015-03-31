#pragma once
//class Character;
#include "Character.h"

class CharacterNonPlayable :
	public Character
{
public:
	CharacterNonPlayable();
	~CharacterNonPlayable();

	void Render();
	void Update(vector<Character*>&);

	void ReactToPlayerAction(vector<Character*>);

};
