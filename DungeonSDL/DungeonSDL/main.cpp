#pragma once
#include <SDL.h>
//#include <SDL_image.h>
#include <SDL_ttf.h>

#include <stdio.h>
#include <string>
#include <iostream>
//#include <windows.h>
#include <vector>
#include <chrono>

#include "GameTimer.h"
#include "Textures.h"
#include "Graphics.h"
#include "TileMap.h"
#include "Utils.h"
#include "World.h"
#include "CharacterPlayable.h"
#include "CharacterNonPlayable.h"
#include "ActMessage.h"

#include "GameState.h"
#include "gui.h"

using namespace std;

Textures gTileTextures;
Texture gtex;

GameTimer gTimer;
Gui *gGui;
World *gWorld;


SDL_Event gEvent;

TTF_Font *gFont = NULL;
int gFontSize = 15;

//SDL_Rect gWindowRect;
//SDL_Rect gGameInfoRect;

float keyTime = 0;
const float keyDelay = 0.12;
bool keyPressed = false;


bool Init()
{
	//Initialization flag
	bool success = true;

	SDL_Init( SDL_INIT_VIDEO );
	Graphics::gWindow = SDL_CreateWindow("DungeonCrawler", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	Graphics::gRenderer = SDL_CreateRenderer( Graphics::gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
	SDL_SetRenderDrawColor( Graphics::gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "best" );

	TTF_Init();

	//SDL_GetWindowSize(Graphics::gWindow, &gWindowRect.w, &gWindowRect.h);

	//gGameInfoRect.x = 50;
	//gGameInfoRect.y = gWindowRect.h - 200;
	//gGameInfoRect.w = gWindowRect.w - 100;
	//gGameInfoRect.h = 100;
	

	return success;
}

bool loadMedia()
{
	bool success = gTileTextures.LoadTextures();
	
	string fontPath = Utils::GetApplicationPath() + "\\infoFont.ttf";

	gFont = TTF_OpenFont(fontPath.c_str(), gFontSize);
	if (gFont == NULL)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}

	return true;

}

void close()
{
	//Free loaded images
	//gLanderTexture.free();
	gWorld->~World();
	gTileTextures.~Textures();

	TTF_CloseFont(gFont);

	//Destroy window	
	SDL_DestroyRenderer( Graphics::gRenderer );
	SDL_DestroyWindow( Graphics::gWindow );
	Graphics::gWindow = NULL;
	Graphics::gRenderer = NULL;

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}


void Update_WorldData_To_GUI()
{
	int playerX;
	int playerY;
	int playerHealth;
	gWorld->GetPlayerData(playerX, playerY, playerHealth);
	gGui->SetPlayerData(playerX, playerY, playerHealth);
}


void Update(const Uint8* keystate, SDL_Event gEvent)
{
	
	actMessage actorMessage;

	keyPressed = false;

	if(keystate[SDL_SCANCODE_UP])
	{
		if (!(keyTime > 0))
		{
			actorMessage.type = messageType::MOVE_UPP;
			gWorld->DelegateMSG(actorMessage);
			keyPressed = true;
		}
	}
	
	if(keystate[SDL_SCANCODE_DOWN])
	{
		if (!(keyTime > 0))
		{
			actorMessage.type = messageType::MOVE_DOWN;
			gWorld->DelegateMSG(actorMessage);
			keyPressed = true;
		}
	}
	
	if(keystate[SDL_SCANCODE_LEFT])
	{
		if (!(keyTime > 0)){
			actorMessage.type = messageType::MOVE_LEFT;
			gWorld->DelegateMSG(actorMessage);
			keyPressed = true;
		}
	}

	if(keystate[SDL_SCANCODE_RIGHT])
	{
		if (!(keyTime > 0))
		{
			actorMessage.type = messageType::MOVE_RIGHT;
			gWorld->DelegateMSG(actorMessage);
			keyPressed = true;
		}
	}

	if (keyPressed){
		keyTime = keyDelay;
		Update_WorldData_To_GUI();
	}

	if (keyTime > 0)
		keyTime -= gTimer.DeltaTime();
	else if (keyTime < 0)
		keyTime = 0;

	gWorld->Update();

	gGui->UpdateFrameStats();

}

int main( int argc, char* args[] )
{

	gTimer.Reset();

	if( !Init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{

		loadMedia();

		gGui = new Gui(gFont, &gTimer);
		gWorld = new World();	
		

		/***************************
		Manual object init for testing
		****************************/

		gWorld->LoadDungeon("dummy");

		/***************************
		****************************/


		bool quit = false;
		while( !quit )
		{
			while (SDL_PollEvent(&gEvent) != 0){
				if (gEvent.type == SDL_QUIT){
					quit = true;
				}

				if (gEvent.key.keysym.sym == SDLK_ESCAPE){
					quit = true;
				}

				if (gEvent.window.event == SDL_WINDOWEVENT_RESIZED){
					//WINDOW_WIDTH = gEvent.window.data1;
					//WINDOW_HEIGHT = gEvent.window.data2;

					//SDL_GetWindowSize(Graphics::gWindow, &gWindowRect.w, &gWindowRect.h);

					//gGameInfoRect.x = 50;
					//gGameInfoRect.y = gWindowRect.h - 200;
					//gGameInfoRect.w = gWindowRect.w - 100;
					//gGameInfoRect.h = 100;

				}
			}//EventWhile


			auto t_start = std::chrono::high_resolution_clock::now();
			
			const Uint8* keystate = SDL_GetKeyboardState(NULL);

			gTimer.Tick();

			Update(keystate, gEvent);

			SDL_SetRenderDrawColor( Graphics::gRenderer, 0x00, 0x00, 0x00, 0xFF );
			SDL_RenderClear( Graphics::gRenderer );
			
			gWorld->Render();
			gGui->Render();

			SDL_RenderPresent( Graphics::gRenderer );
							
		}
	}

	close();
	return 0;
}