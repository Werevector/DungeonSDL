#pragma once

#include "Character.h"
#include "GameState.h"
#include "PlayerBowArrow.h"


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

	void ShootBowArrow(Character*);

	Character* mTargetNPC;

	bool EnemyPresent(int, int, vector<Character*>);
	bool CoordsOutOfBounds(int, int);

	vector<PlayerBowArrow*> m_BowArrows;
};
