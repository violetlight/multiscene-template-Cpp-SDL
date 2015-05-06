#ifndef PREPARE_H
#define PREPARE_H
#include <sdl2/SDL.h>

namespace Screen {
  extern SDL_Window* window;
  extern SDL_Renderer* renderer;
}

namespace Prepare {
  bool init();
}

#endif
