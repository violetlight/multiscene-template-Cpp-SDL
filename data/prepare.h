#ifndef PREPARE_H
#define PREPARE_H
#include <sdl2/SDL.h>

namespace Screen{
  SDL_Window* window;
  SDL_Renderer* renderer;
}

namespace Prepare {
  bool init();
}

#endif
