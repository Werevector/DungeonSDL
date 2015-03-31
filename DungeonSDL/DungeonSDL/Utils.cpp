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

	/*if (x < 0 || x > TileMap::LEVEL_TILE_WIDTH-1 || y < 0 || y > TileMap::LEVEL_TILE_HEIGHT-1){
		return true;
	}
	else{
		return false;
	}*/

	if (x < 0 || x > 8 || y < 0 || y > 8){
	return true;
	}
	else{
	return false;
	}

}

//Bresenham alg, returns the output points
vector<SDL_Point> Utils::Bresenham(int x1, int y1, int const x2, int const y2)
{
	
	vector<SDL_Point> resultVector;
	SDL_Point p;

	int delta_x(x2 - x1);
	// if x1 == x2, then it does not matter what we set here
	signed char const ix((delta_x > 0) - (delta_x < 0));
	delta_x = std::abs(delta_x) << 1;

	int delta_y(y2 - y1);
	// if y1 == y2, then it does not matter what we set here
	signed char const iy((delta_y > 0) - (delta_y < 0));
	delta_y = std::abs(delta_y) << 1;


	//plot(x1, y1);

	if (delta_x >= delta_y)
	{
		// error may go below zero
		int error(delta_y - (delta_x >> 1));

		while (x1 != x2)
		{
			if ((error >= 0) && (error || (ix > 0)))
			{
				error -= delta_x;
				y1 += iy;
			}
			// else do nothing

			error += delta_y;
			x1 += ix;

			//Set point in array
			p.x = x1;
			p.y = y1;
			resultVector.push_back(p);

			//plot(x1, y1);
		}
	}
	else
	{
		// error may go below zero
		int error(delta_x - (delta_y >> 1));

		while (y1 != y2)
		{
			if ((error >= 0) && (error || (iy > 0)))
			{
				error -= delta_y;
				x1 += ix;
			}
			// else do nothing

			error += delta_x;
			y1 += iy;

			//Set point in array
			p.x = x1;
			p.y = y1;
			resultVector.push_back(p);

			//plot(x1, y1);
		}
	}

	return resultVector;

}