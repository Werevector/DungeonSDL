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

	tileMap->LoadAndBuildTileMap(Utils::GetApplicationPath() + "/dungeon.map");
	mapStructure.emplace(0,tileMap);

	TileMap* nextMap;
	nextMap = new TileMap();

	nextMap->left = 0;

	nextMap->SetTileTexture(*gTileTextures.GetTexture(Textures::DUNGEON_MAP_TEST_32));
	nextMap->LoadAndBuildTileMap(Utils::GetApplicationPath() + "/dungeon2.map");
	mapStructure.emplace(1, nextMap);
	/*********************
	dummy stage
	*********************/

}

TileMap* DungeonStructure::getMap(int key){
	return mapStructure.find(key)->second;
}

TileMap* DungeonStructure::getStart(){
	return mapStructure.find(0)->second;
}