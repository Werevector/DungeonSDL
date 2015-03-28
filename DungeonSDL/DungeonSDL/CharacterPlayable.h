#pragma once

class CharacterNonPlayable;

#include "Character.h"
#include "CharacterNonPlayable.h"
#include "GameState.h"

class CharacterPlayable :
	public Character
{
public:
	CharacterPlayable();
	~CharacterPlayable();

	void Render();
	void Update(vector<CharacterNonPlayable*>&);

	/*void AddActMessage(actMessage);*/

protected:

	CharacterNonPlayable* mTargetNPC;

	bool EnemyPresent(int, int, vector<CharacterNonPlayable*>);

};
