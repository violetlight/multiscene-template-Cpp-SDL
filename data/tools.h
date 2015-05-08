#ifndef TOOLS_H
#define TOOLS_H

#include <sdl2/SDL.h>
#include <sdl2/SDL_image.h>
#include <sdl2/SDL_mixer.h>
#include <sdl2/SDL_ttf.h>
#include <string>
#include <map>


namespace Tools {
  bool loadGraphics(std::map<std::string, SDL_Texture*>& map);
  bool loadMusic(std::map<std::string, Mix_Music*>& map);
  bool loadFonts(std::map<std::string, TTF_Font*>& map);
}

#endif
