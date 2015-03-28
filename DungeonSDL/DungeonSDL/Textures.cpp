#include "Textures.h"


Textures::Textures(void)
{
	mSuccess = false;
}


Textures::~Textures(void)
{
	//Free loaded images
	//gLanderTexture.free();
}


Texture* Textures::GetTexture(int texture)
{
	return mTextures[texture];
}


bool Textures::LoadTextures()
{

	string appPath = Utils::GetApplicationPath();
	appPath += "\\assets\\";

	mTextures.push_back(LoadTexture(appPath + "texture_atlas1.png"));
	mTextures.push_back(LoadTexture(appPath + "SpartanSet.png"));

	return mSuccess;
}


Texture* Textures::LoadTexture(string path)
{
	Texture* mapTilesTexture;
	mapTilesTexture = new Texture();
	if( !mapTilesTexture->loadFromFile(path) )
		mSuccess = false;

	return mapTilesTexture;
}
