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
extern bool FULL_SCREEN;

//Stats
extern int WINDOW_HEIGHT;
extern int WINDOW_WIDTH;
extern int WINDOW_CENTER_OFFSET_X;
extern int WINDOW_CENTER_OFFSET_Y;
//extern double GAME_FPS;
//extern double GAME_FRAME_TIME;