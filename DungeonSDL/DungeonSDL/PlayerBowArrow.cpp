#include "PlayerBowArrow.h"


PlayerBowArrow::PlayerBowArrow()
{
	mArrowRect.x = 0;
	mArrowRect.y = 0;
	mArrowRect.w = 7;
	mArrowRect.h = 7;

	mPosX = 0;
	mPosY = 0;

	mTargetNPC = 0;

	mForwardSpeed = 500;

	dx = 0;
	dy = 0;

}


PlayerBowArrow::~PlayerBowArrow()
{
}


void PlayerBowArrow::Render()
{
	SDL_SetRenderDrawColor(Graphics::gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderFillRect(Graphics::gRenderer, &mArrowRect);
}


void PlayerBowArrow::Update()
{

	int dx = cosf(mAngle) * mForwardSpeed*GAME_FRAMEDELTA;
	int dy = -sinf(mAngle) * mForwardSpeed*GAME_FRAMEDELTA;

	mPosX += dx;
	mPosY += dy;

	SetPosition(mPosX, mPosY);
}


void PlayerBowArrow::SetPosition(int x, int y)
{

	//mPosX = x;
	//mPosY = y;

	Projectile::SetPosition(x, y);
	mArrowRect.x = x;// - mArrowRect.w / 2;
	mArrowRect.y = y;// -mArrowRect.h / 2;
	mArrowRect.x += WINDOW_CENTER_OFFSET_X;
	mArrowRect.y += WINDOW_CENTER_OFFSET_Y;

}


void PlayerBowArrow::SetTarget(Character* targetNPC)
{
	mTargetNPC = targetNPC;
}


void PlayerBowArrow::CalculateTravelAngle()
{
	int x1 = mPosX;
	int y1 = mPosY;
	int x2 = mTargetNPC->GetPositionX();
	int y2 = mTargetNPC->GetPositionY();

	int cx = x2 - x1;
	int cy = y2 - y1;

	mAngle = -atan2f(cy, cx);

	//mAngle = 2.35619449f;

	//mAngle = atan2(y1 - y2, x1 - x2);

	//mAngle = mAngle * 180 / M_PI;


	//int dot = x1*x2 + y1*y2;      //# dot product
	//int det = x1*y2 - y1*x2;     //# determinant
	//mAngle = atan2(det, dot);  //# atan2(y, x) or atan2(sin, cos)

	//mAngle = 0.785398163f;
	//int a = mAngle * 180 / M_PI;
	//Point p1;
	//p1.x = x1;
	//p1.y = y1;

	//Point p2;
	//p2.x = x2;
	//p2.y = y2;

	//mAngle = angleBetween(p1, p2);
}


float PlayerBowArrow::angleBetween(Point v1, Point v2)
{
	float len1 = sqrt(v1.x * v1.x + v1.y * v1.y);
	float len2 = sqrt(v2.x * v2.x + v2.y * v2.y);

	float dot = v1.x * v2.x + v1.y * v2.y;

	float a = dot / (len1 * len2);

	if (a >= 1.0)
		return 0.0;
	else if (a <= -1.0)
		return M_PI;
	else
		return acos(a); // 0..PI
}