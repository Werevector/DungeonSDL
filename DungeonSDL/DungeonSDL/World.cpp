#include "World.h"


World::World(void)
{
}


World::~World(void)
{
}


void World::SetDungeonMap(TileMap* map){

	mDungeonMap = map;
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
		(*character)->Update();
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

	for (int i = 0; i < mNonPlayableCharacters.size(); i++)
		mNonPlayableCharacters[i]->ReactToPlayerAction(mCharacters);

}