#pragma once
//Enum describing message type
enum messageType{

	MOVE_UPP,
	MOVE_DOWN,
	MOVE_LEFT,
	MOVE_RIGHT,

	ACTION_ATTACK,
	ACTION_TAKE_DAMAGE,
	AIM_AND_SHOOT_BOW,

	REACT_TO_ACTION,


	DEFAULT

};

// Message structure containing typecode and message info (TODO: flags ?)
struct actMessage {

	messageType type;
	int intParam = 0;

};

