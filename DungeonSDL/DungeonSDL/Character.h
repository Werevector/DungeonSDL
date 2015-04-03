#pragma once

#include <SDL.h>
#include "Graphics.h"
#include <vector>
#include "ActMessage.h"
#include <iostream>
#include "Utils.h"
#include <cmath>
#include"GameState.h"
//#include "TileMap.h"

using namespace std;

class Character
{
public:
	
	Character(void);
	~Character(void);

	void SetMapPosition(int x, int y);
	void SetMapTilePositions(vector< vector<SDL_Rect> > tilePositions);
	void SetCollisionMap(vector< vector<bool> >*);

	int getmMapX();
	int getmMapY();

	void AddActMessage(actMessage);

	void FlipX();
	void FlipY();

	virtual void Render() = 0;
	virtual void Update(vector<Character*>&) = 0;

	bool IsDead();
	vector< vector<bool> >* getVisionMapP();
	void setLightPassableMap(vector< vector<bool> >*);
	vector <actMessage> message_Queue;

protected:
	
	int mMapX;
	int mMapY;

	int health;
	int strength;

	bool damageTaken;
	bool IS_DEAD;

	/*int mPosX;
	int mPosY;*/

	SDL_Rect mCharacter;
	SDL_Rect mCurrentTile;

	vector< vector<SDL_Rect> > mMapTilePositions;
	vector< vector<bool> >* m_collisionMap;
	vector< vector<bool> >* mLightPassageMap;
	vector< vector<bool> > m_VisionMap;

	void CalcDamage(int);
	void CalcVision();

};
