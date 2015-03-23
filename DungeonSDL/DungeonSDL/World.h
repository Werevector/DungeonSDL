#pragma once
#include "TileMap.h"
#include "CharacterPlayable.h"
#include "CharacterNonPlayable.h"
#include <vector>
#include "ActMessage.h"

class World
{
public:
	World(void);
	~World(void);

	void SetDungeonMap(TileMap* map);
	void AddWorldCharacter(CharacterPlayable* character);
	void AddWorldNPCharacter(CharacterNonPlayable* character);
	
	//Character* getCharP();
	
	//Delegate message based on ID, currently only delegates to hero
	void DelegateMSG(actMessage);

	void Update();
	void Render();



private:
	TileMap *mDungeonMap;

	vector<CharacterPlayable*> mCharacters;
	vector<CharacterNonPlayable*> mNonPlayableCharacters;
};

