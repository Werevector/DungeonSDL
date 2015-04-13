#pragma once

#include "Projectile.h"
#include <math.h> 

using namespace std;

class PlayerBowArrow
	: public Projectile
{
public:

	struct Point{
		int x;
		int y;
	};

	PlayerBowArrow();
	~PlayerBowArrow();

	void Render();
	void Update();

	void SetPosition(int x, int y);
	void SetTarget(Character*);
	void CalculateTravelAngle();

private:

	SDL_Rect mArrowRect;
	Character* mTargetNPC;
	int mForwardSpeed;

	int dx;
	int dy;

	float angleBetween(Point v1, Point v2);

};

