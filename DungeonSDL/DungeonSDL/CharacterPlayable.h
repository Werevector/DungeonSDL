#pragma once
#include "Character.h"
#include "CharacterNonPlayable.h"
class CharacterPlayable :
	public Character
{
public:
	CharacterPlayable();
	~CharacterPlayable();

	virtual void Render() override;
	virtual void Update(vector<CharacterNonPlayable*>&) override;

	/*void AddActMessage(actMessage);*/

protected:

	CharacterNonPlayable* mTargetNPC;

	bool EnemyPresent(int, int, vector<CharacterNonPlayable*>);

};

