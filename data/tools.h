#ifndef TOOLS_H
#define TOOLS_H

#include <sdl2/SDL.h>
#include <sdl2/SDL_image.h>
#include <sdl2/SDL_mixer.h>
#include <sdl2/SDL_ttf.h>
#include <string>
#include <map>


namespace Tools {
  extern std::map<std::string, Mix_Music*> music;
  extern std::map<std::string, SDL_Texture*> gfx;
  extern std::map<std::string, TTF_Font*> fonts;

  bool loadMedia();
  bool loadGraphics();
  bool loadMusic();
  bool loadFonts();
}

#endif
