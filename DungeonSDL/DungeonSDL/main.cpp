#pragma once
#include <SDL.h>
//#include <SDL_image.h>

#include <stdio.h>
#include <string>
#include <iostream>
//#include <windows.h>
#include <vector>

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

using namespace std;

Textures gTileTextures;
Texture gtex;
GameTimer gTimer;
World *gWorld;
SDL_Event gEvent;
//vector<Tile> *gTileSet;

float keyTime = 0;
const float keyDelay = 0.12;
bool keyPressed = false;


bool initSDL()
{
	//Initialization flag
	bool success = true;

	SDL_Init( SDL_INIT_VIDEO );
	Graphics::gWindow = SDL_CreateWindow( "DungeonCrawler", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Graphics::SCREEN_WIDTH, Graphics::SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
	Graphics::gRenderer = SDL_CreateRenderer( Graphics::gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
	SDL_SetRenderDrawColor( Graphics::gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "best" );

	

	return success;
}

bool loadMedia()
{
	bool success = gTileTextures.LoadTextures();
	return true;

}

void close()
{
	//Free loaded images
	//gLanderTexture.free();
	gWorld->~World();
	gTileTextures.~Textures();

	//Destroy window	
	SDL_DestroyRenderer( Graphics::gRenderer );
	SDL_DestroyWindow( Graphics::gWindow );
	Graphics::gWindow = NULL;
	Graphics::gRenderer = NULL;


	IMG_Quit();
	SDL_Quit();
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
	}

	if (keyTime > 0){
		keyTime -= gTimer.DeltaTime();
		
	}
	else if (keyTime < 0){
		keyTime = 0;
	}

	gWorld->Update();

}

int main( int argc, char* args[] )
{

	gTimer.Reset();

	if( !initSDL() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{

		loadMedia();

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
			}//EventWhile



			const Uint8* keystate = SDL_GetKeyboardState(NULL);

			gTimer.Tick();

			Update(keystate, gEvent);

			SDL_SetRenderDrawColor( Graphics::gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
			SDL_RenderClear( Graphics::gRenderer );
				
			gWorld->Render();

			SDL_RenderPresent( Graphics::gRenderer );
			
		}
	}

	close();
	return 0;
}