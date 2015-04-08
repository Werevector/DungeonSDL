#pragma once

#include "Character.h"

//class CharacterPlayable;
#include "CharacterPlayable.h"

//class CharacterNonPlayable;
#include "CharacterNonPlayable.h"

//#include "TileMap.h"
#include <vector>
#include "ActMessage.h"
#include "DungeonStructure.h"
#include "Textures.h"
#include "GameState.h"
#include "DungeonRoom.h"



class World
{
public:
	World();
	~World(void);


	bool LoadDungeon(string);
	
	void AddWorldCharacter(Character* character);
	void AddWorldNPCharacter(Character* character);
	
	//Character* getCharP();
	
	//Delegate message based on ID, currently only delegates to hero
	void DelegateMSG(actMessage);

	void GetPlayerData(int &playerX, int &playerY, int &health);

	void Update();
	void Render();



private:
	
	void SetDungeonRoom(DungeonRoom* room);
	DungeonStructure mDungeon;
	DungeonRoom* mCurrentRoom;

	Textures gTileTextures;

	vector<Character*> mCharacters;
	vector<Character*>* mNonPlayableCharacters;
};

