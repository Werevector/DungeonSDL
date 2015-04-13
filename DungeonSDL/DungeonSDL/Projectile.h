#pragma once

#include <SDL.h>
#include "Graphics.h"
#include"GameState.h"
#include "Character.h"

class Projectile
{
public:
	Projectile();
	~Projectile();

	virtual void Render() = 0;
	virtual void Update() = 0;

	void Move(int, int);

	void SetPosition(int x, int y);

protected:

	int mPosX;
	int mPosY;
	float mVelocX;
	float mVelocY;

	float mAngle;

};

