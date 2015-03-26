#pragma once
#include <SDL.h>
#include "Graphics.h"
#include <vector>
#include "ActMessage.h"
#include <iostream>
#include "Utils.h"

using namespace std;

class Character
{
public:
	Character(void);
	~Character(void);

	void SetMapPosition(int x, int y);
	void SetMapTilePositions(vector< vector<SDL_Rect> > tilePositions);
	void SetCollisionMap(vector< vector<bool> >*);

	virtual void Update() = 0;
	virtual void Render() = 0;

	SDL_Rect Get_CurrentTile();

protected:
	
	int mMapX;
	int mMapY;

	/*int mPosX;
	int mPosY;*/

	SDL_Rect mCharacter;
	SDL_Rect mCurrentTile;

	vector< vector<SDL_Rect> > mMapTilePositions;
	vector< vector<bool> >* c_collisionMap;
};

