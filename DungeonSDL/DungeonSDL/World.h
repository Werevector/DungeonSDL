#pragma once
#include "TileMap.h"
#include "CharacterPlayable.h"
#include "CharacterNonPlayable.h"
#include <vector>
#include "ActMessage.h"
#include "DungeonStructure.h"
#include "Textures.h"
#include "GameState.h"

class World
{
public:
	World(void);
	~World(void);


	bool LoadDungeon(string);
	
	void AddWorldCharacter(CharacterPlayable* character);
	void AddWorldNPCharacter(CharacterNonPlayable* character);
	
	//Character* getCharP();
	
	//Delegate message based on ID, currently only delegates to hero
	void DelegateMSG(actMessage);

	void Update();
	void Render();



private:
	
	void SetDungeonMap(TileMap* map);
	DungeonStructure mDungeon;
	TileMap *mDungeonMap;

	Textures gTileTextures;

	vector<CharacterPlayable*> mCharacters;
	vector<CharacterNonPlayable*> mNonPlayableCharacters;
};

