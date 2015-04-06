

class Node{

public:

	int x, y;

	int H;
	int P;
	bool walkable;

	Node* parent;

	Node(int,int,int, int, bool);

	int GetF();
	void SetParent(Node*);
	Node* GetParent();

};

Node::Node(int X, int Y, int h, int p, bool isWalkable){
	
	x = X;
	y = Y;

	H = h;
	P = p;
	walkable = isWalkable;
}

void Node::SetParent(Node* newParent){
	parent = newParent;
}

Node* Node::GetParent(){
	return parent;
}

int Node::GetF(){
	return H + P;
}
