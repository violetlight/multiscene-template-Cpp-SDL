#include <sdl2/SDL.h>
#include <sdl2/SDL_image.h>
#include <stdio.h>
#include <string>
#include "data/prepare.h"
#include "data/tools.h"
// #include "data/constants.h" //i think this will break it

void close(SDL_Window* Window)
{

  // Destroy window
  SDL_DestroyWindow(Window);
  Window = nullptr;

  // Quit SDL subsystems
  SDL_Quit();
}



int main (int argc, char* args[])
{

  Prepare::init();

  // std::map<std::string, SDL_Texture*> gfxMap;
  // loadGraphics(gfxMap);
  std::map<std::string, SDL_Texture*> gfx;
  loadGraphics(gfx);

  bool quit = false;
  SDL_Event e;

  while(!quit)
  {
    while(SDL_PollEvent(&e) != 0)
    {
      // Quit event
      if(e.type == SDL_QUIT)
      {
        quit = true;
      }
    } // events

    //Update the surface
    SDL_SetRenderDrawColor(Screen::renderer, 100, 0, 0, 255);
    SDL_RenderClear(Screen::renderer);
    // SDL_RenderCopy(Screen::renderer, loadGraphics(), NULL, NULL );
    SDL_RenderPresent(Screen::renderer);

  } // main loop


  // instantiate control object
  // std::map (dict) of states
  // control object init, pass in states dict
  // control object main loop()

  close(Screen::window);
  return 0;
}
