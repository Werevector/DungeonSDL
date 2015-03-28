#pragma once
enum State{

	GAME_OVER,
	RUNNING,
	MENU

};

extern State g_gameState;

enum loadDirection{

	UP,DOWN,LEFT,RIGHT,OFF

};

extern loadDirection lDir;

//Flags
extern bool MAP_SWITCH;