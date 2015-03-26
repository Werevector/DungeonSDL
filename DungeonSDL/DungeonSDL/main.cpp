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

using namespace std;

Textures gTileTextures;
Texture gtex;
GameTimer gTimer;
World *gWorld;
SDL_Event gEvent;
//vector<Tile> *gTileSet;

float keyTime = 0;
const float keyDelay = 0.12;


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
	return success;

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
int sum = 0;
void Update(const Uint8* keystate, SDL_Event gEvent)
{
	
	actMessage actorMessage;

	if(keystate[SDL_SCANCODE_UP])
	{
		if (!(keyTime > 0))
		{
			actorMessage.type = messageType::MOVE_UPP;
			gWorld->DelegateMSG(actorMessage);
			keyTime = keyDelay;
		}
	}
	
	if(keystate[SDL_SCANCODE_DOWN])
	{
		if (!(keyTime > 0))
		{
			actorMessage.type = messageType::MOVE_DOWN;
			gWorld->DelegateMSG(actorMessage);
			keyTime = keyDelay;
		}
	}
	
	if(keystate[SDL_SCANCODE_LEFT])
	{
		if (!(keyTime > 0)){
			actorMessage.type = messageType::MOVE_LEFT;
			gWorld->DelegateMSG(actorMessage);
			keyTime = keyDelay;
		}
	}

	if(keystate[SDL_SCANCODE_RIGHT])
	{
		if (!(keyTime > 0))
		{
			actorMessage.type = messageType::MOVE_RIGHT;
			gWorld->DelegateMSG(actorMessage);
			keyTime = keyDelay;
		}
	}

	if (keyTime > 0){
		keyTime -= gTimer.DeltaTime();
		sum++;
	}
	else if (keyTime < 0){
		keyTime = 0;
		sum = 0;
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

		TileMap* tileMap;
		tileMap = new TileMap();
		tileMap->SetTileTexture(*gTileTextures.GetTexture(Textures::DUNGEON_MAP_TEST_32));
		tileMap->LoadAndBuildTileMap(Utils::GetApplicationPath());
		gWorld->SetDungeonMap(tileMap);

		CharacterPlayable* hero;
		hero = new CharacterPlayable();
		hero->SetMapTilePositions(tileMap->GetMapTilePositions());
		hero->SetMapPosition(8, 2);
		gWorld->AddWorldCharacter(hero);

		CharacterNonPlayable* enemy;
		enemy = new CharacterNonPlayable();
		enemy->SetMapTilePositions(tileMap->GetMapTilePositions());
		enemy->SetMapPosition(2, 6);
		gWorld->AddWorldNPCharacter(enemy);

		CharacterNonPlayable* enemy2;
		enemy2 = new CharacterNonPlayable();
		enemy2->SetMapTilePositions(tileMap->GetMapTilePositions());
		enemy2->SetMapPosition(3, 7);
		gWorld->AddWorldNPCharacter(enemy2);

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

			/*if (SDL_QuitRequested()){
				quit = true;
				continue;
			}*/

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