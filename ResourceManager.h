#ifndef RESOURCE_MANAGER.H
#define RESOURCE_MANAGER.H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include <iterator>
#include <map>
#include <string>

class Game;

class ResourceManager
{
private:

	std::map<std::string, SDL_Texture*> textures;


	Game* game;

public:

	ResourceManager(Game* game);

	~ResourceManager();

};



#endif