#pragma once

#include "Character.h"

//class CharacterPlayable;
#include "CharacterPlayable.h"

//class CharacterNonPlayable;
#include "CharacterNonPlayable.h"

#include "TileMap.h"
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
	
	void AddWorldCharacter(Character* character);
	void AddWorldNPCharacter(Character* character);
	
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

	vector<Character*> mCharacters;
	vector<Character*>* mNonPlayableCharacters;
};

