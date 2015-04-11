#pragma once
#include <SDL.h>
#include "Graphics.h"
#include <SDL_ttf.h>
#include <string>
#include "Texture.h"
#include "GameState.h"
#include "GameTimer.h"
#include "Utils.h"

class Gui
{
public:
	Gui(TTF_Font *font, GameTimer* timer);
	~Gui();

	void SetPlayerData(int playerX, int playerY, int playerHealth, int playerHealthMax);

	void UpdateFrameStats();
	void Render();

private:

	void RenderSidebarText();
	void Render_GUI_Borders();
	void RenderPlayerHealthBar();

	//SDL_Rect mGameInfoRect;
	TTF_Font *mFont;

	int mFrameSpacing;

	GameTimer* mTimer;
	float mFps;
	float mMspf;

	int mSidebar_X_TextOffset;
	int mSidebar_Y_TextOffset;

	int mPlayerHealthBar_X_offset;
	int mPlayerHealthBar_Y_offset;
	int mPlayerHealthBar_Width;
	int mPlayerHealthBar_Height;

	int mPlayerX;
	int mPlayerY;
	int mPlayerHealth;
	int mPlayerHealthPercent;
	int mPlayerHealthMax;

	SDL_Color mTextColor;

};

