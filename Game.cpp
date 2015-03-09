#include "Game.h"
#include "GameplayState.h"

#include <iostream>
#include <time.h>

Game::Game()
{
	window=NULL;
	renderer=NULL;

	screen_width=800;
	screen_height=600;

	old_time=0;
	quit=false;
}

bool Game::Init(GameState* state)
{
	if(SDL_Init(SDL_INIT_EVERYTHING)<0)
	{
		std::cerr <<SDL_GetError() <<std::endl;
		return false;
	}
	window=SDL_CreateWindow("Football RPG",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, SDL_WINDOW_SHOWN);
	if(window==NULL)
	{
		std::cerr <<SDL_GetError() << std::endl;
		return false;
	}

	renderer=SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if(renderer==NULL)
	{
		std::cerr <<SDL_GetError() << std::endl;
		return false;
	}

	srand(time(NULL));
	PushState(state);
	return true;
}

void Game::Thread() //check stackempty and does updating
{
	while(quit==false)
	{
		Update();
		Render();
	}
	Quit();
}

// Update function, checks the stack and updates it

void Game::Update()
{
	//check events queue and go process particular states

	while(SDL_PollEvent(&event))
	{
		if(states.size()>0)
			states.back()->HandleEvents(&event);
	}

	//Check to see if stack is empty asit might stillhold events

	if(states.size()>0)
	{
		old_time = new_time;
		new_time = SDL_GetTicks();

		if(new_time > old_time)
		{
			float deltaTime = (float) (new_time - old_time) / 1000.0f;
			states.back()->Update(deltaTime);
		}
	}
}

// Render function for the SDL stuff

void Game::Render()
{
	// clear buffer back
	SDL_RenderClear(renderer);

	//render onto buffer back
	if(states.size()>0)
		states.back()->Render();

	//switch buffers

	SDL_RenderPresent(renderer);
}

