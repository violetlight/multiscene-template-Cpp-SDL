#ifndef TOOLS_H
#define TOOLS_H

#include <sdl2/SDL.h>
#include <sdl2/SDL_image.h>
#include <sdl2/SDL_mixer.h>
#include <string>
#include <map>
#include "sprite.h"


namespace Tools {
  bool loadGraphics(std::map<std::string, SDL_Texture*>& map);
  bool loadMusic(std::map<std::string, Mix_Music*>& map);
}

#endif
