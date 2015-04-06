#pragma once
#include "Node.h"
#include <list>
#include <vector>
#include "SDL.h"

using namespace std;

class Astar{

public:

	list<Node> findAStarPath(vector<vector<Node>>, SDL_Point, SDL_Point ){

	}

private:

	Node current;

	list<Node> open;
	list<Node> closed;


};

list<Node> Astar::findAStarPath(vector<vector<Node>> nodeArray, SDL_Point origin, SDL_Point target ){

	Node start(origin.x, origin.y, 0 , 0, true);
	




}