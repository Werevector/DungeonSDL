#include "DungeonStructure.h"


DungeonStructure::DungeonStructure()
{

	int currentKey = 0;

}

bool DungeonStructure::LoadStructure(string loadPath, Textures gTileTextures)
{

	/*********************
	dummy stage
	*********************/

	DungeonRoom* newRoom;
	newRoom = new DungeonRoom();
	newRoom->BuildRoom(Utils::GetApplicationPath() + "\\start.map");
	Character* NPC = new CharacterNonPlayable();
	newRoom->AddNPC(NPC, 2, 5);
	newRoom->AddGate(8,2,1);
	newRoom->right = 1;
	mRoomStructure.emplace(0, newRoom);
	
	DungeonRoom* newRoom2;
	newRoom2 = new DungeonRoom();
	newRoom2->BuildRoom(Utils::GetApplicationPath() + "\\right.map");
	Character* NPC2 = new CharacterNonPlayable();
	newRoom2->AddNPC(NPC2, 5, 5);
	newRoom2->AddGate(8, 2, 1);
	newRoom2->left = 0;
	newRoom2->right = 2;
	mRoomStructure.emplace(1, newRoom2);

	DungeonRoom* newRoom3;
	newRoom3 = new DungeonRoom();
	newRoom3->BuildRoom(Utils::GetApplicationPath() + "\\right2.map");
	Character* NPC3 = new CharacterNonPlayable();
	newRoom3->AddNPC(NPC3, 3, 6);
	newRoom3->AddGate(8, 2, 1);
	newRoom3->left = 1;
	mRoomStructure.emplace(2, newRoom3);



	/*********************
	dummy stage
	*********************/
	
	return true;
}

DungeonRoom* DungeonStructure::getMap(int key){
	return mRoomStructure.find(key)->second;
}

DungeonRoom* DungeonStructure::getStart(){
	return mRoomStructure.find(0)->second;
}