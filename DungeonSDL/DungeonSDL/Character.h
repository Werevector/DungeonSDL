#pragma once
#include <SDL.h>
#include "Graphics.h"
#include <vector>
#include "ActMessage.h"
#include <iostream>
#include "Utils.h"

using namespace std;
class CharacterNonPlayable;

class Character
{
public:
	Character(void);
	~Character(void);

	void SetMapPosition(int x, int y);
	void SetMapTilePositions(vector< vector<SDL_Rect> > tilePositions);
	void SetCollisionMap(vector< vector<bool> >*);

	virtual void Update(vector<CharacterNonPlayable*>&) = 0;
	virtual void Render() = 0;

	int getmMapX();
	int getmMapY();

	void AddActMessage(actMessage);

	bool IsDead();

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

	vector< vector<SDL_Rect> > mMapTilePositions;
	vector< vector<bool> >* c_collisionMap;

	void CalcDamage(int);

};

