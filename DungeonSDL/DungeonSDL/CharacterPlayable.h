#pragma once
#include "Character.h"
class CharacterPlayable :
	public Character
{
public:
	CharacterPlayable();
	~CharacterPlayable();

	virtual void Render() override;
	virtual void Update() override;

	void AddActMessage(actMessage);

	vector <actMessage> message_Queue;
};

