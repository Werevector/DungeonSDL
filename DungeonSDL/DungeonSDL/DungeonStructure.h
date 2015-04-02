#pragma once
#include <vector>
#include <map>
#include <string>
#include "TileMap.h"
#include "Textures.h"
#include "DungeonRoom.h"

class CharacterNonPlayable;
#include "CharacterNonPlayable.h"

using namespace std;

class DungeonStructure{


public:

	DungeonStructure();
	
	bool LoadStructure(string, Textures);
	
	DungeonRoom* getStart();
	DungeonRoom* getMap(int);

private:

	//Structure map
	map<int, DungeonRoom*> mRoomStructure;

	int currentKey;

};