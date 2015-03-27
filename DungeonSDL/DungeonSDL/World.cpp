#include "World.h"


World::World(void)
{

	gTileTextures.LoadTextures();

}


World::~World(void)
{
}


void World::SetDungeonMap(TileMap* map){

	mDungeonMap = map;
}

bool World::LoadDungeon(string dungeonPath){
	mDungeon.LoadStructure(dungeonPath, gTileTextures);
	mDungeonMap = mDungeon.getStart();

	CharacterPlayable* hero;
	hero = new CharacterPlayable();
	hero->SetMapTilePositions(mDungeonMap->GetMapTilePositions());
	hero->SetMapPosition(8, 2);
	AddWorldCharacter(hero);

	CharacterNonPlayable* enemy;
	enemy = new CharacterNonPlayable();
	enemy->SetMapTilePositions(mDungeonMap->GetMapTilePositions());
	enemy->SetMapPosition(2, 6);
	AddWorldNPCharacter(enemy);

	CharacterNonPlayable* enemy2;
	enemy2 = new CharacterNonPlayable();
	enemy2->SetMapTilePositions(mDungeonMap->GetMapTilePositions());
	enemy2->SetMapPosition(3, 7);
	AddWorldNPCharacter(enemy2);

}


void World::AddWorldCharacter(CharacterPlayable* character)
{
	character->SetCollisionMap(mDungeonMap->getCollisionMapP());
	mCharacters.push_back(character);
}


void World::AddWorldNPCharacter(CharacterNonPlayable* character)
{
	mNonPlayableCharacters.push_back(character);
}


void World::Update()
{
	for (vector<CharacterPlayable*>::iterator character = mCharacters.begin(); character != mCharacters.end(); ++character){
		(*character)->Update(mNonPlayableCharacters);
	}

	for (auto character = mNonPlayableCharacters.begin(); character != mNonPlayableCharacters.end(); ++character){
		(*character)->Update(mCharacters);
	}

	for (int i = 0; i < mNonPlayableCharacters.size(); i++){

		if (mNonPlayableCharacters[i]->IsDead()){
			mNonPlayableCharacters.erase(mNonPlayableCharacters.begin() + i);
		}

	}


}


void World::Render()
{
	mDungeonMap->Render();

	for(int i = 0; i < mCharacters.size(); i++)
		mCharacters[i]->Render();

	for (int i = 0; i < mNonPlayableCharacters.size(); i++)
		mNonPlayableCharacters[i]->Render();
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
		for (int i = 0; i < mNonPlayableCharacters.size(); i++)
			mNonPlayableCharacters[i]->AddActMessage(actorMessage);
	}

}