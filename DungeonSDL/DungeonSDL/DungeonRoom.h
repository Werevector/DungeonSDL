#pragma once
#include "TileMap.h"
#include <vector>
#include <list>
#include "TileTypeCodes.h"

#define RoomTileHeight 9
#define RoomTileWidth 9

struct GatePoint{

	int gateX;
	int gateY;
	int key;

};

class DungeonRoom{
	

public:

	DungeonRoom();

	void Render(vector< vector<bool> >*);

	void AddNPC(Character*, int, int);

	void BuildRoom(string path);

	void AddGate(int, int, int);

	vector< vector<bool> >* getCollisionMapP();
	vector< vector<bool> >* getLightPassageMapP();
	vector<Character*>* getNpcListP();
	vector< vector<SDL_Rect> > getRoomTileRects();

	int right;
	int left;
	int up;
	int down;

private:

	TileMap mTileMap;

	void BuildCollisionMap(vector<Tile>);
	void BuildLightPassageMap(vector<Tile>);

	vector< vector<SDL_Rect> > mTilePostions;
	vector< vector<bool> > mCollisionMap;
	vector< vector<bool> > mLightPassageMap;
	vector<GatePoint> mGatePointList;
	
	vector<Character*> mNpcList;

};