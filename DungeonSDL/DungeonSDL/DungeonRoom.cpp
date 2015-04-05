#include "DungeonRoom.h"

DungeonRoom::DungeonRoom(){
	mCollisionMap = vector<std::vector<bool>>(RoomTileHeight, std::vector<bool>(RoomTileHeight));
	mLightPassageMap = vector<std::vector<bool>>(RoomTileHeight, std::vector<bool>(RoomTileHeight));
}

void DungeonRoom::BuildRoom(string path){
	mTileMap.LoadAndBuildTileMap(path);
	mTileMap.SetTileTexture();

	BuildCollisionMap(mTileMap.getTileSet());
	BuildLightPassageMap(mTileMap.getTileSet());

}

void DungeonRoom::BuildCollisionMap(vector<Tile> tileMap){
	
	mCollisionMap = vector<std::vector<bool>>(mTileMap.LEVEL_TILE_WIDTH, std::vector<bool>(mTileMap.LEVEL_TILE_HEIGHT));

	for (int i = 0; i < tileMap.size(); i++){
		
		int x = (i) % mTileMap.LEVEL_TILE_WIDTH;
		int y = floor(i / mTileMap.LEVEL_TILE_HEIGHT);
	
		if (tileMap[i].getType() == TILE_WATER || tileMap[i].getType() >= TILE_STATUE)
			mCollisionMap[x][y] = true;

	}
}

void DungeonRoom::BuildLightPassageMap(vector<Tile>tileMap){
	
	mLightPassageMap = vector<std::vector<bool>>(mTileMap.LEVEL_TILE_WIDTH, std::vector<bool>(mTileMap.LEVEL_TILE_HEIGHT));

	for (int i = 0; i < tileMap.size(); i++){

		int x = (i) % mTileMap.LEVEL_TILE_WIDTH;
		int y = floor(i / mTileMap.LEVEL_TILE_HEIGHT);

		if ((tileMap[i].getType() >= TILE_STATUE))
			mLightPassageMap[x][y] = true;

	}
}

void DungeonRoom::AddGate(int x, int y, int key){
	GatePoint newGate;
	
	newGate.gateX = x;
	newGate.gateY = y;
	newGate.key = key;

	mGatePointList.push_back(newGate);

}

void DungeonRoom::Render(vector< vector<bool> >* playerVision){
	mTileMap.Render(playerVision);
}

void DungeonRoom::AddNPC(Character* newNPC, int x, int y){
	newNPC->SetMapTilePositions(mTileMap.GetMapTilePositions());
	newNPC->SetCollisionMap(&mCollisionMap);
	newNPC->setLightPassableMap(&mLightPassageMap);
	newNPC->SetMapPosition(x,y);
	mNpcList.push_back(newNPC);
}



/////**GETTERS**/////

vector< vector<bool> >* DungeonRoom::getCollisionMapP(){
	return &mCollisionMap;
}

vector< vector<bool> >* DungeonRoom::getLightPassageMapP(){
	return &mLightPassageMap;
}

vector<Character*>* DungeonRoom::getNpcListP(){
	return &mNpcList;
}

vector< vector<SDL_Rect> > DungeonRoom::getRoomTileRects(){
	return mTileMap.GetMapTilePositions();
}