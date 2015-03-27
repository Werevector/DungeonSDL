#include <vector>
#include <map>
#include <string>
#include "TileMap.h"
#include "Textures.h"

using namespace std;
class DungeonStructure{


public:

	DungeonStructure();
	
	bool LoadStructure(string, Textures);
	
	TileMap* getStart();
	TileMap* getMap(int);

	//Get map from current position
	int getRight();
	int getLeft();
	int getUp();
	int getDown();
	

private:

	//Structure map
	map<int, TileMap*> mapStructure;

	int currentKey;

};