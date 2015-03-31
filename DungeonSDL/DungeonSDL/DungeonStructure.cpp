#include "DungeonStructure.h"


DungeonStructure::DungeonStructure()
{

	/*TileMap* tileMap;
	tileMap = new TileMap();
	tileMap->SetTileTexture(*gTileTextures.GetTexture(Textures::DUNGEON_MAP_TEST_32));
	tileMap->LoadAndBuildTileMap(Utils::GetApplicationPath());
	gWorld->SetDungeonMap(tileMap);*/

	int currentKey = 0;


}

bool DungeonStructure::LoadStructure(string loadPath, Textures gTileTextures)
{

	/*********************
	dummy stage
	*********************/
	TileMap* tileMap;
	tileMap = new TileMap();
	tileMap->SetTileTexture(*gTileTextures.GetTexture(Textures::DUNGEON_MAP_TEST_32));

	tileMap->right = 1;

	tileMap->LoadAndBuildTileMap(Utils::GetApplicationPath() + "\\start.map");
	Character* enemy3;
	enemy3 = new CharacterNonPlayable();
	enemy3->SetMapTilePositions(tileMap->GetMapTilePositions());
	enemy3->SetMapPosition(3, 3);
	tileMap->addNPC(enemy3);
	mapStructure.emplace(0,tileMap);

	TileMap* nextMap;
	nextMap = new TileMap();
	nextMap->left = 0;
	nextMap->right = 2;
	nextMap->SetTileTexture(*gTileTextures.GetTexture(Textures::DUNGEON_MAP_TEST_32));
	nextMap->LoadAndBuildTileMap(Utils::GetApplicationPath() + "\\right.map");

	Character* enemy;
	enemy = new CharacterNonPlayable();
	enemy->SetMapTilePositions(nextMap->GetMapTilePositions());
	enemy->SetMapPosition(5, 6);
	nextMap->addNPC(enemy);

	mapStructure.emplace(1, nextMap);

	TileMap* nextMap2;
	nextMap2 = new TileMap();
	nextMap2->left = 1;
	nextMap2->SetTileTexture(*gTileTextures.GetTexture(Textures::DUNGEON_MAP_TEST_32));
	nextMap2->LoadAndBuildTileMap(Utils::GetApplicationPath() + "\\right2.map");

	Character* enemy2;
	enemy2 = new CharacterNonPlayable();
	enemy2->SetMapTilePositions(nextMap2->GetMapTilePositions());
	enemy2->SetMapPosition(6, 6);
	nextMap2->addNPC(enemy2);

	mapStructure.emplace(2, nextMap2);

	



	/*********************
	dummy stage
	*********************/
	
	return true;
}

TileMap* DungeonStructure::getMap(int key){
	return mapStructure.find(key)->second;
}

TileMap* DungeonStructure::getStart(){
	return mapStructure.find(0)->second;
}