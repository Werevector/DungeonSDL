#pragma once
#include "Character.h"
#include "CharacterPlayable.h"
class CharacterNonPlayable :
	public Character
{
public:
	CharacterNonPlayable();
	~CharacterNonPlayable();

	virtual void Render() override;
	virtual void Update() override;

	void ReactToPlayerAction(vector<CharacterPlayable*> playerChars);
};

