#ifndef TOOLS_H
#define TOOLS_H

#include <sdl2/SDL.h>
#include <sdl2/SDL_image.h>
#include <string>
#include <map>

//Loads individual image
SDL_Texture* loadTexture(std::string path);

//work in progress
bool loadGraphics(std::map<std::string, SDL_Texture*> map);

#endif
