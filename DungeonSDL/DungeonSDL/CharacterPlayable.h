#pragma once

#include "Character.h"
#include "GameState.h"

class CharacterPlayable :
	public Character
{
public:
	CharacterPlayable();
	~CharacterPlayable();

	void Render();
	void Update(vector<Character*>&);

	/*void AddActMessage(actMessage);*/

protected:

	Character* mTargetNPC;

	bool EnemyPresent(int, int, vector<Character*>);

};
