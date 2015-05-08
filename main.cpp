#include <sdl2/SDL.h>
#include <sdl2/SDL_image.h>
#include <sdl2/SDL_mixer.h>
#include <stdio.h>
#include <string>
#include "data/prepare.h"
#include "data/tools.h"
//#include "data/constants.h" //i think this will break it
#include <iostream>

void close(std::map<std::string, SDL_Texture*> gfx,
           std::map<std::string, Mix_Music*> music)
{

  // Destroy gfx
  for (auto &img: gfx)
  {
    SDL_DestroyTexture(img.second);
    img.second = nullptr;
  }

  // Destroy music
  for (auto &track: music)
  {
    Mix_FreeMusic(track.second);
    track.second = nullptr;
  }

  // Destroy window
  SDL_DestroyRenderer(Screen::renderer);
  SDL_DestroyWindow(Screen::window);
  Screen::window = nullptr;
  Screen::renderer = nullptr;

  // Quit SDL subsystems
  Mix_Quit();
  IMG_Quit();
  SDL_Quit();
}



int main (int argc, char* args[])
{

  Prepare::init();

  // all of this needs to go into a loadMedia function or something
  std::map<std::string, Mix_Music*> music;
  Tools::loadMusic(music);

  std::map<std::string, SDL_Texture*> gfx;
  Tools::loadGraphics(gfx);

  Tools::Sprite testGuy;
  if( !testGuy.loadFromFile( "resources/graphics/foo.png" ) ) //shim
  {
    printf( "Failed to load Foo' texture image!\n" );
  }
  // --------------------------------------------------------------

  bool quit = false;
  SDL_Event e;

  while(!quit)
  {
    while(SDL_PollEvent(&e) != 0)
    {

      // Key press
      if (e.type == SDL_KEYDOWN)
      {
        if (e.key.keysym.sym == SDLK_9)
        {    // no music playing
          if (Mix_PlayingMusic() == 0)
          {    // then play it
            if (Mix_PlayMusic(music["koorong.wav"], -1) == -1)
            {  // error
              return 1;
            } // music is playing
          } else
          {
            if (Mix_PausedMusic() == 1)
            {
              Mix_ResumeMusic();
            } else
            {
              Mix_PauseMusic();
            }
          }
        }
      }

      // Quit event
      if(e.type == SDL_QUIT)
      {
        quit = true;
      }
    }

    // Clear screen
    SDL_SetRenderDrawColor(Screen::renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(Screen::renderer);

    // Render splash image
    SDL_RenderCopy(Screen::renderer, gfx["splash2.png"], NULL, NULL );
    testGuy.render(0, 0);

    // Update screen
    SDL_RenderPresent(Screen::renderer);

  } // main loop


  // instantiate control object
  // std::map (dict) of states
  // control object init, pass in states dict
  // control object main loop()

  close(gfx, music);
  return 0;
}
