#include "GameState.h"

State g_gameState = RUNNING;

loadDirection lDir = OFF;

bool MAP_SWITCH = false;
bool FULL_SCREEN = false;

int WINDOW_HEIGHT = 800;
int WINDOW_WIDTH = 1000;
int WINDOW_CENTER_OFFSET_X = 0;
int WINDOW_CENTER_OFFSET_Y = 0;
double GAME_FPS = 0.0;
double GAME_FRAME_TIME = 0.0;