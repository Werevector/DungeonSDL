#include "World.h"


World::World()
{

	gTileTextures.LoadTextures();
	mNonPlayableCharacters = new vector < Character* > ;

}


World::~World(void)
{
}


void World::SetDungeonRoom(DungeonRoom* room){

	mCurrentRoom = room;
	mCharacters[0]->SetCollisionMap(mCurrentRoom->getCollisionMapP());
	mCharacters[0]->setLightPassableMap(mCurrentRoom->getLightPassageMapP());
}

bool World::LoadDungeon(string dungeonPath){
	
	mDungeon.LoadStructure(dungeonPath, gTileTextures);

	mCurrentRoom = mDungeon.getStart();
	mNonPlayableCharacters = mCurrentRoom->getNpcListP();

	CharacterPlayable* hero;
	hero = new CharacterPlayable();
	hero->SetMapTilePositions(mCurrentRoom->getRoomTileRects());
	hero->SetMapPosition(3, 2);
	AddWorldCharacter(hero);

	return true;

}


void World::AddWorldCharacter(Character* character)
{
	character->SetCollisionMap(mCurrentRoom->getCollisionMapP());
	character->setLightPassableMap(mCurrentRoom->getLightPassageMapP());
	mCharacters.push_back(character);
}


void World::AddWorldNPCharacter(Character* character)
{
	mNonPlayableCharacters->push_back(character);
}


void World::Update()
{
	for (auto character = mCharacters.begin(); character != mCharacters.end(); ++character){
		(*character)->Update(*mNonPlayableCharacters);
	}

	for (auto character = mNonPlayableCharacters->begin(); character != mNonPlayableCharacters->end(); ++character){
		(*character)->Update(mCharacters);
	}

	//TODO Jan: Testing persistent dead bodies
	for (int i = 0; i < mNonPlayableCharacters->size(); i++){

		if ((*mNonPlayableCharacters)[i]->IsDead()){
			mNonPlayableCharacters->erase(mNonPlayableCharacters->begin() + i);
		}

	}

	if (MAP_SWITCH){

		switch (lDir){

		case UP:
			SetDungeonRoom(mDungeon.getMap(mCurrentRoom->up));
			mCharacters[0]->SetMapTilePositions(mCurrentRoom->getRoomTileRects());
			mCharacters[0]->FlipY();
			mNonPlayableCharacters = mCurrentRoom->getNpcListP();
			MAP_SWITCH = false;
			break;
		case DOWN:
			SetDungeonRoom(mDungeon.getMap(mCurrentRoom->down));
			mCharacters[0]->SetMapTilePositions(mCurrentRoom->getRoomTileRects());
			mCharacters[0]->FlipY();
			mNonPlayableCharacters = mCurrentRoom->getNpcListP();
			MAP_SWITCH = false;
			break;
		case LEFT:
			SetDungeonRoom(mDungeon.getMap(mCurrentRoom->left));
			mCharacters[0]->SetMapTilePositions(mCurrentRoom->getRoomTileRects());
			mCharacters[0]->FlipX();
			mNonPlayableCharacters = mCurrentRoom->getNpcListP();
			MAP_SWITCH = false;
			break;
		case RIGHT:
			SetDungeonRoom(mDungeon.getMap(mCurrentRoom->right));
			mCharacters[0]->SetMapTilePositions(mCurrentRoom->getRoomTileRects());
			mCharacters[0]->FlipX();
			mNonPlayableCharacters = mCurrentRoom->getNpcListP();
			MAP_SWITCH = false;
			break;
		default:
			break;

		}

	}


}


void World::Render()
{

	vector< vector<bool> >* playerVision = mCharacters[0]->getVisionMapP();
	mCurrentRoom->Render(playerVision);

	for(int i = 0; i < mCharacters.size(); i++)
		mCharacters[i]->Render();

	for (int i = 0; i < mNonPlayableCharacters->size(); i++){
		
		bool isVisible = (*playerVision)[(*mNonPlayableCharacters)[i]->GetMapPositionX()][(*mNonPlayableCharacters)[i]->GetMapPositionY()];
		
		if (isVisible)
		{
			(*mNonPlayableCharacters)[i]->Render();
		}
	}
}

//Character* World::getCharP(){
//	return mCharacters[0];
//}

void World::DelegateMSG(actMessage message){

	mCharacters[0]->AddActMessage(message);

	if (message.type == messageType::MOVE_DOWN || message.type == messageType::MOVE_UPP || message.type == messageType::MOVE_LEFT || message.type == messageType::MOVE_RIGHT)
	{
		actMessage actorMessage;
		actorMessage.type = messageType::REACT_TO_ACTION;
		for (int i = 0; i < mNonPlayableCharacters->size(); i++)
			(*mNonPlayableCharacters)[i]->AddActMessage(actorMessage);
	}

}


void World::GetPlayerData(int &playerX, int &playerY, int &health, int &healthMax)
{
	if (mCharacters.size() != 0)
	{
		playerX = mCharacters[0]->GetMapPositionX();
		playerY = mCharacters[0]->GetMapPositionX();
		health = mCharacters[0]->GetHealth();
		healthMax = mCharacters[0]->GetHealthMax();
	}
}