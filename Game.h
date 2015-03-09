#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include<vector>

class GameState;

class Game
{
private:
	SDL_Window*window;
	SDL_Renderer* renderer;
	SDL_Event event;

	int screen_width;
	int screen_height;

	bool quit;

	std::vector<GameState*>states;

	Uint32 new_time;
	Uint32 old_time;

public:
	Game();

	bool Init(GameState* state);

	void Thread();

private:

	void Update();
	void Render();

	void Quit();

public:
	void PushState(GameState* state);
	void PopState();
	void setQuit();

	SDL_Renderer* getRenderer();
};




#endif