#pragma once
#include "Texture.h"
#include "Utils.h"
#include <vector>

using namespace std;

class Textures
{
public:

	enum loaded_textures 
	{
		DUNGEON_MAP_TEST_16,
		DUNGEON_MAP_TEST_32
	};

	Textures(void);
	~Textures(void);

	bool LoadTextures();

	Texture* GetTexture(int texture);

private:

	Texture* LoadTexture(string path);
	vector<Texture*> mTextures;
	bool mSuccess;

};

