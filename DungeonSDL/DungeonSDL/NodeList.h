#pragma once
#include <vector>
#include "Node.h"

using namespace std;

class NodeList{

public:

	void insert(Node);


private:
	

	void sort();
	vector<Node> internalList;

};