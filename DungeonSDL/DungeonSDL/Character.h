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

	void Update();

	vector <actMessage> message_Queue;

	void Render();

	void AddActMessage(actMessage);

private:
	
	int mMapX;
	int mMapY;

	int mPosX;
	int mPosY;

	SDL_Rect mCharacter;

	vector< vector<SDL_Rect> > mMapTilePositions;
};

