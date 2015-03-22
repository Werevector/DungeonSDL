#include "Utils.h"


//Utils::Utils(void)
//{
//}
//
//
//Utils::~Utils(void)
//{
//}


string Utils::GetApplicationPath()
{
	char buffer[MAX_PATH];
	GetModuleFileName( NULL, buffer, MAX_PATH );

	char *pos = strrchr(buffer, '\\');
	if (pos != NULL) 
	   *pos = '\0';

	string appPath(buffer);
	return appPath;
}

bool Utils::CoordsOutOfBounds(int x, int y){

	if (x < 0 || x > TileMap::LEVEL_TILE_WIDTH-1 || y < 0 || y > TileMap::LEVEL_TILE_HEIGHT-1){
		return true;
	}
	else{
		return false;
	}

}