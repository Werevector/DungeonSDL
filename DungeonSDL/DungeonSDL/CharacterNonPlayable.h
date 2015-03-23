#pragma once
#include "Character.h"
class CharacterNonPlayable :
	public Character
{
public:
	CharacterNonPlayable();
	~CharacterNonPlayable();

	virtual void Render() override;
	virtual void Update() override;
};

