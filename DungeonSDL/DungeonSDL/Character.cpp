#include "Character.h"


Character::Character(void)
{
	mCharacter.x = 0;
	mCharacter.y = 0;
	mCharacter.w = 15;
	mCharacter.h = 15;

	mMapX = 0;
	mMapY = 0;
	mPosX = 0;
	mPosY = 0;

	mHealth = 5;
	mHealthMax = 10;

	IS_DEAD = false;

	m_VisionMap = vector<std::vector<bool>>(9, std::vector<bool>(9));

	/*mPosX = 0;
	mPosY= 0;*/

}


Character::~Character(void)
{

}


void Character::SetMapPosition(int x, int y)
{
	mMapX = x;
	mMapY = y;

	if(!mMapTilePositions.empty())
	{
		mCurrentTile = mMapTilePositions[x][y];

		mPosX = mCurrentTile.x;
		mPosY = mCurrentTile.y;
		//mPosX += WINDOW_CENTER_OFFSET_X;
		//mPosY += WINDOW_CENTER_OFFSET_Y;

		mCharacter.x = mCurrentTile.x;// -mCharacter.w / 2;
		mCharacter.y = mCurrentTile.y;// -mCharacter.h / 2;
		mCharacter.x += WINDOW_CENTER_OFFSET_X;
		mCharacter.y += WINDOW_CENTER_OFFSET_Y;

	}
}


void Character::SetMapTilePositions(vector< vector<SDL_Rect> > tilePositions)
{
	mMapTilePositions = tilePositions;
}


void Character::SetCollisionMap(vector< vector<bool> >* collMap){
	m_collisionMap = collMap;
}


void Character::setLightPassableMap(vector< vector<bool> >* lightMap){
	mLightPassageMap = lightMap;
	m_VisionMap = vector<std::vector<bool>>(lightMap->size(), std::vector<bool>(lightMap->size()));
	CalcVision();
}


void Character::CalcVision(){

	vector<SDL_Point> VisionPoints;
	bool hasVision;

	for (int x = 0; x < m_collisionMap->size(); x++){
		for (int y = 0; y < m_collisionMap->size(); y++){

			//Assume that tile is visible
			hasVision = true;

			//Get line points from Bresenham
			VisionPoints = Utils::Bresenham(x,y,mMapX,mMapY);
			
			//Check if wall(Light cannot pass) is in the way 
			for (int i = 0; i < VisionPoints.size(); i++){
				if ((*mLightPassageMap)[VisionPoints[i].x][VisionPoints[i].y]){
					hasVision = false;
				}
			}

			m_VisionMap[x][y] = hasVision;

		}
	}

}


vector< vector<bool> >* Character::getVisionMapP(){
	return &m_VisionMap;
}


void Character::FlipX(){
	mMapX = abs( mMapX - 9 + 1 );
}


void Character::FlipY(){
	mMapY = abs( mMapY - 9 + 1 );
}


void Character::CalcDamage(int damage){
	mHealth -= damage;
	if (mHealth < 0){
		IS_DEAD = true;
	}
}


void Character::AddActMessage(actMessage new_msg)
{
	message_Queue.push_back(new_msg);
}


bool Character::IsDead(){
	return IS_DEAD;
}


int Character::GetMapPositionX()
{
	return mMapX;
}


int Character::GetMapPositionY()
{
	return mMapY;
}


int Character::GetPositionX()
{
	return mPosX;
}


int Character::GetPositionY()
{
	return mPosY;
}


int Character::GetHealth()
{
	return mHealth;
}


int Character::GetHealthMax()
{
	return mHealthMax;
}



