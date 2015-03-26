#pragma once
#include "Character.h"
#include "CharacterPlayable.h"
class CharacterNonPlayable :
	public Character
{
public:
	CharacterNonPlayable();
	~CharacterNonPlayable();

	void ReactToPlayerAction(vector<CharacterPlayable*> playerChars);

	virtual void Render();
	virtual void Update(vector<CharacterNonPlayable*>&);

};

