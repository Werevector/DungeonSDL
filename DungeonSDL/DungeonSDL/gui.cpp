#include "gui.h"


Gui::Gui(TTF_Font *font, GameTimer* timer)
{
	//mGameInfoRect.x = 50;
	//mGameInfoRect.y = 200;
	//mGameInfoRect.w = 100;
	//mGameInfoRect.h = 100;

	mFont = font;

	mFrameSpacing = 150;

	mTimer = timer;

	mFps = 0;
	mMspf = 0;

	mSidebar_X_TextOffset = 5;
	mSidebar_Y_TextOffset = 20;

	mTextColor = { 255, 255, 255 };

	mPlayerHealthBar_X_offset = 400;
	mPlayerHealthBar_Y_offset = WINDOW_HEIGHT - 120;
	mPlayerHealthBar_Width = 120;
	mPlayerHealthBar_Height = 25;

	mPlayerX = 0;
	mPlayerY = 0;
	mPlayerHealth = 0;

}


Gui::~Gui()
{
}

void Gui::UpdateFrameStats()
{
	Utils::CalculateFrameStats(*mTimer, mFps, mMspf);
}

void Gui::Render()
{

	Render_GUI_Borders();
	RenderSidebarText();
	RenderPlayerHealthBar();

}


void Gui::RenderPlayerHealthBar()
{
	
	SDL_Rect playerHeathBarFrame = { mPlayerHealthBar_X_offset, 
								     mPlayerHealthBar_Y_offset, 
									 mPlayerHealthBar_Width, 
									 mPlayerHealthBar_Height };

	SDL_Rect playerHeathBarRect = { mPlayerHealthBar_X_offset + 1, 
									mPlayerHealthBar_Y_offset + 1, 
									mPlayerHealthBar_Width - 2, 
									mPlayerHealthBar_Height - 2 };

	SDL_SetRenderDrawColor(Graphics::gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderDrawRect(Graphics::gRenderer, &playerHeathBarFrame);

	SDL_SetRenderDrawColor(Graphics::gRenderer, 0xFF, 0x00, 0x00, 0xFF);
	SDL_RenderFillRect(Graphics::gRenderer, &playerHeathBarRect);

}


void Gui::Render_GUI_Borders()
{

	SDL_SetRenderDrawColor(Graphics::gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderDrawLine(Graphics::gRenderer, mFrameSpacing, 0, mFrameSpacing, WINDOW_HEIGHT - mFrameSpacing);
	SDL_RenderDrawLine(Graphics::gRenderer, mFrameSpacing, WINDOW_HEIGHT - mFrameSpacing, WINDOW_WIDTH, WINDOW_HEIGHT - mFrameSpacing);

}


void Gui::RenderSidebarText()
{

	Texture gTextTexture;
	gTextTexture.loadFromRenderedText("FrameTime: " + std::to_string((int)mMspf), mTextColor, mFont);
	gTextTexture.render(mSidebar_X_TextOffset, mSidebar_Y_TextOffset);

	gTextTexture.loadFromRenderedText("FPS: " + std::to_string((int)mFps), mTextColor, mFont);
	gTextTexture.render(mSidebar_X_TextOffset, mSidebar_Y_TextOffset + 20);

	gTextTexture.free();
}


void Gui::SetPlayerData(int playerX, int playerY, int playerHealth)
{
	mPlayerX = playerX;
	mPlayerY = playerY;
	mPlayerHealth = playerHealth;
}
